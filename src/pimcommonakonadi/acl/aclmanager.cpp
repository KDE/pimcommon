/*
 * Copyright (c) 2010 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
 * Copyright (c) 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "aclmanager.h"
#include "aclentrydialog_p.h"
#include "aclutils_p.h"
#include "aclmodifyjob.h"
#include "imapaclattribute.h"
#include "imapresourcesettings.h"
#include "pimcommonakonadi_debug.h"
#include "util/pimutil.h"

#include <AkonadiCore/CollectionFetchJob>
#include <AkonadiCore/ServerManager>
#include <Akonadi/Contact/ContactGroupExpandJob>
#include <Akonadi/Contact/ContactGroupSearchJob>

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
    enum Role {
        UserIdRole = Qt::UserRole + 1,
        PermissionsRole,
        PermissionsTextRole
    };

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
            return QStringLiteral("%1: %2").
                   arg(QString::fromLatin1(right.first), AclUtils::permissionsToUserString(right.second));
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

        QPair<QByteArray, KIMAP::Acl::Rights> &right = mRights[ index.row() ];
        switch (role) {
        case UserIdRole:
            right.first = value.toByteArray();
            Q_EMIT dataChanged(index, index);
            return true;
            break;
        case PermissionsRole:
            right.second = static_cast<KIMAP::Acl::Rights>(value.toInt());
            Q_EMIT dataChanged(index, index);
            return true;
            break;
        default:
            return false;
            break;
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

        typedef QPair<QByteArray, KIMAP::Acl::Rights> RightPair;
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
    QVector<QPair<QByteArray, KIMAP::Acl::Rights> > mRights;
};

class Q_DECL_HIDDEN PimCommon::AclManager::Private
{
public:
    Private(AclManager *qq)
        : q(qq)
        , mChanged(false)
    {
        mAddAction = new QAction(i18n("Add Entry..."), q);
        q->connect(mAddAction, SIGNAL(triggered(bool)),
                   q, SLOT(addAcl()));

        mEditAction = new QAction(i18n("Edit Entry..."), q);
        mEditAction->setEnabled(false);
        q->connect(mEditAction, SIGNAL(triggered(bool)),
                   q, SLOT(editAcl()));

        mDeleteAction = new QAction(i18n("Remove Entry"), q);
        mDeleteAction->setEnabled(false);
        q->connect(mDeleteAction, SIGNAL(triggered(bool)),
                   q, SLOT(deleteAcl()));

        mModel = new AclModel(q);

        mSelectionModel = new QItemSelectionModel(mModel);
        q->connect(mSelectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                   q, SLOT(selectionChanged()));
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
            const KIMAP::Acl::Rights rights
                = static_cast<KIMAP::Acl::Rights>(index.data(AclModel::PermissionsRole).toInt());

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
        dlg.setWindowTitle(i18n("Add ACL"));

        if (!dlg.exec()) {
            return;
        }

        if (mModel->insertRow(mModel->rowCount())) {
            const QModelIndex index = mModel->index(mModel->rowCount() - 1, 0);
            mModel->setData(index, dlg.userId(), AclModel::UserIdRole);
            mModel->setData(index, static_cast<int>(dlg.permissions()), AclModel::PermissionsRole);

            mChanged = true;
        }
    }

    void editAcl()
    {
        if (mEditAction->isEnabled()) {
            const QModelIndex index = mSelectionModel->selectedIndexes().first();
            const QString userId = index.data(AclModel::UserIdRole).toString();
            const KIMAP::Acl::Rights permissions
                = static_cast<KIMAP::Acl::Rights>(index.data(AclModel::PermissionsRole).toInt());

            AclEntryDialog dlg;
            dlg.setWindowTitle(i18n("Edit ACL"));
            dlg.setUserId(userId);
            dlg.setPermissions(permissions);

            if (!dlg.exec()) {
                return;
            }

            mModel->setData(index, dlg.userId(), AclModel::UserIdRole);
            mModel->setData(index, static_cast<int>(dlg.permissions()), AclModel::PermissionsRole);
            mChanged = true;
        }
    }

    void deleteAcl()
    {
        const QModelIndex index = mSelectionModel->selectedIndexes().first();
        const QString userId = index.data(AclModel::UserIdRole).toString();

        if (mImapUserName == userId) {
            if (KMessageBox::Cancel == KMessageBox::warningContinueCancel(
                    nullptr,
                    i18n("Do you really want to remove your own permissions for this folder? "
                         "You will not be able to access it afterwards."),
                    i18n("Remove"))) {
                return;
            }
        } else {
            if (KMessageBox::Cancel == KMessageBox::warningContinueCancel(
                    nullptr,
                    i18n("Do you really want to remove these permissions for this folder?"),
                    i18n("Remove"))) {
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

        const PimCommon::ImapAclAttribute *attribute
            = collection.attribute<PimCommon::ImapAclAttribute>();
        const QMap<QByteArray, KIMAP::Acl::Rights> rights = attribute->rights();

        QString resource = collection.resource();
        if (resource.contains(QStringLiteral("akonadi_kolabproxy_resource"))) {

            const QString basename = Akonadi::ServerManager::agentServiceName(Akonadi::ServerManager::Agent,
                                                                        QStringLiteral("akonadi_kolabproxy_resource"));

            QDBusInterface interface(basename, QStringLiteral("/KolabProxy"));
            if (interface.isValid()) {
                QDBusReply<QString> reply = interface.call(QStringLiteral("imapResourceForCollection"), collection.remoteId().toLongLong());
                if (reply.isValid()) {
                    resource = reply;
                }
            }
        }
        OrgKdeAkonadiImapSettingsInterface *imapSettingsInterface
            = PimCommon::Util::createImapSettingsInterface(resource);

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

        mUserRights = rights[ mImapUserName.toUtf8() ];

        mModel->setRights(rights);
        selectionChanged();
    }

    AclManager *q = nullptr;
    AclModel *mModel = nullptr;
    QItemSelectionModel *mSelectionModel = nullptr;
    QAction *mAddAction = nullptr;
    QAction *mEditAction = nullptr;
    QAction *mDeleteAction = nullptr;

    Akonadi::Collection mCollection;
    QString mImapUserName;
    KIMAP::Acl::Rights mUserRights;
    bool mChanged;
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
    Akonadi::CollectionFetchJob *job
        = new Akonadi::CollectionFetchJob(d->mCollection, Akonadi::CollectionFetchJob::Base);
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

    QMap<QByteArray, KIMAP::Acl::Rights> newRights;

    const QMap<QByteArray, KIMAP::Acl::Rights> rights = d->mModel->rights();
    QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator it = rights.cbegin();
    const QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator itEnd = rights.cend();
    for (; it != itEnd; ++it) {
        // we can use job->exec() here, it is not a hot path
        Akonadi::ContactGroupSearchJob *searchJob = new Akonadi::ContactGroupSearchJob(this);
        searchJob->setQuery(Akonadi::ContactGroupSearchJob::Name, QString::fromLatin1(it.key()));
        searchJob->setLimit(1);
        if (!searchJob->exec()) {
            continue;
        }

        if (!searchJob->contactGroups().isEmpty()) {   // it has been a distribution list
            Akonadi::ContactGroupExpandJob *expandJob
                = new Akonadi::ContactGroupExpandJob(searchJob->contactGroups().at(0), this);
            if (expandJob->exec()) {
                const KContacts::Addressee::List lstContacts = expandJob->contacts();
                for (const KContacts::Addressee &contact : lstContacts) {
                    const QByteArray rawEmail
                        = KEmailAddress::extractEmailAddress(contact.preferredEmail().toUtf8());
                    if (!rawEmail.isEmpty()) {
                        newRights[ rawEmail ] = it.value();
                    }
                }
            }
        } else { // it has been a normal contact
            const QByteArray rawEmail = KEmailAddress::extractEmailAddress(it.key());
            if (!rawEmail.isEmpty()) {
                newRights[ rawEmail ] = it.value();
            }
        }
    }
    PimCommon::AclModifyJob *modifyAclJob = new PimCommon::AclModifyJob;
    modifyAclJob->setNewRights(newRights);
    modifyAclJob->setTopLevelCollection(d->mCollection);
    modifyAclJob->setRecursive(recursive);
    modifyAclJob->start();
}

void AclManager::setChanged(bool b)
{
    d->mChanged = b;
}

#include "moc_aclmanager.cpp"
