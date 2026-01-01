/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "collectionaclwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "acllistview.h"
#include "aclmanager.h"

#include <KLocalizedString>

#include <QAction>
#include <QActionEvent>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

using namespace PimCommon;
/**
 * Unfortunately QPushButton doesn't support to plug in
 * a QAction like QToolButton does, so we have to reimplement it :(
 */
class ActionButton : public QPushButton
{
public:
    explicit ActionButton(QWidget *parent = nullptr)
        : QPushButton(parent)
    {
    }

    void setDefaultAction(QAction *action)
    {
        if (!actions().contains(action)) {
            addAction(action);
            connect(this, &QAbstractButton::clicked, action, &QAction::trigger);
        }

        setText(action->text());
        setEnabled(action->isEnabled());

        mDefaultAction = action;
    }

protected:
    void actionEvent(QActionEvent *event) override
    {
        QAction *action = event->action();
        switch (event->type()) {
        case QEvent::ActionChanged:
            if (action == mDefaultAction) {
                setDefaultAction(mDefaultAction);
            }
            return;
            break;
        default:
            break;
        }

        QPushButton::actionEvent(event);
    }

private:
    QAction *mDefaultAction = nullptr;
};

CollectionAclWidget::CollectionAclWidget(QWidget *parent)
    : QWidget(parent)
    , mAclManager(new PimCommon::AclManager(this))
    , mRecursiveChk(new QCheckBox(i18nc("@option:check", "Apply permissions on all &subfolders."), this))
{
    auto layout = new QHBoxLayout(this);
    auto listViewLayout = new QVBoxLayout;
    layout->addLayout(listViewLayout);

    auto view = new AclListView;
    view->setObjectName("list_view"_L1);
    listViewLayout->addWidget(view);
    listViewLayout->addWidget(mRecursiveChk);
    connect(mRecursiveChk, &QCheckBox::clicked, this, &CollectionAclWidget::slotRecursivePermissionChanged);

    view->setAlternatingRowColors(true);
    view->setModel(mAclManager->model());
    view->setSelectionModel(mAclManager->selectionModel());

    auto buttonBox = new QWidget;
    auto buttonBoxVBoxLayout = new QVBoxLayout(buttonBox);
    buttonBoxVBoxLayout->setContentsMargins({});
    layout->addWidget(buttonBox);

    auto button = new ActionButton(buttonBox);
    buttonBoxVBoxLayout->addWidget(button);
    button->setObjectName("add"_L1);
    button->setDefaultAction(mAclManager->addAction());

    button = new ActionButton(buttonBox);
    buttonBoxVBoxLayout->addWidget(button);
    button->setObjectName("edit"_L1);
    button->setDefaultAction(mAclManager->editAction());

    button = new ActionButton(buttonBox);
    buttonBoxVBoxLayout->addWidget(button);
    button->setDefaultAction(mAclManager->deleteAction());
    button->setObjectName("delete"_L1);

    auto spacer = new QWidget(buttonBox);
    buttonBoxVBoxLayout->addWidget(spacer);
    spacer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    connect(view, SIGNAL(doubleClicked(QModelIndex)), mAclManager->editAction(), SIGNAL(triggered()));
    connect(mAclManager, &AclManager::collectionCanBeAdministrated, this, &CollectionAclWidget::slotCollectionCanBeAdministrated);
    connect(mAclManager, &AclManager::collectionCanBeAdministrated, view, &AclListView::slotCollectionCanBeAdministrated);
}

CollectionAclWidget::~CollectionAclWidget() = default;

void CollectionAclWidget::slotCollectionCanBeAdministrated(bool b)
{
    if (!b) {
        mRecursiveChk->setChecked(false);
    }
    mRecursiveChk->setEnabled(b);
}

AclManager *CollectionAclWidget::aclManager() const
{
    return mAclManager;
}

bool CollectionAclWidget::recursive() const
{
    return mRecursiveChk->isChecked();
}

void CollectionAclWidget::setEnableRecursiveCheckBox(bool enable)
{
    if (!enable) {
        mRecursiveChk->setChecked(false);
    }
    mRecursiveChk->setEnabled(enable);
}

void CollectionAclWidget::slotRecursivePermissionChanged()
{
    mAclManager->setChanged(true);
}

#include "moc_collectionaclwidget.cpp"
