/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "verifynewversionwidget.h"
#include "pimcommon_debug.h"
#include "verifynewversion/checknewversiondialog.h"
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
    QUrl url;
#if defined(Q_OS_WIN)
    url = QUrl(mUrls.value(VerifyNewVersionWidget::OsVersion::Windows));
#endif

#if defined(Q_OS_MACOS)
#ifdef Q_PROCESSOR_ARM_64
    url = QUrl(mUrls.value(VerifyNewVersionWidget::OsVersion::MacOsArm64));
#else
    url = QUrl(mUrls.value(VerifyNewVersionWidget::OsVersion::MacOs));
#endif
#endif
    if (!url.isEmpty()) {
        CheckNewVersionDialog dlg(nullptr);
        dlg.checkNewVersion();
        dlg.exec();
    }
}

#include "moc_verifynewversionwidget.cpp"
