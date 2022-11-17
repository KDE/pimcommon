/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "grammarerror.h"
#include "pimcommontextgrammarcheck_export.h"
#include <QTextEdit>
namespace PimCommonTextGrammarCheck
{
class GrammarAction;
class PIMCOMMONTEXTGRAMMARCHECK_EXPORT GrammarResultTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit GrammarResultTextEdit(QWidget *parent = nullptr);
    ~GrammarResultTextEdit() override;

    void applyGrammarResult(const QVector<GrammarError> &infos);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    bool event(QEvent *ev) override;
Q_SIGNALS:
    void replaceText(const PimCommonTextGrammarCheck::GrammarAction &act);
    void checkAgain();
    void closeChecker();
    void configure();

private:
    Q_DISABLE_COPY(GrammarResultTextEdit)
    void slotReplaceWord(const PimCommonTextGrammarCheck::GrammarAction &act, const QString &replacementWord);
    void slotOpenGrammarUrlInfo(const QString &url);
    void generalPaletteChanged();
    QColor mTextColor;
    QColor mNegativeTextColor;
};
}
