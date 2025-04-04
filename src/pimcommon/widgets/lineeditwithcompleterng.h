/*
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QLineEdit>
class QStringListModel;
namespace PimCommon
{
/**
 * @brief The LineEditWithCompleterNg class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT LineEditWithCompleterNg : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEditWithCompleterNg(QWidget *parent = nullptr);
    ~LineEditWithCompleterNg() override;

    void addCompletionItem(const QString &str);
    void slotClearHistory();

protected:
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QStringListModel *const mCompleterListModel;
    QStringList mListCompetion;
};
}
