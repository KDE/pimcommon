/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QTreeWidget>
class QPaintEvent;
class QEvent;
namespace PimCommon
{
/*!
 * \class PimCommon::CustomTreeView
 * \brief The CustomTreeView class provides a tree widget with default text support
 * \inmodule PimCommon
 * \inheaderfile PimCommon/CustomTreeView
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomTreeView : public QTreeWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a CustomTreeView.
     * @param parent The parent widget
     */
    explicit CustomTreeView(QWidget *parent = nullptr);
    /*!
     * Destructs the CustomTreeView.
     */
    ~CustomTreeView() override;

    /*!
     * Sets the default text to display when the tree is empty.
     * @param text The default text
     */
    void setDefaultText(const QString &text);

    /*!
     * Returns whether the default text is shown.
     * @return true if default text is shown, false otherwise
     */
    [[nodiscard]] bool showDefaultText() const;
    /*!
     * Sets whether to show the default text.
     * @param b true to show default text, false otherwise
     */
    void setShowDefaultText(bool b);

protected:
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;

    bool mShowDefaultText = true;

private:
    PIMCOMMON_NO_EXPORT void generalPaletteChanged();
    PIMCOMMON_NO_EXPORT void generalFontChanged();
    QColor mTextColor;
    QString mDefaultText;
};
}
