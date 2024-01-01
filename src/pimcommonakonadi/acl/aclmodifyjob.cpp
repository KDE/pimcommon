/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "aclmodifyjob.h"
#include "aclutils_p.h"
#include "imapresourcesettings.h"
#include "pimcommonakonadi_debug.h"
#include "util/pimutil.h"
#include <Akonadi/ServerManager>
#include <KEmailAddress>

#include "imapaclattribute.h"

#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/CollectionModifyJob>
#include <Akonadi/ContactGroupExpandJob>
#include <Akonadi/ContactGroupSearchJob>
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <KMessageBox>
#include <QDBusInterface>
#include <QDBusReply>

using namespace PimCommon;
// #define SEARCHCONTACT_AKONADI 1

AclModifyJob::AclModifyJob(QObject *parent)
    : QObject(parent)
{
    connect(this, &AclModifyJob::searchContactDone, this, &AclModifyJob::slotModifyAcl);
    connect(this, &AclModifyJob::searchNextContact, this, &AclModifyJob::searchContact);
}

AclModifyJob::~AclModifyJob() = default;

void AclModifyJob::searchContact()
{
    const QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator itEnd = mCurrentRight.cend();
    if (mIt != itEnd) {
        auto searchJob = new Akonadi::ContactGroupSearchJob(this);
        searchJob->setQuery(Akonadi::ContactGroupSearchJob::Name, QString::fromLatin1(mIt.key()));
        searchJob->setLimit(1);
        connect(searchJob, &Akonadi::ContactGroupSearchJob::result, this, &AclModifyJob::slotGroupSearchResult);
    } else {
        Q_EMIT searchContactDone();
    }
}

void AclModifyJob::slotGroupSearchResult(KJob *job)
{
    auto searchJob = qobject_cast<Akonadi::ContactGroupSearchJob *>(job);
    if (!searchJob->contactGroups().isEmpty()) { // it has been a distribution list
        auto expandJob = new Akonadi::ContactGroupExpandJob(searchJob->contactGroups().at(0), this);
        if (expandJob->exec()) {
            const KContacts::Addressee::List lstContacts = expandJob->contacts();
            for (const KContacts::Addressee &contact : lstContacts) {
                const QByteArray rawEmail = KEmailAddress::extractEmailAddress(contact.preferredEmail().toUtf8());
                if (!rawEmail.isEmpty()) {
                    mNewRight[rawEmail] = mIt.value();
                }
            }
        }
    } else { // it has been a normal contact
        const QByteArray rawEmail = KEmailAddress::extractEmailAddress(mIt.key());
        if (!rawEmail.isEmpty()) {
            mNewRight[rawEmail] = mIt.value();
        }
    }
    ++mIt;
    Q_EMIT searchNextContact();
}

void AclModifyJob::start()
{
    if (!mTopLevelCollection.isValid()) {
        deleteLater();
        return;
    }
#ifdef SEARCHCONTACT_AKONADI
    mIt = mCurrentRight.cbegin();
    searchContact();
#else
    const QMap<QByteArray, KIMAP::Acl::Rights> rights = mCurrentRight;
    QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator it = rights.cbegin();
    const QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator itEnd = rights.cend();
    for (; it != itEnd; ++it) {
        const QByteArray rawEmail = KEmailAddress::extractEmailAddress(it.key());
        if (!rawEmail.isEmpty()) {
            mNewRight[rawEmail] = it.value();
        }
    }
    slotModifyAcl();
#endif
}

void AclModifyJob::slotModifyAcl()
{
    mCurrentIndex = 0;
    if (mRecursive) {
        auto job = new Akonadi::CollectionFetchJob(mTopLevelCollection, Akonadi::CollectionFetchJob::Recursive, this);
        job->fetchScope().setAncestorRetrieval(Akonadi::CollectionFetchScope::All);
        connect(job, &Akonadi::CollectionFetchJob::finished, this, [this](KJob *job) {
            if (job->error()) {
                qCWarning(PIMCOMMONAKONADI_LOG) << job->errorString();
                slotFetchCollectionFailed();
            } else {
                auto fetch = static_cast<Akonadi::CollectionFetchJob *>(job);
                slotFetchCollectionFinished(fetch->collections());
            }
        });
    } else {
        changeAcl(mTopLevelCollection);
    }
}

bool AclModifyJob::canAdministrate(const PimCommon::ImapAclAttribute *attribute, const Akonadi::Collection &collection) const
{
    if (!attribute || !collection.isValid()) {
        return false;
    }
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
    return rights[imapUserName.toUtf8()] & KIMAP::Acl::Admin;
}

void AclModifyJob::setCurrentRight(const QMap<QByteArray, KIMAP::Acl::Rights> &currentRight)
{
    mCurrentRight = currentRight;
}

void AclModifyJob::changeAcl(const Akonadi::Collection &collection)
{
    if (collection.hasAttribute<PimCommon::ImapAclAttribute>()) {
        Akonadi::Collection mutableCollection = collection;
        auto attribute = mutableCollection.attribute<PimCommon::ImapAclAttribute>();
        if (canAdministrate(attribute, mutableCollection)) {
            attribute->setRights(mNewRight);
            auto modifyJob = new Akonadi::CollectionModifyJob(mutableCollection);
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
            const auto attribute = col.attribute<PimCommon::ImapAclAttribute>();
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
                                               i18nc("@title:window", "Apply Permissions"))
        != KMessageBox::Continue) {
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

#include "moc_aclmodifyjob.cpp"
