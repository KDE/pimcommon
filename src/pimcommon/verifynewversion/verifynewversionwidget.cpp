/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "verifynewversionwidget.h"
#include "verifynewversionutils.h"
#include <KLocalizedString>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
using namespace PimCommon;
using namespace Qt::Literals::StringLiterals;
VerifyNewVersionWidget::VerifyNewVersionWidget(QObject *parent)
    : QObject{parent}
{
}

VerifyNewVersionWidget::~VerifyNewVersionWidget() = default;

bool VerifyNewVersionWidget::canVerifyNewVersion() const
{
    return VerifyNewVersionUtils::canVerifyNewVersion();
}

QAction *VerifyNewVersionWidget::verifyNewVersionAction()
{
    if (!mVerifyNewVersionAction) {
        // TODO add icon
        mVerifyNewVersionAction = new QAction(i18n("Check New Version"), this);
        connect(mVerifyNewVersionAction, &QAction::triggered, this, &VerifyNewVersionWidget::slotVerifyNewVersion);
    }
    return mVerifyNewVersionAction;
}

void VerifyNewVersionWidget::addOsUrlInfo(OsVersion os, const QString &url)
{
    mUrls.insert(os, url);
}

void VerifyNewVersionWidget::slotVerifyNewVersion()
{
    const QUrl url = VerifyNewVersionUtils::newVersionUrl();
    if (!url.isEmpty()) {
        QDesktopServices::openUrl(url);
    }
}

#include "moc_verifynewversionwidget.cpp"
