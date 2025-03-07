/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  code based on kdenlive
*/

#include "needupdateversionwidget.h"
#include "pimcommon_debug.h"
#include <KLocalizedString>

using namespace PimCommon;
NeedUpdateVersionWidget::NeedUpdateVersionWidget(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setPosition(KMessageWidget::Header);
    setCloseButtonVisible(true);
    auto action = new QAction(i18nc("@action", "Disable version check"), this);
    addAction(action);
    connect(action, &QAction::triggered, this, &NeedUpdateVersionWidget::slotDisableVersionCheck);
}

NeedUpdateVersionWidget::~NeedUpdateVersionWidget() = default;

void NeedUpdateVersionWidget::setObsoleteVersion(NeedUpdateVersionUtils::ObsoleteVersion obsolete)
{
    if (PimCommon::NeedUpdateVersionUtils::checkVersion()) {
        switch (obsolete) {
        case NeedUpdateVersionUtils::ObsoleteVersion::Unknown:
            qCWarning(PIMCOMMON_LOG) << "Unknown value: seems to be a bug";
            break;
        case NeedUpdateVersionUtils::ObsoleteVersion::OlderThan6Months:
            setMessageType(KMessageWidget::Information);
            setText(i18n("Your version is older than 6 months, we encourage you to upgrade."));
            animatedShow();
            break;
        case NeedUpdateVersionUtils::ObsoleteVersion::OlderThan12Months:
            setMessageType(KMessageWidget::Warning);
            setText(i18n("Your version is older than 1 year, we strongly encourage you to upgrade."));
            animatedShow();
            break;
        case NeedUpdateVersionUtils::ObsoleteVersion::NotObsoleteYet:
            // It's ok
            break;
        }
    }
}

void NeedUpdateVersionWidget::slotDisableVersionCheck()
{
    PimCommon::NeedUpdateVersionUtils::disableCheckVersion();
    animatedHide();
}

#include "moc_needupdateversionwidget.cpp"
