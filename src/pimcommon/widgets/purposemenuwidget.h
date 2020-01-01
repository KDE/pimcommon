/*
  Copyright (c) 2018-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PURPOSEMENUWIDGET_H
#define PURPOSEMENUWIDGET_H

#include <QObject>
#include "pimcommon_export.h"
namespace Purpose {
class Menu;
}
class QMenu;
class QTemporaryFile;
namespace PimCommon {
/**
 * @brief The PurposeMenuWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT PurposeMenuWidget : public QObject
{
    Q_OBJECT
public:
    explicit PurposeMenuWidget(QWidget *parentWidget, QObject *parent = nullptr);
    ~PurposeMenuWidget() override;

    virtual QByteArray text() = 0;
    QMenu *menu() const;
private:
    void slotInitializeShareMenu();
    void slotShareActionFinished(const QJsonObject &output, int error, const QString &message);
    Purpose::Menu *mShareMenu = nullptr;
    QTemporaryFile *mTemporaryShareFile = nullptr;
    QWidget *mParentWidget = nullptr;
};
}

#endif // PURPOSEMENUWIDGET_H
