/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "recentaddresswidget.h"
#include "recentaddresses.h"

#include <KConfig>
#include <KLocalizedString>
#include <KMessageBox>
#include <QLineEdit>
#include <QPushButton>

#include <QKeyEvent>
#include <QListWidget>
#include <QShortcut>
#include <QToolButton>
#include <QVBoxLayout>

#include <Libkdepim/LineEditCatchReturnKey>
#include <PimCommon/EmailValidator>
#include <kwidgetsaddons_version.h>

using namespace PimCommon;
RecentAddressWidget::RecentAddressWidget(QWidget *parent)
    : QWidget(parent)
    , mLineEdit(new QLineEdit(this))
    , mNewButton(new QToolButton(this))
    , mRemoveButton(new QToolButton(this))
    , mListView(new QListWidget(this))
{
    auto layout = new QVBoxLayout(this);

    auto lineLayout = new QHBoxLayout;
    layout->addLayout(lineLayout);

    mLineEdit->setObjectName(QStringLiteral("line_edit"));
    new KPIM::LineEditCatchReturnKey(mLineEdit, this);
    mLineEdit->installEventFilter(this);
    mLineEdit->setClearButtonEnabled(true);
    mLineEdit->setValidator(new PimCommon::EmailValidator(this));
    connect(mLineEdit, &QLineEdit::returnPressed, this, &RecentAddressWidget::slotAddItem);

    lineLayout->addWidget(mLineEdit);

    mNewButton->setToolTip(i18n("Add"));
    mNewButton->setObjectName(QStringLiteral("new_button"));
    mNewButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mNewButton->setEnabled(false);
    connect(mNewButton, &QPushButton::clicked, this, &RecentAddressWidget::slotAddItem);
    connect(mLineEdit, &QLineEdit::textChanged, this, &RecentAddressWidget::slotUpdateAddButton);
    lineLayout->addWidget(mNewButton);

    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    mRemoveButton->setToolTip(i18n("Remove"));
    mRemoveButton->setObjectName(QStringLiteral("remove_button"));
    mRemoveButton->setEnabled(false);
    lineLayout->addWidget(mRemoveButton);
    connect(mRemoveButton, &QPushButton::clicked, this, &RecentAddressWidget::slotRemoveItem);

    auto shortcut = new QShortcut(this);
    shortcut->setKey(QKeySequence(Qt::Key_Delete));
    connect(shortcut, &QShortcut::activated, this, &RecentAddressWidget::slotRemoveItem);

    mListView->setObjectName(QStringLiteral("list_view"));
    mListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mListView->setSortingEnabled(true);
    connect(mListView, &QListWidget::itemSelectionChanged, this, &RecentAddressWidget::updateButtonState);
    layout->addWidget(mListView);
    mDirty = false;
}

RecentAddressWidget::~RecentAddressWidget() = default;

void RecentAddressWidget::slotUpdateAddButton(const QString &str)
{
    mNewButton->setEnabled(!str.trimmed().isEmpty());
}

void RecentAddressWidget::slotAddItem()
{
    const QString newEmail = mLineEdit->text();
    if (newEmail.isEmpty()) {
        return;
    }
    const int numberOfItem(mListView->count());
    for (int i = 0; i < numberOfItem; ++i) {
        if (mListView->item(i)->text() == newEmail) {
            return;
        }
    }

    mListView->insertItem(0, mLineEdit->text());
    mListView->setCurrentRow(0, QItemSelectionModel::ClearAndSelect);
    mLineEdit->clear();
    mLineEdit->setFocus();
    mDirty = true;
    updateButtonState();
}

void RecentAddressWidget::slotRemoveItem()
{
    const QList<QListWidgetItem *> selectedItems = mListView->selectedItems();
    if (selectedItems.isEmpty()) {
        return;
    }
    const int answer =
        KMessageBox::questionTwoActions(this,
                                        i18np("Do you want to remove this email address?", "Do you want to remove %1 email addresses?", selectedItems.count()),
                                        i18n("Remove"),
                                        KStandardGuiItem::remove(),
                                        KStandardGuiItem::cancel());
    if (answer == KMessageBox::ButtonCode::PrimaryAction) {
        for (QListWidgetItem *item : selectedItems) {
            delete mListView->takeItem(mListView->row(item));
        }
        mDirty = true;
        updateButtonState();
    }
}

void RecentAddressWidget::updateButtonState()
{
    QList<QListWidgetItem *> selectedItems = mListView->selectedItems();
    const int numberOfElementSelected(selectedItems.count());
    mRemoveButton->setEnabled(numberOfElementSelected);
    bool enableElement = (numberOfElementSelected <= 1);
    mNewButton->setEnabled(enableElement);
    mLineEdit->setEnabled(enableElement);
}

void RecentAddressWidget::setAddresses(const QStringList &addrs)
{
    mListView->clear();
    mListView->addItems(addrs);
}

bool RecentAddressWidget::eventFilter(QObject *o, QEvent *e)
{
    if (o == mLineEdit && e->type() == QEvent::KeyPress) {
        auto keyEvent = static_cast<QKeyEvent *>(e);
        if (keyEvent->key() == Qt::Key_Down || keyEvent->key() == Qt::Key_Up) {
            return (static_cast<QObject *>(mListView))->event(e);
        }
    }

    return false;
}

void RecentAddressWidget::storeAddresses(KConfig *config)
{
    const int numberOfItem(mListView->count());
    for (int i = 0; i < numberOfItem; ++i) {
        PimCommon::RecentAddresses::self(config)->add(mListView->item(i)->text());
    }
}

bool RecentAddressWidget::wasChanged() const
{
    return mDirty;
}
