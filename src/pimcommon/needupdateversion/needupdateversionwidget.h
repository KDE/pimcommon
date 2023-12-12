/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimcommon_export.h"
#include <KMessageWidget>
namespace PimCommon
{
/**
 * @brief The NeedUpdateVersionWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT NeedUpdateVersionWidget : public KMessageWidget
{
    Q_OBJECT
public:
    enum class ObsoleteVersion {
        Unknown,
        OlderThan6Months,
        OlderThan12Months,
    };
    explicit NeedUpdateVersionWidget(QWidget *parent = nullptr);
    ~NeedUpdateVersionWidget() override;

    void setObsoleteVersion(NeedUpdateVersionWidget::ObsoleteVersion obsolete);

private:
    PIMCOMMON_NO_EXPORT void slotDisableVersionCheck();
};
}
