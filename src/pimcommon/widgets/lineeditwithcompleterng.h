/*
  SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QLineEdit>
class QStringListModel;
namespace PimCommon
{
/*!
 * \class LineEditWithCompleterNg
 * \brief The LineEditWithCompleterNg class provides a line editor with completion support
 * \inmodule PimCommon
 * \inheaderfile PimCommon/LineEditWithCompleterNg
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT LineEditWithCompleterNg : public QLineEdit
{
    Q_OBJECT
public:
    /*!
     * Constructs a LineEditWithCompleterNg.
     * @param parent The parent widget
     */
    explicit LineEditWithCompleterNg(QWidget *parent = nullptr);
    /*!
     * Destructs the LineEditWithCompleterNg.
     */
    ~LineEditWithCompleterNg() override;

    /*!
     * Adds a completion item to the history.
     * @param str The item to add to completion
     */
    void addCompletionItem(const QString &str);
    /*!
     * Clears the completion history.
     */
    void slotClearHistory();

protected:
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    QStringListModel *const mCompleterListModel;
    QStringList mListCompetion;
};
}
