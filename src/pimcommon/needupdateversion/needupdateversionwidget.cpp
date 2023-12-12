/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "needupdateversionwidget.h"
#include "pimcommon_debug.h"
#include <KLocalizedString>

using namespace PimCommon;
NeedUpdateVersionWidget::NeedUpdateVersionWidget(QWidget *parent)
    : KMessageWidget(parent)
{
}

NeedUpdateVersionWidget::~NeedUpdateVersionWidget() = default;

void NeedUpdateVersionWidget::setObsoleteVersion(ObsoleteVersion obsolete)
{
    switch (obsolete) {
    case ObsoleteVersion::Unknown:
        qCWarning(PIMCOMMON_LOG) << "Unknown value: seems to be a bug";
        break;
    case ObsoleteVersion::OlderThan6Months:
        setMessageType(KMessageWidget::Information);
        setText(i18n("Your version is older than 6 months, we encourage you to upgrade"));
        animatedShow();
        break;
    case ObsoleteVersion::OlderThan12Months:
        setMessageType(KMessageWidget::Warning);
        setText(i18n("Your version is older than 1 year, we strongly encourage you to upgrade"));
        animatedShow();
        break;
    }
}

#include "moc_needupdateversionwidget.cpp"
