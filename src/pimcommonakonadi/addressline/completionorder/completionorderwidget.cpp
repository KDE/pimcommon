/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "completionorderwidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KDescendantsProxyModel>
#include <KLDAPCore/LdapClient>
#include <KLDAPCore/LdapClientSearch>

#include <KContacts/Addressee>
#include <KContacts/ContactGroup>
#include <KLDAPCore/LdapClientSearchConfig>

#include <Akonadi/ChangeRecorder>
#include <Akonadi/CollectionFilterProxyModel>
#include <Akonadi/EntityTreeModel>
#include <Akonadi/Monitor>

#include <kldapcore/ldapserver.h>

#include <KConfigGroup>
#include <KLocalizedString>
#include <QDBusConnection>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

using namespace PimCommon;

CompletionOrderEditorAdaptor::CompletionOrderEditorAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    setAutoRelaySignals(true);
}

class LDAPCompletionItem : public CompletionItem
{
public:
    explicit LDAPCompletionItem(KLDAPCore::LdapClient *ldapClient)
        : mLdapClient(ldapClient)
    {
        mWeight = mLdapClient->completionWeight();
    }

    [[nodiscard]] QString label() const override
    {
        return i18n("LDAP server %1", mLdapClient->server().host());
    }

    [[nodiscard]] QIcon icon() const override
    {
        return QIcon::fromTheme(QStringLiteral("kmail"));
    }

    [[nodiscard]] int completionWeight() const override
    {
        return mWeight;
    }

    void save(CompletionOrderWidget *) override
    {
        KConfig *config = KLDAPCore::LdapClientSearchConfig::config();
        KConfigGroup group(config, QStringLiteral("LDAP"));
        group.writeEntry(QStringLiteral("SelectedCompletionWeight%1").arg(mLdapClient->clientNumber()), mWeight);
        group.sync();
    }

    [[nodiscard]] bool hasEnableSupport() const override
    {
        return false;
    }

    [[nodiscard]] bool isEnabled() const override
    {
        return true;
    }

    void setIsEnabled(bool b) override
    {
        Q_UNUSED(b)
    }

protected:
    void setCompletionWeight(int weight) override
    {
        mWeight = weight;
    }

private:
    KLDAPCore::LdapClient *const mLdapClient;
    int mWeight;
};

class SimpleCompletionItem : public CompletionItem
{
public:
    SimpleCompletionItem(CompletionOrderWidget *editor, const QString &label, const QString &identifier, int weight, bool enableSupport = false)
        : mLabel(label)
        , mIdentifier(identifier)
        , mHasEnableSupport(enableSupport)
        , mEnabled(true)
    {
        KConfigGroup groupCompletionWeights(editor->configFile(), QStringLiteral("CompletionWeights"));
        mWeight = groupCompletionWeights.readEntry(mIdentifier, weight);
        if (mHasEnableSupport) {
            KConfigGroup groupEnabled(editor->configFile(), QStringLiteral("CompletionEnabled"));
            mEnabled = groupEnabled.readEntry(mIdentifier, true);
        }
    }

    ~SimpleCompletionItem() override = default;

    [[nodiscard]] bool isEnabled() const override
    {
        return mEnabled;
    }

    [[nodiscard]] bool hasEnableSupport() const override
    {
        return mHasEnableSupport;
    }

    void setIcon(const QIcon &icon)
    {
        mIcon = icon;
    }

    [[nodiscard]] QString label() const override
    {
        return mLabel;
    }

    [[nodiscard]] QIcon icon() const override
    {
        return mIcon;
    }

    [[nodiscard]] int completionWeight() const override
    {
        return mWeight;
    }

    void setIsEnabled(bool b) override
    {
        mEnabled = b;
    }

    void save(CompletionOrderWidget *editor) override
    {
        KConfigGroup group(editor->configFile(), QStringLiteral("CompletionWeights"));
        group.writeEntry(mIdentifier, mWeight);
        if (mHasEnableSupport) {
            KConfigGroup groupEnabled(editor->configFile(), QStringLiteral("CompletionEnabled"));
            groupEnabled.writeEntry(mIdentifier, isEnabled());
        }
    }

protected:
    void setCompletionWeight(int weight) override
    {
        mWeight = weight;
    }

private:
    QString mLabel;
    QString mIdentifier;
    int mWeight;
    QIcon mIcon;
    bool mHasEnableSupport;
    bool mEnabled;
};

/////////

class CompletionViewItem : public QTreeWidgetItem
{
public:
    CompletionViewItem(QTreeWidget *parent, CompletionItem *item)
        : QTreeWidgetItem(parent)
    {
        setItem(item);
    }

    ~CompletionViewItem() override
    {
        delete mItem;
    }

    void setItem(CompletionItem *item)
    {
        mItem = item;
        setText(0, mItem->label());
        setIcon(0, mItem->icon());
        if (mItem->hasEnableSupport()) {
            setFlags(flags() | Qt::ItemIsUserCheckable);
            setCheckState(0, mItem->isEnabled() ? Qt::Checked : Qt::Unchecked);
        } else {
            setFlags(flags() & ~Qt::ItemIsUserCheckable);
        }
    }

