/*
  SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QComboBox>

namespace PimCommon
{
class IncidencesForWidgetPrivate;
/*!
 * \class IncidencesForWidget
 * \brief The IncidencesForWidget class is used for configuring which users sharing this folder should get "busy" periods in their freebusy lists
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/IncidencesForWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT IncidencesForWidget : public QComboBox
{
    Q_OBJECT
public:
    /*!
     * Constructs an IncidencesForWidget.
     * @param parent The parent widget
     */
    explicit IncidencesForWidget(QWidget *parent = nullptr);
    /*!
     * Destructs the IncidencesForWidget.
     */
    ~IncidencesForWidget() override;

    /*!
     * Returns the label name for this widget.
     * @return The label text
     */
    static QString labelName();
};
}
