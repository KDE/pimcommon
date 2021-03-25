/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QWidget>

namespace PimCommon
{
class IncidencesForWidgetPrivate;
/**
 * @brief The IncidencesForWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT IncidencesForWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IncidencesForWidget(QWidget *parent = nullptr);
    ~IncidencesForWidget() override;

    Q_REQUIRED_RESULT int currentIndex() const;
    void setCurrentIndex(int index);

Q_SIGNALS:
    void currentIndexChanged(int value);

private:
    IncidencesForWidgetPrivate *const d;
};
}

