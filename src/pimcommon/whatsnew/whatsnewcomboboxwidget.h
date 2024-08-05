/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QWidget>
class QComboBox;
namespace PimCommon
{
class PIMCOMMON_EXPORT WhatsNewComboBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WhatsNewComboBoxWidget(QWidget *parent = nullptr);
    ~WhatsNewComboBoxWidget() override;

    void addVersion(const QString &name, int identifier);

    void initializeVersion(int type);

Q_SIGNALS:
    void versionChanged(int type);

private:
    PIMCOMMON_NO_EXPORT void slotCurrentIndexChanged(int index);
    QComboBox *const mVersionComboBox;
};
}
