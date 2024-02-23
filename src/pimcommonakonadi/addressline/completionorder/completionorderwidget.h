/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_private_export.h"
#include <KConfig>
#include <QDBusAbstractAdaptor>
#include <QWidget>

class QPushButton;
class QAbstractItemModel;
class QModelIndex;
class QTreeWidget;

namespace KLDAPWidgets
{
class LdapClientSearch;
}

namespace PimCommon
{
class CompletionOrderEditorAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.pim.CompletionOrder")
public:
    explicit CompletionOrderEditorAdaptor(QObject *parent);
Q_SIGNALS:
    void completionOrderChanged();
};

class CompletionOrderWidget;

// Base class for items in the list
class CompletionItem
{
public:
    virtual ~CompletionItem() = default;

    virtual QString label() const = 0;
    virtual QIcon icon() const = 0;
    virtual int completionWeight() const = 0;
    virtual void setCompletionWeight(int weight) = 0;
    virtual void save(CompletionOrderWidget *) = 0;
    virtual bool hasEnableSupport() const = 0;
    virtual bool isEnabled() const = 0;
    virtual void setIsEnabled(bool b) = 0;
};

class PIMCOMMONAKONADI_TESTS_EXPORT CompletionOrderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CompletionOrderWidget(QWidget *parent = nullptr);
    ~CompletionOrderWidget() override;
    void save();

    KConfig *configFile();
    void loadCompletionItems();
    void setLdapClientSearch(KLDAPWidgets::LdapClientSearch *ldapSearch);

Q_SIGNALS:
    void completionOrderChanged();

private:
    PIMCOMMONAKONADI_NO_EXPORT void rowsInserted(const QModelIndex &parent, int start, int end);
    PIMCOMMONAKONADI_NO_EXPORT void slotSelectionChanged();
    PIMCOMMONAKONADI_NO_EXPORT void slotMoveUp();
    PIMCOMMONAKONADI_NO_EXPORT void slotMoveDown();
    PIMCOMMONAKONADI_NO_EXPORT void addRecentAddressItem();
    PIMCOMMONAKONADI_NO_EXPORT void addCompletionItemForCollection(const QModelIndex &);
    PIMCOMMONAKONADI_NO_EXPORT void slotItemChanged();

    KConfig mConfig;
    QTreeWidget *mListView = nullptr;
    QPushButton *mUpButton = nullptr;
    QPushButton *mDownButton = nullptr;
    QAbstractItemModel *mCollectionModel = nullptr;
    KLDAPWidgets::LdapClientSearch *mLdapSearch = nullptr;

    int mDefaultValue = 60;
    bool mDirty = false;
};
}