    [[nodiscard]] CompletionItem *item() const
    {
        return mItem;
    }

    bool operator<(const QTreeWidgetItem &other) const override
    {
        const QTreeWidgetItem *otherItem = &other;
        const auto completionItem = static_cast<const CompletionViewItem *>(otherItem);
        // item with weight 100 should be on the top -> reverse sorting
        return mItem->completionWeight() > completionItem->item()->completionWeight();
    }

private:
    CompletionItem *mItem = nullptr;
};

CompletionOrderWidget::CompletionOrderWidget(QWidget *parent)
    : QWidget(parent)
    , mConfig(QStringLiteral("kpimcompletionorder"))
{
    new CompletionOrderEditorAdaptor(this);
    QDBusConnection::sessionBus().registerObject(QStringLiteral("/"), this, QDBusConnection::ExportAdaptors);

    auto hbox = new QHBoxLayout(this);

    auto page = new QWidget(this);
    auto pageHBoxLayout = new QHBoxLayout(page);
    pageHBoxLayout->setContentsMargins({});
    hbox->addWidget(page);
    mListView = new QTreeWidget(page);
    mListView->setObjectName("listview"_L1);

    pageHBoxLayout->addWidget(mListView);
    mListView->setColumnCount(1);
    mListView->setAlternatingRowColors(true);
    mListView->setIndentation(0);
    mListView->setAllColumnsShowFocus(true);
    mListView->setHeaderHidden(true);
    mListView->setSortingEnabled(true);

    auto upDownBox = new QWidget(page);
    auto upDownBoxVBoxLayout = new QVBoxLayout(upDownBox);
    upDownBoxVBoxLayout->setContentsMargins({});
    pageHBoxLayout->addWidget(upDownBox);
    mUpButton = new QPushButton(upDownBox);
    upDownBoxVBoxLayout->addWidget(mUpButton);
    mUpButton->setAutoRepeat(true);
    mUpButton->setObjectName("mUpButton"_L1);
    mUpButton->setIcon(QIcon::fromTheme(QStringLiteral("go-up")));
    mUpButton->setEnabled(false); // b/c no item is selected yet
    mUpButton->setToolTip(i18nc("@info:tooltip", "Move Up"));
    mUpButton->setFocusPolicy(Qt::StrongFocus);

    mDownButton = new QPushButton(upDownBox);
    upDownBoxVBoxLayout->addWidget(mDownButton);
    mDownButton->setAutoRepeat(true);
    mDownButton->setObjectName("mDownButton"_L1);
    mDownButton->setIcon(QIcon::fromTheme(QStringLiteral("go-down")));
    mDownButton->setEnabled(false); // b/c no item is selected yet
    mDownButton->setToolTip(i18nc("@info:tooltip", "Move Down"));
    mDownButton->setFocusPolicy(Qt::StrongFocus);

    auto spacer = new QWidget(upDownBox);
    upDownBoxVBoxLayout->addWidget(spacer);
    upDownBoxVBoxLayout->setStretchFactor(spacer, 100);

    connect(mListView, &QTreeWidget::itemSelectionChanged, this, &CompletionOrderWidget::slotSelectionChanged);
    connect(mListView, &QTreeWidget::currentItemChanged, this, &CompletionOrderWidget::slotSelectionChanged);
    connect(mListView, &QTreeWidget::itemChanged, this, &CompletionOrderWidget::slotItemChanged);
    connect(mUpButton, &QAbstractButton::clicked, this, &CompletionOrderWidget::slotMoveUp);
    connect(mDownButton, &QAbstractButton::clicked, this, &CompletionOrderWidget::slotMoveDown);
}

CompletionOrderWidget::~CompletionOrderWidget() = default;

void CompletionOrderWidget::save()
{
    if (mDirty) {
        int w = 100;
        // Clean up order
        KConfigGroup group(configFile(), QStringLiteral("CompletionWeights"));
        group.deleteGroup(QLatin1StringView());

        for (int itemIndex = 0; itemIndex < mListView->topLevelItemCount(); ++itemIndex) {
            auto item = static_cast<CompletionViewItem *>(mListView->topLevelItem(itemIndex));
            item->item()->setCompletionWeight(w);
            item->item()->setIsEnabled(item->checkState(0) == Qt::Checked);
            item->item()->save(this);
            --w;
        }
        Q_EMIT completionOrderChanged();
    }
}

KConfig *CompletionOrderWidget::configFile()
{
    return &mConfig;
}

void CompletionOrderWidget::addRecentAddressItem()
{
    // Be default it's the first.
    auto item = new SimpleCompletionItem(this, i18n("Recent Addresses"), QStringLiteral("Recent Addresses"), 10);
    item->setIcon(QIcon::fromTheme(QStringLiteral("kmail")));
    new CompletionViewItem(mListView, item);
}

