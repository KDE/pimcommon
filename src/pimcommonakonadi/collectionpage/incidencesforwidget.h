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
 * \brief The IncidencesForWidget class is used for configuring which
 * users sharing this folder should get "busy" periods in their freebusy
 * lists.
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT IncidencesForWidget : public QComboBox
{
    Q_OBJECT
public:
    /*!
     */
    explicit IncidencesForWidget(QWidget *parent = nullptr);
    /*!
     */
    ~IncidencesForWidget() override;

    /// Label name of the combobox.
    /*!
     */
    static QString labelName();
};
}
