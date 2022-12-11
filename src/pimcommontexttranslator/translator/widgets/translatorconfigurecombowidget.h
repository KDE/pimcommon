/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommontexttranslator_export.h"
#include <QWidget>
namespace PimCommonTextTranslator
{
class PIMCOMMONTEXTTRANSLATOR_EXPORT TranslatorConfigureComboWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureComboWidget(QWidget *parent = nullptr);
    ~TranslatorConfigureComboWidget() override;
};
}
