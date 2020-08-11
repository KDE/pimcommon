/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QTreeWidget>
#include "pimcommon_export.h"
class QPaintEvent;
class QEvent;
namespace PimCommon {
/**
 * @brief The CustomTreeView class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomTreeView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CustomTreeView(QWidget *parent = nullptr);
    ~CustomTreeView() override;

    void setDefaultText(const QString &text);

    Q_REQUIRED_RESULT bool showDefaultText() const;
    void setShowDefaultText(bool b);

private:
    void generalPaletteChanged();
    void generalFontChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;

protected:
    bool mShowDefaultText;

private:
    QColor mTextColor;
    QString mDefaultText;
};
}

#endif
