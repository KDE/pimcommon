/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontextgrammar_export.h"
#include <QComboBox>
namespace PimCommonTextGrammar
{
class LanguageInfo;
class PIMCOMMONTEXTGRAMMAR_EXPORT LanguageToolComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit LanguageToolComboBox(QWidget *parent = nullptr);
    ~LanguageToolComboBox() override;

    void setLanguage(const QString &str);
    Q_REQUIRED_RESULT QString language() const;

    void fillComboBox(const QVector<LanguageInfo> &info);

private:
    void fillComboBox();
    Q_DISABLE_COPY(LanguageToolComboBox)
};
}
