/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QComboBox>

namespace PimCommon
{
/**
 * @brief The ContentTypeWidget class is a combobox allowing the
 * user to select one of the multiple collection types.
 *
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ContentTypeWidget : public QComboBox
{
    Q_OBJECT
public:
    explicit ContentTypeWidget(QWidget *parent = nullptr);
    ~ContentTypeWidget() override;

    void setCurrentItem(const QString &name);

    /// Label name that should be used in a QFormLayout with a ContentTypeWidget
    static QString labelName();
};
}
