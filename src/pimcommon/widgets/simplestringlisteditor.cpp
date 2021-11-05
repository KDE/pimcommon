/*
    simplestringlisteditor.cpp

    This file is part of KMail, the KDE mail client.
    SPDX-FileCopyrightText: 2001 Marc Mutz <mutz@kde.org>

    SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "simplestringlisteditor.h"

#include "pimcommon_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QInputDialog>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>

//********************************************************
// SimpleStringListEditor
//********************************************************
using namespace PimCommon;

class PimCommon::SimpleStringListEditorPrivate
{
public:
    SimpleStringListEditorPrivate()
    {
    }

    QList<QListWidgetItem *> selectedItems() const
    {
        QList<QListWidgetItem *> listWidgetItem;
        const int numberOfFilters = mListBox->count();
        for (int i = 0; i < numberOfFilters; ++i) {
            if (mListBox->item(i)->isSelected()) {
                listWidgetItem << mListBox->item(i);
            }
        }
        return listWidgetItem;
    }

    QListWidget *mListBox = nullptr;
    QPushButton *mAddButton = nullptr;
    QPushButton *mRemoveButton = nullptr;
    QPushButton *mModifyButton = nullptr;
    QPushButton *mUpButton = nullptr;
    QPushButton *mDownButton = nullptr;
    QPushButton *mCustomButton = nullptr;
    QVBoxLayout *mButtonLayout = nullptr;
    QString mAddDialogLabel = i18n("New entry:");
    QString mAddDialogTitle = i18n("New Value");
    QString mModifyDialogTitle = i18n("New Value");
    QString mModifyDialogLabel = i18n("New entry:");
    QString mRemoveDialogLabel = i18n("Do you want to remove selected text?");
};

SimpleStringListEditor::SimpleStringListEditor(QWidget *parent,
                                               ButtonCode buttons,
                                               const QString &addLabel,
                                               const QString &removeLabel,
                                               const QString &modifyLabel,
                                               const QString &addDialogLabel)
    : QWidget(parent)
    , d(new SimpleStringListEditorPrivate)
{
    setAddDialogLabel(addDialogLabel);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    auto hlay = new QHBoxLayout(this);
    hlay->setContentsMargins({});

    d->mListBox = new QListWidget(this);

    d->mListBox->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(d->mListBox, &QListWidget::customContextMenuRequested, this, &SimpleStringListEditor::slotContextMenu);

    d->mListBox->setSelectionMode(QAbstractItemView::ExtendedSelection);
    hlay->addWidget(d->mListBox, 1);

    if (buttons == None) {
        qCDebug(PIMCOMMON_LOG) << "SimpleStringListBox called with no buttons."
                                  "Consider using a plain QListBox instead!";
    }

    d->mButtonLayout = new QVBoxLayout(); // inherits spacing
    hlay->addLayout(d->mButtonLayout);

    if (buttons & Add) {
        if (addLabel.isEmpty()) {
            d->mAddButton = new QPushButton(i18n("&Add..."), this);
        } else {
            d->mAddButton = new QPushButton(addLabel, this);
        }
        d->mAddButton->setAutoDefault(false);
        d->mButtonLayout->addWidget(d->mAddButton);
        connect(d->mAddButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotAdd);
    }

    if (buttons & Modify) {
        if (modifyLabel.isEmpty()) {
            d->mModifyButton = new QPushButton(i18n("&Modify..."), this);
        } else {
            d->mModifyButton = new QPushButton(modifyLabel, this);
        }
        d->mModifyButton->setAutoDefault(false);
        d->mModifyButton->setEnabled(false); // no selection yet
        d->mButtonLayout->addWidget(d->mModifyButton);
        connect(d->mModifyButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotModify);
        connect(d->mListBox, &QListWidget::itemDoubleClicked, this, &SimpleStringListEditor::slotModify);
    }

    if (buttons & Remove) {
        if (removeLabel.isEmpty()) {
            d->mRemoveButton = new QPushButton(i18n("&Remove"), this);
        } else {
            d->mRemoveButton = new QPushButton(removeLabel, this);
        }
        d->mRemoveButton->setAutoDefault(false);
        d->mRemoveButton->setEnabled(false); // no selection yet
        d->mButtonLayout->addWidget(d->mRemoveButton);
        connect(d->mRemoveButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotRemove);
    }

    if (buttons & Up) {
        if (!(buttons & Down)) {
            qCDebug(PIMCOMMON_LOG) << "Are you sure you want to use an Up button"
                                      "without a Down button??";
        }
        d->mUpButton = new QPushButton(QString(), this);
        d->mUpButton->setIcon(QIcon::fromTheme(QStringLiteral("go-up")));
        d->mUpButton->setAutoDefault(false);
        d->mUpButton->setEnabled(false); // no selection yet
        d->mButtonLayout->addWidget(d->mUpButton);
        connect(d->mUpButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotUp);
    }

    if (buttons & Down) {
        if (!(buttons & Up)) {
            qCDebug(PIMCOMMON_LOG) << "Are you sure you want to use a Down button"
                                      "without an Up button??";
        }
        d->mDownButton = new QPushButton(QString(), this);
        d->mDownButton->setIcon(QIcon::fromTheme(QStringLiteral("go-down")));
        d->mDownButton->setAutoDefault(false);
        d->mDownButton->setEnabled(false); // no selection yet
        d->mButtonLayout->addWidget(d->mDownButton);
        connect(d->mDownButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotDown);
    }

    if (buttons & Custom) {
        d->mCustomButton = new QPushButton(i18n("&Customize..."), this);
        d->mCustomButton->setAutoDefault(false);
        d->mCustomButton->setEnabled(false); // no selection yet
        d->mButtonLayout->addWidget(d->mCustomButton);
        connect(d->mCustomButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotCustomize);
    }

    d->mButtonLayout->addStretch(1); // spacer

    connect(d->mListBox, &QListWidget::currentItemChanged, this, &SimpleStringListEditor::slotSelectionChanged);
    connect(d->mListBox, &QListWidget::itemSelectionChanged, this, &SimpleStringListEditor::slotSelectionChanged);
}

SimpleStringListEditor::~SimpleStringListEditor() = default;

void SimpleStringListEditor::setUpDownAutoRepeat(bool b)
{
    if (d->mUpButton) {
        d->mUpButton->setAutoRepeat(b);
    }
    if (d->mDownButton) {
        d->mDownButton->setAutoRepeat(b);
    }
}

void SimpleStringListEditor::setStringList(const QStringList &strings)
{
    d->mListBox->clear();
    d->mListBox->addItems(strings);
}

void SimpleStringListEditor::appendStringList(const QStringList &strings)
{
    d->mListBox->addItems(strings);
}

QStringList SimpleStringListEditor::stringList() const
{
    QStringList result;
    const int numberOfItem(d->mListBox->count());
    result.reserve(numberOfItem);
    for (int i = 0; i < numberOfItem; ++i) {
        result << (d->mListBox->item(i)->text());
    }
    return result;
}

bool SimpleStringListEditor::containsString(const QString &str)
{
    const int numberOfItem(d->mListBox->count());
    for (int i = 0; i < numberOfItem; ++i) {
        if (d->mListBox->item(i)->text() == str) {
            return true;
        }
    }
    return false;
}

void SimpleStringListEditor::setButtonText(ButtonCode button, const QString &text)
{
    switch (button) {
    case Add:
        if (!d->mAddButton) {
            break;
        }
        d->mAddButton->setText(text);
        return;
    case Remove:
        if (!d->mRemoveButton) {
            break;
        }
        d->mRemoveButton->setText(text);
        return;
    case Modify:
        if (!d->mModifyButton) {
            break;
        }
        d->mModifyButton->setText(text);
        return;
    case Custom:
        if (!d->mCustomButton) {
            break;
        }
        d->mCustomButton->setText(text);
        return;
    case Up:
    case Down:
        qCDebug(PIMCOMMON_LOG) << "SimpleStringListEditor: Cannot change text of"
                                  "Up and Down buttons: they don't contains text!";
        return;
    default:
        if (button & All) {
            qCDebug(PIMCOMMON_LOG) << "No such button!";
        } else {
            qCDebug(PIMCOMMON_LOG) << "Can only set text for one button at a time!";
        }
        return;
    }

    qCDebug(PIMCOMMON_LOG) << "The requested button has not been created!";
}

void SimpleStringListEditor::addNewEntry()
{
    bool ok = false;
    const QString newEntry = QInputDialog::getText(this, d->mAddDialogTitle, d->mAddDialogLabel, QLineEdit::Normal, QString(), &ok);
    if (ok && !newEntry.trimmed().isEmpty()) {
        insertNewEntry(newEntry);
    }
}

void SimpleStringListEditor::insertNewEntry(const QString &entry)
{
    QString newEntry = entry;
    // let the user verify the string before adding
    Q_EMIT aboutToAdd(newEntry);
    if (!newEntry.isEmpty() && !containsString(newEntry)) {
        d->mListBox->addItem(newEntry);
        slotSelectionChanged();
        Q_EMIT changed();
    }
}

void SimpleStringListEditor::slotAdd()
{
    addNewEntry();
}

void SimpleStringListEditor::slotCustomize()
{
    QListWidgetItem *item = d->mListBox->currentItem();
    if (!item) {
        return;
    }
    const QString newText = customEntry(item->text());
    if (!newText.isEmpty()) {
        item->setText(newText);
        Q_EMIT changed();
    }
}

QString SimpleStringListEditor::customEntry(const QString &text)
{
    Q_UNUSED(text)
    return {};
}

void SimpleStringListEditor::slotRemove()
{
    const QList<QListWidgetItem *> selectedItems = d->mListBox->selectedItems();
    if (selectedItems.isEmpty()) {
        return;
    }
    const int answer = KMessageBox::warningYesNo(this, d->mRemoveDialogLabel, i18n("Remove"), KStandardGuiItem::remove(), KStandardGuiItem::cancel());
    if (answer == KMessageBox::Yes) {
        for (QListWidgetItem *item : selectedItems) {
            delete d->mListBox->takeItem(d->mListBox->row(item));
        }
        slotSelectionChanged();
        Q_EMIT changed();
    }
}

QString SimpleStringListEditor::modifyEntry(const QString &text)
{
    bool ok = false;
    QString newText = QInputDialog::getText(this, d->mModifyDialogTitle, d->mModifyDialogLabel, QLineEdit::Normal, text, &ok);
    Q_EMIT aboutToAdd(newText);

    if (!ok || newText.trimmed().isEmpty() || newText == text) {
        return QString();
    }

    return newText;
}

void SimpleStringListEditor::slotModify()
{
    QListWidgetItem *item = d->mListBox->currentItem();
    if (!item) {
        return;
    }
    const QString newText = modifyEntry(item->text());
    if (!newText.isEmpty()) {
        item->setText(newText);
        Q_EMIT changed();
    }
}

void SimpleStringListEditor::setRemoveDialogLabel(const QString &removeDialogLabel)
{
    d->mRemoveDialogLabel = removeDialogLabel;
}

void SimpleStringListEditor::setAddDialogLabel(const QString &addDialogLabel)
{
    d->mAddDialogLabel = addDialogLabel;
}

void SimpleStringListEditor::setAddDialogTitle(const QString &str)
{
    d->mAddDialogTitle = str;
}

void SimpleStringListEditor::setModifyDialogTitle(const QString &str)
{
    d->mModifyDialogTitle = str;
}

void SimpleStringListEditor::setModifyDialogLabel(const QString &str)
{
    d->mModifyDialogLabel = str;
}

void SimpleStringListEditor::slotUp()
{
    QList<QListWidgetItem *> listWidgetItem = d->selectedItems();
    if (listWidgetItem.isEmpty()) {
        return;
    }

    const int numberOfItem(listWidgetItem.count());
    const int currentRow = d->mListBox->currentRow();
    if ((numberOfItem == 1) && (currentRow == 0)) {
        qCDebug(PIMCOMMON_LOG) << "Called while the _topmost_ filter is selected, ignoring.";
        return;
    }
    bool wasMoved = false;

    for (int i = 0; i < numberOfItem; ++i) {
        const int posItem = d->mListBox->row(listWidgetItem.at(i));
        if (posItem == i) {
            continue;
        }
        QListWidgetItem *item = d->mListBox->takeItem(posItem);
        d->mListBox->insertItem(posItem - 1, item);

        wasMoved = true;
    }
    if (wasMoved) {
        Q_EMIT changed();
        d->mListBox->setCurrentRow(currentRow - 1);
    }
}

void SimpleStringListEditor::slotDown()
{
    QList<QListWidgetItem *> listWidgetItem = d->selectedItems();
    if (listWidgetItem.isEmpty()) {
        return;
    }

    const int numberOfElement(d->mListBox->count());
    const int numberOfItem(listWidgetItem.count());
    const int currentRow = d->mListBox->currentRow();
    if ((numberOfItem == 1) && (currentRow == numberOfElement - 1)) {
        qCDebug(PIMCOMMON_LOG) << "Called while the _last_ filter is selected, ignoring.";
        return;
    }

    int j = 0;
    bool wasMoved = false;
    for (int i = numberOfItem - 1; i >= 0; --i, j++) {
        const int posItem = d->mListBox->row(listWidgetItem.at(i));
        if (posItem == (numberOfElement - 1 - j)) {
            continue;
        }
        QListWidgetItem *item = d->mListBox->takeItem(posItem);
        d->mListBox->insertItem(posItem + 1, item);
        wasMoved = true;
    }
    if (wasMoved) {
        Q_EMIT changed();
        d->mListBox->setCurrentRow(currentRow + 1);
    }
}

void SimpleStringListEditor::slotSelectionChanged()
{
    const QList<QListWidgetItem *> lstSelectedItems = d->mListBox->selectedItems();
    const int numberOfItemSelected(lstSelectedItems.count());
    const bool uniqItemSelected = (numberOfItemSelected == 1);
    const bool aItemIsSelected = !lstSelectedItems.isEmpty();
    // if there is one, item will be non-null (ie. true), else 0
    // (ie. false):
    if (d->mRemoveButton) {
        d->mRemoveButton->setEnabled(aItemIsSelected);
    }

    if (d->mModifyButton) {
        d->mModifyButton->setEnabled(uniqItemSelected);
    }

    const int currentIndex = d->mListBox->currentRow();

    const bool allItemSelected = (d->mListBox->count() == numberOfItemSelected);
    const bool theLast = (currentIndex >= d->mListBox->count() - 1);
    const bool theFirst = (currentIndex == 0);

    if (d->mCustomButton) {
        d->mCustomButton->setEnabled(uniqItemSelected);
    }

    if (d->mUpButton) {
        d->mUpButton->setEnabled(aItemIsSelected && ((uniqItemSelected && !theFirst) || (!uniqItemSelected)) && !allItemSelected);
    }
    if (d->mDownButton) {
        d->mDownButton->setEnabled(aItemIsSelected && ((uniqItemSelected && !theLast) || (!uniqItemSelected)) && !allItemSelected);
    }
}

void SimpleStringListEditor::slotContextMenu(const QPoint &pos)
{
    QList<QListWidgetItem *> lstSelectedItems = d->mListBox->selectedItems();
    const bool hasItemsSelected = !lstSelectedItems.isEmpty();
    QMenu menu(this);
    if (d->mAddButton) {
        QAction *act = menu.addAction(d->mAddButton->text(), this, &SimpleStringListEditor::slotAdd);
        act->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    }
    if (d->mModifyButton && (lstSelectedItems.count() == 1)) {
        QAction *act = menu.addAction(d->mModifyButton->text(), this, &SimpleStringListEditor::slotModify);
        act->setIcon(QIcon::fromTheme(QStringLiteral("document-edit")));
    }
    if (d->mRemoveButton && hasItemsSelected) {
        menu.addSeparator();
        QAction *act = menu.addAction(d->mRemoveButton->text(), this, &SimpleStringListEditor::slotRemove);
        act->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    }
    if (!menu.isEmpty()) {
        menu.exec(d->mListBox->mapToGlobal(pos));
    }
}

QSize SimpleStringListEditor::sizeHint() const
{
    // Override height because we want the widget to be tall enough to fit the
    // button columns, but we want to allow it to be made smaller than list
    // sizeHint().height()
    QSize sh = QWidget::sizeHint();
    sh.setHeight(d->mButtonLayout->minimumSize().height());
    return sh;
}
