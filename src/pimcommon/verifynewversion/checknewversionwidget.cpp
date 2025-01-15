/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checknewversionwidget.h"
#include "needupdateversion/needupdatecheckexistingnewversionjob.h"
#include "needupdateversion/needupdateversionutils.h"
#include "pimcommon_debug.h"
#include <KLocalizedString>
#include <QDesktopServices>
#include <QLabel>
#include <QVBoxLayout>

using namespace PimCommon;
CheckNewVersionWidget::CheckNewVersionWidget(QWidget *parent)
    : QWidget{parent}
    , mCheckVersionResultLabel(new QLabel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mCheckVersionResultLabel->setObjectName(QStringLiteral("mCheckVersionResultLabel"));
    mCheckVersionResultLabel->setWordWrap(true);
    mCheckVersionResultLabel->setOpenExternalLinks(true);
    mainLayout->addWidget(mCheckVersionResultLabel);
}

CheckNewVersionWidget::~CheckNewVersionWidget() = default;

void CheckNewVersionWidget::checkNewVersion()
{
    auto job = new NeedUpdateCheckExistingNewVersionJob(this);
    job->setUrl(mUrl);
    job->setCompileDate(NeedUpdateVersionUtils::compileDate());
    connect(job, &NeedUpdateCheckExistingNewVersionJob::foundNewVersion, this, &CheckNewVersionWidget::slotFoundNewVersion);
    job->start();
}

void CheckNewVersionWidget::setUrl(const QUrl &url)
{
    mUrl = url;
}

void CheckNewVersionWidget::slotFoundNewVersion(bool found)
{
    if (found) {
        mCheckVersionResultLabel->setTextFormat(Qt::RichText);
        mCheckVersionResultLabel->setText(i18n("A new version found. Click <a href=\"%1\">here</a> for downloading it.", mUrl.toString()));
        connect(mCheckVersionResultLabel, &QLabel::linkActivated, this, [](const QString &url) {
            if (!QDesktopServices::openUrl(QUrl(url))) {
                qCWarning(PIMCOMMON_LOG) << "Impossible to open url: " << url;
            }
        });
    } else {
        mCheckVersionResultLabel->setText(i18n("No new version found."));
    }
}

#include "moc_checknewversionwidget.cpp"
