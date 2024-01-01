/*
  SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/
#pragma once

#include <Akonadi/Collection>
#include <KIMAP/Acl>
#include <QObject>
class KJob;
namespace PimCommon
{
class ImapAclAttribute;
class AclModifyJob : public QObject
{
    Q_OBJECT
public:
    explicit AclModifyJob(QObject *parent = nullptr);
    ~AclModifyJob() override;

    void setTopLevelCollection(const Akonadi::Collection &topLevelCollection);
    void setRecursive(bool recursive);
    void start();

    void setCurrentRight(const QMap<QByteArray, KIMAP::Acl::Rights> &currentRight);

Q_SIGNALS:
    void searchContactDone();
    void searchNextContact();

private:
    void slotModifyDone(KJob *job);
    void slotFetchCollectionFinished(const Akonadi::Collection::List &collectionList);
    void slotFetchCollectionFailed();
    void changeAcl(const Akonadi::Collection &collection);
    void checkNewCollection();
    bool canAdministrate(const PimCommon::ImapAclAttribute *attribute, const Akonadi::Collection &collection) const;
    void searchContact();
    void slotModifyAcl();
    void slotGroupSearchResult(KJob *job);

    Akonadi::Collection mTopLevelCollection;
    Akonadi::Collection::List mRecursiveCollection;
    QMap<QByteArray, KIMAP::Acl::Rights> mNewRight;
    QMap<QByteArray, KIMAP::Acl::Rights> mCurrentRight;
    QMap<QByteArray, KIMAP::Acl::Rights>::const_iterator mIt;
    bool mRecursive = false;
    int mCurrentIndex = -1;
};
}
