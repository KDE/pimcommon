/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimcommontextgrammar_export.h"
#include <QDialog>
namespace PimCommonTextGrammar
{
class GrammalecteConfigWidget;
class PIMCOMMONTEXTGRAMMAR_EXPORT GrammalecteConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GrammalecteConfigDialog(QWidget *parent = nullptr, bool disableMessageBox = false);
    ~GrammalecteConfigDialog() override;

private:
    Q_DISABLE_COPY(GrammalecteConfigDialog)
    void writeConfig();
    void readConfig();
    GrammalecteConfigWidget *const mConfigWidget;
};
}
