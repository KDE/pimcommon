/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommontexttranslator_export.h"
#include <QWidget>
class QComboBox;
class QToolButton;
namespace PimCommonTextTranslator
{
class TranslatorConfigureLanguageListWidget;
class PIMCOMMONTEXTTRANSLATOR_EXPORT TranslatorConfigureListsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureListsWidget(QWidget *parent = nullptr);
    ~TranslatorConfigureListsWidget() override;

    void save();
    void load();

private:
    void fillEngine();
    void slotEngineChanged(int index);
    void slotConfigureEngine();
    QComboBox *const mEngine;
    QToolButton *const mConfigureEngine;
    PimCommonTextTranslator::TranslatorConfigureLanguageListWidget *const mFromLanguageWidget;
    PimCommonTextTranslator::TranslatorConfigureLanguageListWidget *const mToLanguageWidget;
};
}
