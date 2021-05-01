/*
 * SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "aclmanager.h"
#include "aclentrydialog_p.h"
#include "aclmodifyjob.h"
#include "aclutils_p.h"
#include "imapaclattribute.h"
#include "imapresourcesettings.h"
#include "pimcommonakonadi_debug.h"
#include "util/pimutil.h"

#include <AkonadiCore/CollectionFetchJob>
#include <AkonadiCore/ServerManager>

#include <KEmailAddress>
#include <KLocalizedString>
#include <KMessageBox>

#include <QAbstractListModel>
#include <QAction>
#include <QDBusInterface>
#include <QDBusReply>
#include <QItemSelectionModel>

using namespace PimCommon;

class AclModel : public QAbstractListModel
{
public:
    enum Role { UserIdRole = Qt::UserRole + 1, PermissionsRole, PermissionsTextRole };

    AclModel(QObject *parent = nullptr)
        : QAbstractListModel(parent)
    {
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (index.row() < 0 || index.row() >= mRights.count()) {
            return QVariant();
        }

        const QPair<QByteArray, KIMAP::Acl::Rights> right = mRights.at(index.row());
        switch (role) {
        case Qt::DisplayRole:
            return QStringLiteral("%1: %2").arg(QString::fromLatin1(right.first), AclUtils::permissionsToUserString(right.second));
        case UserIdRole:
            return QString::fromLatin1(right.first);
        case PermissionsRole:
            return QVariant(static_cast<int>(right.second));
        case PermissionsTextRole:
            return AclUtils::permissionsToUserString(right.second);
        default:
            return QVariant();
        }
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
    {
        if (index.row() < 0 || index.row() >= mRights.count()) {
            return false;
        }

        QPair<QByteArray, KIMAP::Acl::Rights> &right = mRights[index.row()];
        switch (role) {
        case UserIdRole:
            right.first = value.toByteArray();
            Q_EMIT dataChanged(index, index);
            return true;
        case PermissionsRole:
            right.second = static_cast<KIMAP::Acl::Rights>(value.toInt());
            Q_EMIT dataChanged(index, index);
            return true;
        default:
            return false;
        }

        return false;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        if (parent.isValid()) {
            return 0;
        } else {
            return mRights.count();
        }
    }

    void setRights(const QMap<QByteArray, KIMAP::Acl::Rights> &rights)
    {
        beginResetModel();

        mRights.clear();

        QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator it = rights.cbegin();
        const QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator itEnd = rights.cend();
        for (; it != itEnd; ++it) {
            mRights.append(qMakePair(it.key(), it.value()));
        }

        endResetModel();
    }

    QMap<QByteArray, KIMAP::Acl::Rights> rights() const
    {
        QMap<QByteArray, KIMAP::Acl::Rights> result;

        using RightPair = QPair<QByteArray, KIMAP::Acl::Rights>;
        for (const RightPair &right : qAsConst(mRights)) {
            result.insert(right.first, right.second);
        }

        return result;
    }

protected:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override
    {
        beginInsertRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i) {
            mRights.insert(row, qMakePair(QByteArray(), KIMAP::Acl::Rights()));
        }
        endInsertRows();

        return true;
    }

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override
    {
        beginRemoveRows(parent, row, row + count - 1);
        for (int i = 0; i < count; ++i) {
            mRights.remove(row, count);
        }
        endRemoveRows();

        return true;
    }

private:
    QVector<QPair<QByteArray, KIMAP::Acl::Rights>> mRights;
};

class Q_DECL_HIDDEN PimCommon::AclManager::Private
{
public:
    Private(AclManager *qq)
        : q(qq)
    {
        mAddAction = new QAction(i18n("Add Entry..."), q);
        q->connect(mAddAction, &QAction::triggered, q, [this]() {
            addAcl();
        });

        mEditAction = new QAction(i18n("Edit Entry..."), q);
        mEditAction->setEnabled(false);
        q->connect(mEditAction, &QAction::triggered, q, [this]() {
            editAcl();
        });

        mDeleteAction = new QAction(i18n("Remove Entry"), q);
        mDeleteAction->setEnabled(false);
        q->connect(mDeleteAction, &QAction::triggered, q, [this]() {
            deleteAcl();
        });

        mModel = new AclModel(q);

        mSelectionModel = new QItemSelectionModel(mModel);
        q->connect(mSelectionModel, &QItemSelectionModel::selectionChanged, q, [this]() {
            selectionChanged();
        });
    }

    ~Private()
    {
    }

    void selectionChanged()
    {
        const bool itemSelected = !mSelectionModel->selectedIndexes().isEmpty();

        bool canAdmin = (mUserRights & KIMAP::Acl::Admin);

        bool canAdminThisItem = canAdmin;
        if (canAdmin && itemSelected) {
            const QModelIndex index = mSelectionModel->selectedIndexes().first();
            const QString userId = index.data(AclModel::UserIdRole).toString();
            const KIMAP::Acl::Rights rights = static_cast<KIMAP::Acl::Rights>(index.data(AclModel::PermissionsRole).toInt());

            // Don't allow users to remove their own admin permissions - there's no way back
            if (mImapUserName == userId && (rights & KIMAP::Acl::Admin)) {
                canAdminThisItem = false;
            }
        }

        mAddAction->setEnabled(canAdmin);
        mEditAction->setEnabled(itemSelected && canAdminThisItem);
        mDeleteAction->setEnabled(itemSelected && canAdminThisItem);
    }

    void addAcl()
    {
        AclEntryDialog dlg;
        dlg.setWindowTitle(i18nc("@title:window", "Add ACL"));

        if (!dlg.exec()) {
            return;
        }
        const QString userId = dlg.userId();
        const QStringList lstAddresses = KEmailAddress::splitAddressList(userId);
        for (const QString &addr : lstAddresses) {
            if (mModel->insertRow(mModel->rowCount())) {
                const QModelIndex index = mModel->index(mModel->rowCount() - 1, 0);
                const QString extractedAddress = KEmailAddress::extractEmailAddress(addr);
                mModel->setData(index, extractedAddress, AclModel::UserIdRole);
                mModel->setData(index, static_cast<int>(dlg.permissions()), AclModel::PermissionsRole);

                mChanged = true;
            }
        }
    }

    void editAcl()
    {
        if (mEditAction->isEnabled()) {
            const QModelIndex index = mSelectionModel->selectedIndexes().first();
            const QString userId = index.data(AclModel::UserIdRole).toString();
            const KIMAP::Acl::Rights permissions = static_cast<KIMAP::Acl::Rights>(index.data(AclModel::PermissionsRole).toInt());

            AclEntryDialog dlg;
            dlg.setWindowTitle(i18nc("@title:window", "Edit ACL"));
            dlg.setUserId(userId);
            dlg.setPermissions(permissions);

            if (!dlg.exec()) {
                return;
            }
            const QStringList lstAddresses = KEmailAddress::splitAddressList(dlg.userId());
            if (lstAddresses.count() == 1) {
                mModel->setData(index, KEmailAddress::extractEmailAddress(lstAddresses.at(0)), AclModel::UserIdRole);
                mModel->setData(index, static_cast<int>(dlg.permissions()), AclModel::PermissionsRole);
                mChanged = true;
            } else {
                bool firstElement = true;
                for (const QString &addr : lstAddresses) {
                    if (firstElement) {
                        mModel->setData(index, KEmailAddress::extractEmailAddress(lstAddresses.at(0)), AclModel::UserIdRole);
                        mModel->setData(index, static_cast<int>(dlg.permissions()), AclModel::PermissionsRole);
                        firstElement = false;
                    } else {
                        if (mModel->insertRow(mModel->rowCount())) {
                            const QModelIndex rowindex = mModel->index(mModel->rowCount() - 1, 0);
                            mModel->setData(rowindex, KEmailAddress::extractEmailAddress(addr), AclModel::UserIdRole);
                            mModel->setData(rowindex, static_cast<int>(dlg.permissions()), AclModel::PermissionsRole);
                        }
                    }
                }
                mChanged = true;
            }
        }
    }

    void deleteAcl()
    {
        const QModelIndex index = mSelectionModel->selectedIndexes().first();
        const QString userId = index.data(AclModel::UserIdRole).toString();

        if (mImapUserName == userId) {
            if (KMessageBox::Cancel
                == KMessageBox::warningContinueCancel(nullptr,
                                                      i18n("Do you really want to remove your own permissions for this folder? "
                                                           "You will not be able to access it afterwards."),
                                                      i18n("Remove"))) {
                return;
            }
        } else {
            if (KMessageBox::Cancel
                == KMessageBox::warningContinueCancel(nullptr, i18n("Do you really want to remove these permissions for this folder?"), i18n("Remove"))) {
                return;
            }
        }

        mModel->removeRow(index.row(), QModelIndex());
        mChanged = true;
    }

    void setCollection(const Akonadi::Collection &collection)
    {
        mCollection = collection;
        mChanged = false;

        const auto attribute = collection.attribute<PimCommon::ImapAclAttribute>();
        const QMap<QByteArray, KIMAP::Acl::Rights> rights = attribute->rights();

        QString resource = collection.resource();
        if (resource.contains(QLatin1String("akonadi_kolabproxy_resource"))) {
            const QString basename = Akonadi::ServerManager::agentServiceName(Akonadi::ServerManager::Agent, QStringLiteral("akonadi_kolabproxy_resource"));

            QDBusInterface interface(basename, QStringLiteral("/KolabProxy"));
            if (interface.isValid()) {
                QDBusReply<QString> reply = interface.call(QStringLiteral("imapResourceForCollection"), collection.remoteId().toLongLong());
                if (reply.isValid()) {
                    resource = reply;
                }
            }
        }
        OrgKdeAkonadiImapSettingsInterface *imapSettingsInterface = PimCommon::Util::createImapSettingsInterface(resource);

        QString loginName;
        QString serverName;
        if (imapSettingsInterface && imapSettingsInterface->isValid()) {
            QDBusReply<QString> reply = imapSettingsInterface->userName();
            if (reply.isValid()) {
                loginName = reply;
            }

            reply = imapSettingsInterface->imapServer();
            if (reply.isValid()) {
                serverName = reply;
            }
        } else {
            qCDebug(PIMCOMMONAKONADI_LOG) << " collection has not imap as resources: " << collection.resource();
        }
        delete imapSettingsInterface;

        mImapUserName = loginName;
        if (!rights.contains(loginName.toUtf8())) {
            const QString guessedUserName = AclUtils::guessUserName(loginName, serverName);
            if (rights.contains(guessedUserName.toUtf8())) {
                mImapUserName = guessedUserName;
            }
        }

        mUserRights = rights[mImapUserName.toUtf8()];

        mModel->setRights(rights);
        selectionChanged();
    }

    AclManager *const q;
    AclModel *mModel = nullptr;
    QItemSelectionModel *mSelectionModel = nullptr;
    QAction *mAddAction = nullptr;
    QAction *mEditAction = nullptr;
    QAction *mDeleteAction = nullptr;

    Akonadi::Collection mCollection;
    QString mImapUserName;
    KIMAP::Acl::Rights mUserRights;
    bool mChanged = false;
};

AclManager::AclManager(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

AclManager::~AclManager()
{
    delete d;
}

void AclManager::setCollection(const Akonadi::Collection &collection)
{
    d->setCollection(collection);
    Q_EMIT collectionChanged(d->mCollection);
    Q_EMIT collectionCanBeAdministrated(d->mUserRights & KIMAP::Acl::Admin);
}

Akonadi::Collection AclManager::collection() const
{
    return d->mCollection;
}

QAbstractItemModel *AclManager::model() const
{
    return d->mModel;
}

QItemSelectionModel *AclManager::selectionModel() const
{
    return d->mSelectionModel;
}

QAction *AclManager::addAction() const
{
    return d->mAddAction;
}

QAction *AclManager::editAction() const
{
    return d->mEditAction;
}

QAction *AclManager::deleteAction() const
{
    return d->mDeleteAction;
}

void AclManager::save(bool recursive)
{
    if (!d->mCollection.isValid() || !d->mChanged) {
        return;
    }

    // refresh the collection, it might be outdated in the meantime
    auto job = new Akonadi::CollectionFetchJob(d->mCollection, Akonadi::CollectionFetchJob::Base);
    if (!job->exec()) {
        qCDebug(PIMCOMMONAKONADI_LOG) << " collection Fetch error" << job->errorString();
        return;
    }

    if (job->collections().isEmpty()) {
        qCDebug(PIMCOMMONAKONADI_LOG) << " collection list Fetched is Empty ";
        return;
    }

    d->mCollection = job->collections().at(0);

    d->mChanged = false;

    auto modifyAclJob = new PimCommon::AclModifyJob;
    modifyAclJob->setCurrentRight(d->mModel->rights());
    modifyAclJob->setTopLevelCollection(d->mCollection);
    modifyAclJob->setRecursive(recursive);
    modifyAclJob->start();
}

void AclManager::setChanged(bool b)
{
    d->mChanged = b;
}

#include "moc_aclmanager.cpp"