void CompletionOrderWidget::addCompletionItemForCollection(const QModelIndex &index)
{
    const auto collection = index.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
    if (!collection.isValid()) {
        return;
    }

    auto item = new SimpleCompletionItem(this, index.data().toString(), QString::number(collection.id()), mDefaultValue++, true);
    item->setIcon(index.data(Qt::DecorationRole).value<QIcon>());

    new CompletionViewItem(mListView, item);
}

void CompletionOrderWidget::loadCompletionItems()
{
    if (mLdapSearch) {
        // The first step is to gather all the data, creating CompletionItem objects
        const QList<KLDAPCore::LdapClient *> listClients = mLdapSearch->clients();
        for (KLDAPCore::LdapClient *client : listClients) {
            // TODO add activities support
#if 0
            if (client->server().enablePlasmaActivities() && !client->server().activities().contains(/*TODO*/)) {
                continue;
            }
#endif
            new CompletionViewItem(mListView, new LDAPCompletionItem(client));
        }
    }

    auto monitor = new Akonadi::ChangeRecorder(this);
    monitor->fetchCollection(true);
    monitor->setCollectionMonitored(Akonadi::Collection::root());
    monitor->setMimeTypeMonitored(KContacts::Addressee::mimeType(), true);
    monitor->setMimeTypeMonitored(KContacts::ContactGroup::mimeType(), true);

    auto model = new Akonadi::EntityTreeModel(monitor, this);
    model->setItemPopulationStrategy(Akonadi::EntityTreeModel::NoItemPopulation);

    auto descendantsProxy = new KDescendantsProxyModel(this);
    descendantsProxy->setDisplayAncestorData(true);
    descendantsProxy->setSourceModel(model);

    auto mimeTypeProxy = new Akonadi::CollectionFilterProxyModel(this);
    mimeTypeProxy->addMimeTypeFilters({KContacts::Addressee::mimeType(), KContacts::ContactGroup::mimeType()});
    mimeTypeProxy->setSourceModel(descendantsProxy);
    mimeTypeProxy->setExcludeVirtualCollections(true);

    mCollectionModel = mimeTypeProxy;

    connect(mimeTypeProxy, &QAbstractItemModel::rowsInserted, this, &CompletionOrderWidget::rowsInserted);
    for (int row = 0; row < mCollectionModel->rowCount(); ++row) {
        addCompletionItemForCollection(mCollectionModel->index(row, 0));
    }
    addRecentAddressItem();

    mListView->sortItems(0, Qt::AscendingOrder);

    mDirty = false;
}

void CompletionOrderWidget::setLdapActivitiesAbstract(KLDAPCore::LdapActivitiesAbstract *ldapActivities)
{
    mLdapActivities = ldapActivities;
}

void CompletionOrderWidget::setLdapClientSearch(KLDAPCore::LdapClientSearch *ldapSearch)
{
    mLdapSearch = ldapSearch;
}

void CompletionOrderWidget::rowsInserted(const QModelIndex &parent, int start, int end)
{
    for (int row = start; row <= end; ++row) {
        addCompletionItemForCollection(mCollectionModel->index(row, 0, parent));
    }

    mListView->sortItems(0, Qt::AscendingOrder);
}

void CompletionOrderWidget::slotItemChanged()
{
    mDirty = true;
}

void CompletionOrderWidget::slotSelectionChanged()
{
    QTreeWidgetItem *item = mListView->currentItem();
    mDownButton->setEnabled(item && mListView->itemBelow(item));
    mUpButton->setEnabled(item && mListView->itemAbove(item));
}

static void swapItems(CompletionViewItem *one, CompletionViewItem *other)
{
    CompletionItem *oneCompletion = one->item();
    CompletionItem *otherCompletion = other->item();

    int weight = otherCompletion->completionWeight();
    otherCompletion->setCompletionWeight(oneCompletion->completionWeight());
    oneCompletion->setCompletionWeight(weight);

    one->setItem(oneCompletion);
    other->setItem(otherCompletion);
}

void CompletionOrderWidget::slotMoveUp()
{
    auto item = static_cast<CompletionViewItem *>(mListView->currentItem());
    if (!item) {
        return;
    }
    auto above = static_cast<CompletionViewItem *>(mListView->itemAbove(item));
    if (!above) {
        return;
    }
    swapItems(item, above);
    mListView->sortItems(0, Qt::AscendingOrder);
    slotSelectionChanged();
    mDirty = true;
}

void CompletionOrderWidget::slotMoveDown()
{
    auto item = static_cast<CompletionViewItem *>(mListView->currentItem());
    if (!item) {
        return;
    }
    auto below = static_cast<CompletionViewItem *>(mListView->itemBelow(item));
    if (!below) {
        return;
    }
    swapItems(item, below);
    mListView->sortItems(0, Qt::AscendingOrder);
    slotSelectionChanged();
    mDirty = true;
}

#include "moc_completionorderwidget.cpp"
