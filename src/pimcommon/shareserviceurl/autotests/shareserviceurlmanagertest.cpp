/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "shareserviceurlmanagertest.h"
#include "../shareserviceurlmanager.h"
#include <KActionMenu>
#include <QMenu>
#include <QTest>
ShareServiceUrlManagerTest::ShareServiceUrlManagerTest(QObject *parent)
    : QObject(parent)
{
}

ShareServiceUrlManagerTest::~ShareServiceUrlManagerTest() = default;

void ShareServiceUrlManagerTest::shouldHaveDefaultValue()
{
    PimCommon::ShareServiceUrlManager manager;
    QVERIFY(manager.menu());
    QVERIFY(!manager.menu()->menu()->actions().isEmpty());

    // Based on 0 => we need to look at PimCommon::ShareServiceUrlManager::ServiceEndType
    QCOMPARE(manager.menu()->menu()->actions().count(), (static_cast<int>(PimCommon::ShareServiceUrlManager::ServiceEndType)));
}

void ShareServiceUrlManagerTest::shouldGenerateServiceUrl_data()
{
    QTest::addColumn<QString>("title");
    QTest::addColumn<QString>("link");
    QTest::addColumn<PimCommon::ShareServiceUrlManager::ServiceType>("serviceType");
    QTest::addColumn<QUrl>("output");
    // Url is valid ?
    QTest::addColumn<bool>("valid");
    QTest::newRow("no title no link") << QString() << QString() << PimCommon::ShareServiceUrlManager::Fbook << QUrl() << false;
    QTest::newRow("no title but valid link (facebook)") << QString() << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::Fbook
                                                        << QUrl(QStringLiteral("https://www.facebook.com/sharer.php?u=http://www.kde.org&t")) << true;
    QTest::newRow("title and valid link (facebook)") << QStringLiteral("kde") << QStringLiteral("http://www.kde.org")
                                                     << PimCommon::ShareServiceUrlManager::Fbook
                                                     << QUrl(QStringLiteral("https://www.facebook.com/sharer.php?u=http://www.kde.org&t=kde")) << true;

    QTest::newRow("no title but valid link (twitter)") << QString() << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::Twitter
                                                       << QUrl(QStringLiteral("https://twitter.com/share?url=http://www.kde.org&text")) << true;
    QTest::newRow("title and valid link (twitter)") << QStringLiteral("kde") << QStringLiteral("http://www.kde.org")
                                                    << PimCommon::ShareServiceUrlManager::Twitter
                                                    << QUrl(QStringLiteral("https://twitter.com/share?url=http://www.kde.org&text=kde")) << true;

    QTest::newRow("no title but valid link (mailto)") << QString() << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::MailTo
                                                      << QUrl(QStringLiteral("mailto:?subject&body=http://www.kde.org")) << true;
    QTest::newRow("title and valid link (mailto)") << QStringLiteral("kde") << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::MailTo
                                                   << QUrl(QStringLiteral("mailto:?subject=kde&body=http://www.kde.org")) << true;

    QTest::newRow("no title but valid link (linkedin)")
        << QString() << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::LinkedIn
        << QUrl(QStringLiteral("http://www.linkedin.com/shareArticle?mini=true&url=http://www.kde.org&title")) << true;
    QTest::newRow("title and valid link (linkedin)") << QStringLiteral("kde") << QStringLiteral("http://www.kde.org")
                                                     << PimCommon::ShareServiceUrlManager::LinkedIn
                                                     << QUrl(QStringLiteral("http://www.linkedin.com/shareArticle?mini=true&url=http://www.kde.org&title=kde"))
                                                     << true;

    QTest::newRow("no title but valid link (evernote)") << QString() << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::Evernote
                                                        << QUrl(QStringLiteral("https://www.evernote.com/clip.action?url=http://www.kde.org&title")) << true;
    QTest::newRow("title and valid link (evernote)") << QStringLiteral("kde") << QStringLiteral("http://www.kde.org")
                                                     << PimCommon::ShareServiceUrlManager::Evernote
                                                     << QUrl(QStringLiteral("https://www.evernote.com/clip.action?url=http://www.kde.org&title=kde")) << true;

    QTest::newRow("no title but valid link (pocket)") << QString() << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::Pocket
                                                      << QUrl(QStringLiteral("https://getpocket.com/save?url=http://www.kde.org&title")) << true;
    QTest::newRow("title and valid link (pocket)") << QStringLiteral("kde") << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::Pocket
                                                   << QUrl(QStringLiteral("https://getpocket.com/save?url=http://www.kde.org&title=kde")) << true;

    QTest::newRow("no title but valid link (livejournal)")
        << QString() << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::LiveJournal
        << QUrl(QStringLiteral("http://www.livejournal.com/update.bml?event=http://www.kde.org&subject")) << true;
    QTest::newRow("title and valid link (livejournal)")
        << QStringLiteral("kde") << QStringLiteral("http://www.kde.org") << PimCommon::ShareServiceUrlManager::LiveJournal
        << QUrl(QStringLiteral("http://www.livejournal.com/update.bml?event=http://www.kde.org&subject=kde")) << true;
}

void ShareServiceUrlManagerTest::shouldGenerateServiceUrl()
{
    QFETCH(QString, title);
    QFETCH(QString, link);
    QFETCH(PimCommon::ShareServiceUrlManager::ServiceType, serviceType);
    QFETCH(QUrl, output);
    QFETCH(bool, valid);

    PimCommon::ShareServiceUrlManager manager;
    const QUrl urlGenerated = manager.generateServiceUrl(link, title, serviceType);
    QCOMPARE(urlGenerated, output);
    QCOMPARE(urlGenerated.isValid(), valid);
}

QTEST_MAIN(ShareServiceUrlManagerTest)
