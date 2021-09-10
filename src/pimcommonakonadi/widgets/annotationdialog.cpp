/*
   SPDX-FileCopyrightText: 2010 Thomas McGuire <mcguire@kde.org>
   SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "annotationdialog.h"
#include <KPIMTextEdit/PlainTextEditorWidget>

#include <Akonadi/EntityAnnotationsAttribute>
#include <Akonadi/Item>
#include <Akonadi/ItemModifyJob>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KStandardGuiItem>

#include <QComboBox>
#include <QIcon>

#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace PimCommon;

class Q_DECL_HIDDEN AnnotationEditDialog::Private
{
public:
    Private()
    {
    }

    Akonadi::Item mItem;
    KPIMTextEdit::PlainTextEditorWidget *mTextEdit = nullptr;
    QComboBox *mNoteType = nullptr;
    bool mHasAnnotation = false;
};

AnnotationEditDialog::AnnotationEditDialog(const Akonadi::Item &item, QWidget *parent)
    : QDialog(parent)
    , d(new Private)
{
    d->mItem = item;
    // check for correct key?
    d->mHasAnnotation = item.hasAttribute<Akonadi::EntityAnnotationsAttribute>();
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    auto mainWidget = new QWidget(this);
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mainWidget);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AnnotationEditDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AnnotationEditDialog::reject);

    if (d->mHasAnnotation) {
        setWindowTitle(i18nc("@title:window", "Edit Note"));
        auto user1Button = new QPushButton;
        buttonBox->addButton(user1Button, QDialogButtonBox::ActionRole);
        user1Button->setText(i18nc("@action:button", "Delete Note"));
        user1Button->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));
        connect(user1Button, &QPushButton::clicked, this, &AnnotationEditDialog::slotDeleteNote);
    } else {
        setWindowTitle(i18nc("@title:window", "Add Note"));
    }

    buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);

    auto label = new QLabel(i18n("Enter the text that should be stored as a note to the mail:"));
    auto vbox = new QVBoxLayout(mainWidget);
    vbox->setContentsMargins(0, 0, 0, 0);
    d->mTextEdit = new KPIMTextEdit::PlainTextEditorWidget(this);
    vbox->addWidget(label);
    vbox->addWidget(d->mTextEdit);
    d->mTextEdit->setFocus();

    auto hbox = new QHBoxLayout;
    hbox->addStretch();
    label = new QLabel(i18nc("@label:listbox", "Note type:"));
    hbox->addWidget(label);
    d->mNoteType = new QComboBox;
    hbox->addWidget(d->mNoteType);
    d->mNoteType->addItem(i18nc("@item:inlistbox", "Private note"), QByteArrayLiteral("/private/comment"));
    d->mNoteType->addItem(i18nc("@item:inlistbox", "Shared note"), QByteArrayLiteral("/shared/comment"));

    vbox->addLayout(hbox);
    if (d->mHasAnnotation && item.attribute<Akonadi::EntityAnnotationsAttribute>()) {
        if (item.attribute<Akonadi::EntityAnnotationsAttribute>()->contains("/private/comment")) {
            d->mNoteType->setCurrentIndex(d->mNoteType->findData(QStringLiteral("/private/comment")));
            d->mTextEdit->setPlainText(item.attribute<Akonadi::EntityAnnotationsAttribute>()->value("/private/comment"));
        } else {
            d->mNoteType->setCurrentIndex(d->mNoteType->findData(QStringLiteral("/shared/comment")));
            d->mTextEdit->setPlainText(item.attribute<Akonadi::EntityAnnotationsAttribute>()->value("/shared/comment"));
        }
    }
    mainLayout->addWidget(buttonBox);
    readConfig();
}

AnnotationEditDialog::~AnnotationEditDialog()
{
    writeConfig();
    delete d;
}

void AnnotationEditDialog::slotAccepted()
{
    bool textIsEmpty = d->mTextEdit->isEmpty();
    if (!textIsEmpty) {
        d->mItem.removeAttribute<Akonadi::EntityAnnotationsAttribute>();
        auto annotation = d->mItem.attribute<Akonadi::EntityAnnotationsAttribute>(Akonadi::Item::AddIfMissing);
        QMap<QByteArray, QByteArray> map;
        map.insert(d->mNoteType->itemData(d->mNoteType->currentIndex()).toByteArray(), d->mTextEdit->toPlainText().toUtf8());
        annotation->setAnnotations(map);
        d->mItem.addAttribute(annotation);
    } else if (d->mHasAnnotation && textIsEmpty) {
        d->mItem.removeAttribute<Akonadi::EntityAnnotationsAttribute>();
    }
    new Akonadi::ItemModifyJob(d->mItem);
    accept();
}

void AnnotationEditDialog::slotDeleteNote()
{
    const int answer = KMessageBox::warningContinueCancel(this,
                                                          i18n("Do you really want to delete this note?"),
                                                          i18nc("@title:window", "Delete Note?"),
                                                          KStandardGuiItem::del());
    if (answer == KMessageBox::Continue) {
        d->mItem.removeAttribute<Akonadi::EntityAnnotationsAttribute>();
        new Akonadi::ItemModifyJob(d->mItem);
        accept();
    }
}

void AnnotationEditDialog::readConfig()
{
    KSharedConfig::Ptr cfg = KSharedConfig::openConfig();
    KConfigGroup group(cfg, "AnnotationEditDialog");
    QSize size = group.readEntry("Size", QSize());
    if (!size.isEmpty()) {
        resize(size);
    }
}

void AnnotationEditDialog::writeConfig()
{
    KSharedConfig::Ptr cfg = KSharedConfig::openConfig();
    KConfigGroup group(cfg, "AnnotationEditDialog");
    group.writeEntry("Size", size());
}
