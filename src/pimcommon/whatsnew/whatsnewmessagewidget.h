/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "pimcommon_export.h"
#include <KMessageWidget>
#include <PimCommon/WhatsNewInfo>

#include <QCoreApplication>

namespace PimCommon
{
class PIMCOMMON_EXPORT WhatsNewMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    explicit WhatsNewMessageWidget(QWidget *parent = nullptr, const QString &applicationName = QCoreApplication::applicationName());
    ~WhatsNewMessageWidget() override;

    void setWhatsNewInfos(const QList<PimCommon::WhatsNewInfo> &infos);

private:
    PIMCOMMON_NO_EXPORT void slotLinkActivated(const QString &contents);
    QList<PimCommon::WhatsNewInfo> mWhatsNewInfos;
    QString mApplicationName;
};
}
