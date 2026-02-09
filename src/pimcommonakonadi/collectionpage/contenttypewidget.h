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
/*!
 * \class PimCommon::ContentTypeWidget
 * \brief The ContentTypeWidget class provides a combobox for selecting collection types
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/ContentTypeWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ContentTypeWidget : public QComboBox
{
    Q_OBJECT
public:
    /*!
     * Constructs a ContentTypeWidget.
     * @param parent The parent widget
     */
    explicit ContentTypeWidget(QWidget *parent = nullptr);
    /*!
     * Destructs the ContentTypeWidget.
     */
    ~ContentTypeWidget() override;

    /*!
     * Sets the current item by name.
     * @param name The name of the content type to select
     */
    void setCurrentItem(const QString &name);

    /*!
     * Returns the label name for use in a QFormLayout.
     * @return The label text
     */
    static QString labelName();
};
}
