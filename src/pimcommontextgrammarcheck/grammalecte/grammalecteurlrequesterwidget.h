/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommontextgrammarcheckprivate_export.h"
#include <QWidget>
class QLineEdit;
namespace PimCommonTextGrammarCheck
{
class PIMCOMMONTEXTGRAMMARCHECK_TESTS_EXPORT GrammalecteUrlRequesterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammalecteUrlRequesterWidget(QWidget *parent = nullptr);
    ~GrammalecteUrlRequesterWidget() override;

    void setPath(const QString &path);
    Q_REQUIRED_RESULT QString path() const;

    void setPlaceholderText(const QString &text);

private:
    QLineEdit *const mLineEdit;
};
}
