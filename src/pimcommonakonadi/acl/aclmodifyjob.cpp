/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "aclmodifyjob.h"
#include "imapresourcesettings.h"
#include "util/pimutil.h"
#include "aclutils_p.h"
#include "pimcommonakonadi_debug.h"
#include <AkonadiCore/ServerManager>
#include <KEmailAddress>

#include "imapaclattribute.h"
#include "job/fetchrecursivecollectionsjob.h"
#include <KMessageBox>
#include <KLocalizedString>
#include <QDBusInterface>
#include <QDBusReply>
#include <AkonadiCore/CollectionModifyJob>

using namespace PimCommon;

AclModifyJob::AclModifyJob(QObject *parent)
    : QObject(parent)
{
}

AclModifyJob::~AclModifyJob()
{
}

void AclModifyJob::searchContact()
{
    QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator it = mCurrentRight.cbegin();
    const QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator itEnd = mCurrentRight.cend();
    for (; it != itEnd; ++it) {
#if 0 //BUG in searchjob
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
                        mNewRight[ rawEmail ] = it.value();
                    }
                }
            }
        } else { // it has been a normal contact
#endif
            const QByteArray rawEmail = KEmailAddress::extractEmailAddress(it.key());
            if (!rawEmail.isEmpty()) {
                mNewRight[ rawEmail ] = it.value();
            }
        //}
    }

}

void AclModifyJob::start()
{
    if (!mTopLevelCollection.isValid()) {
        deleteLater();
        return;
    }
    searchContact();

    mCurrentIndex = 0;
    if (mRecursive) {
        PimCommon::FetchRecursiveCollectionsJob *fetchJob = new PimCommon::FetchRecursiveCollectionsJob(this);
        fetchJob->setTopCollection(mTopLevelCollection);
        connect(fetchJob, &FetchRecursiveCollectionsJob::fetchCollectionFailed, this, &AclModifyJob::slotFetchCollectionFailed);
        connect(fetchJob, &FetchRecursiveCollectionsJob::fetchCollectionFinished, this, &AclModifyJob::slotFetchCollectionFinished);
        fetchJob->start();
    } else {
        changeAcl(mTopLevelCollection);
    }
}

bool AclModifyJob::canAdministrate(PimCommon::ImapAclAttribute *attribute, const Akonadi::Collection &collection) const
{
    if (!attribute || !collection.isValid()) {
        return false;
    }
    const QMap<QByteArray, KIMAP::Acl::Rights> rights = attribute->rights();

    QString resource = collection.resource();
    if (resource.contains(QLatin1String("akonadi_kolabproxy_resource"))) {
        const QString basename = Akonadi::ServerManager::agentServiceName(Akonadi::ServerManager::Agent,
                                                                          QStringLiteral("akonadi_kolabproxy_resource"));
        QDBusInterface interface(basename, QLatin1String("/KolabProxy"));
        if (interface.isValid()) {
            QDBusReply<QString> reply = interface.call(QLatin1String("imapResourceForCollection"), collection.remoteId().toLongLong());
            if (reply.isValid()) {
                resource = reply;
            }
        }
    }
    OrgKdeAkonadiImapSettingsInterface *imapSettingsInterface
        = PimCommon::Util::createImapSettingsInterface(resource);

    QString loginName;
    QString serverName;
    if (imapSettingsInterface->isValid()) {
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

    QString imapUserName = loginName;
    if (!rights.contains(loginName.toUtf8())) {
        const QString guessedUserName = AclUtils::guessUserName(loginName, serverName);
        if (rights.contains(guessedUserName.toUtf8())) {
            imapUserName = guessedUserName;
        }
    }
    return rights[ imapUserName.toUtf8() ] & KIMAP::Acl::Admin;
}

void AclModifyJob::setCurrentRight(const QMap<QByteArray, KIMAP::Acl::Rights> &currentRight)
{
    mCurrentRight = currentRight;
}

void AclModifyJob::changeAcl(const Akonadi::Collection &collection)
{
    if (collection.hasAttribute<PimCommon::ImapAclAttribute>()) {
        PimCommon::ImapAclAttribute *attribute = collection.attribute<PimCommon::ImapAclAttribute>();
        if (canAdministrate(attribute, collection)) {
            attribute->setRights(mNewRight);
            Akonadi::CollectionModifyJob *modifyJob = new Akonadi::CollectionModifyJob(collection);
            connect(modifyJob, &KJob::result, this, &AclModifyJob::slotModifyDone);
        }
    } else {
        checkNewCollection();
    }
}

void AclModifyJob::checkNewCollection()
{
    mCurrentIndex++;
    if (mCurrentIndex < mRecursiveCollection.count()) {
        changeAcl(mRecursiveCollection.at(mCurrentIndex));
    } else {
        deleteLater();
    }
}

void AclModifyJob::slotModifyDone(KJob *job)
{
    if (job->error()) {
        qCDebug(PIMCOMMONAKONADI_LOG) << " Error during modify collection " << job->errorString();
    }
    checkNewCollection();
}

void AclModifyJob::slotFetchCollectionFinished(const Akonadi::Collection::List &collectionList)
{
    QStringList folderNames;
    for (const Akonadi::Collection &col : collectionList) {
        if (col.hasAttribute<PimCommon::ImapAclAttribute>()) {
            PimCommon::ImapAclAttribute *attribute = col.attribute<PimCommon::ImapAclAttribute>();
            if (canAdministrate(attribute, col)) {
                QString fullName;
                bool parentFound;
                Akonadi::Collection cur = col;
                do {
                    parentFound = false;
                    // parentCollection() only returns the ID, but we have the
                    // collection in our list already because we've recursively
                    // fetched. So look it up in our list.
                    for (const Akonadi::Collection &it : collectionList) {
                        if (it.id() == cur.id()) {
                            fullName = QLatin1String("/") + it.displayName() + fullName;
                            parentFound = true;
                            cur = cur.parentCollection();
                            break;
                        }
                    }
                } while (parentFound);
                // Remove leading slash
                folderNames << fullName.right(fullName.size() - 1);
            } else {
                qCDebug(PIMCOMMONAKONADI_LOG) << "AclModifyJob: No rights to administer " << col.name();
            }
        } else {
            qCDebug(PIMCOMMONAKONADI_LOG) << "AclModifyJob: Collection " << col.name() << "has no ACL.";
        }
    }
    folderNames.sort();
    if (KMessageBox::warningContinueCancelList(nullptr,
                                               i18n("Do you really want to apply the folder's permissions to these subfolders?"),
                                               folderNames,
                                               i18n("Apply Permissions")) != KMessageBox::Continue) {
        deleteLater();
        qCDebug(PIMCOMMONAKONADI_LOG) << "AclModifyJob: User canceled .";
        return;
    }
    mRecursiveCollection = collectionList;
    changeAcl(mTopLevelCollection);
}

void AclModifyJob::slotFetchCollectionFailed()
{
    qCDebug(PIMCOMMONAKONADI_LOG) << "fetch collection failed";
    deleteLater();
}

void AclModifyJob::setTopLevelCollection(const Akonadi::Collection &topLevelCollection)
{
    mTopLevelCollection = topLevelCollection;
}

void AclModifyJob::setRecursive(bool recursive)
{
    mRecursive = recursive;
}
