/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef COMPLETIONORDERWIDGET_H
#define COMPLETIONORDERWIDGET_H

#include <QWidget>
#include "pimcommonakonadi_private_export.h"
#include <QDBusAbstractAdaptor>
#include <KConfig>

class QPushButton;
class QAbstractItemModel;
class QModelIndex;
class QTreeWidget;

namespace KLDAP {
class LdapClientSearch;
}

namespace PimCommon {
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
    virtual ~CompletionItem()
    {
    }

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
    ~CompletionOrderWidget();
    void save();

    KConfig *configFile();
    void loadCompletionItems();
    void setLdapClientSearch(KLDAP::LdapClientSearch *ldapSearch);

Q_SIGNALS:
    void completionOrderChanged();

private:
    void rowsInserted(const QModelIndex &parent, int start, int end);
    void slotSelectionChanged();
    void slotMoveUp();
    void slotMoveDown();
    void readConfig();
    void writeConfig();
    void addRecentAddressItem();
    void addCompletionItemForCollection(const QModelIndex &);
    void slotItemChanged();

    KConfig mConfig;
    QTreeWidget *mListView = nullptr;
    QPushButton *mUpButton = nullptr;
    QPushButton *mDownButton = nullptr;
    QAbstractItemModel *mCollectionModel = nullptr;
    KLDAP::LdapClientSearch *mLdapSearch = nullptr;

    int mDefaultValue = 60;
    bool mDirty = false;
};
}

#endif // COMPLETIONORDERWIDGET_H