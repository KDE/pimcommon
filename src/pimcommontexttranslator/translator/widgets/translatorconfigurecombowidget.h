/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWidget>
namespace PimCommonTextTranslator
{
class TranslatorConfigureComboWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureComboWidget(QWidget *parent = nullptr);
    ~TranslatorConfigureComboWidget() override;
};
}
