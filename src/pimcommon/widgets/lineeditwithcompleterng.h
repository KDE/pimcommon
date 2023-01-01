/*
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

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

protected:
    void contextMenuEvent(QContextMenuEvent *e) override;

public Q_SLOTS:
    void slotClearHistory();

private:
    QStringListModel *const mCompleterListModel;
    QStringList mListCompetion;
};
}
