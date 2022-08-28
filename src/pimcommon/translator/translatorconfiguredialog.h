/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "pimcommon_export.h"
#include <QDialog>
namespace PimCommon
{
class TranslatorConfigureWidget;
class PIMCOMMON_EXPORT TranslatorConfigureDialog : public QDialog
{
public:
    explicit TranslatorConfigureDialog(QWidget *parent = nullptr);
    ~TranslatorConfigureDialog() override;

private:
    TranslatorConfigureWidget *const mTranslatorConfigureWidget;
    void slotAccept();
    void readConfig();
    void writeConfig();
};
}
