/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_private_export.h"
#include <QWidget>
class QComboBox;
namespace PimCommon
{
class PIMCOMMON_TESTS_EXPORT TranslatorConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureWidget(QWidget *parent = nullptr);
    ~TranslatorConfigureWidget() override;

private:
    void loadSettings();
    void saveSettings();
    QComboBox *const mEngine;
};
}
