/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef CONTENTTYPEWIDGET_H
#define CONTENTTYPEWIDGET_H

#include <QWidget>
#include "pimcommonakonadi_export.h"
namespace PimCommon {
class ContentTypeWidgetPrivate;
/**
 * @brief The ContentTypeWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT ContentTypeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentTypeWidget(QWidget *parent = nullptr);
    ~ContentTypeWidget();

    Q_REQUIRED_RESULT int currentIndex() const;
    void setCurrentIndex(int index);

    void setCurrentItem(const QString &name);
    Q_REQUIRED_RESULT QString currentText() const;

Q_SIGNALS:
    void activated(int index);

private:
    ContentTypeWidgetPrivate *const d;
};
}
#endif // CONTENTTYPEWIDGET_H
