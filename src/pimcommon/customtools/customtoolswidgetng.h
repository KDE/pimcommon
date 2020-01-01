/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

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

#ifndef CUSTOMTOOLSWIDGETNG_H
#define CUSTOMTOOLSWIDGETNG_H

#include <QWidget>
#include "pimcommon_export.h"
class KToggleAction;
class KActionCollection;
namespace PimCommon {
class CustomToolsWidgetNgPrivate;
class CustomToolsPlugin;
class CustomToolsViewInterface;
/**
 * @brief The CustomToolsWidgetNg class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsWidgetNg : public QWidget
{
    Q_OBJECT
public:
    explicit CustomToolsWidgetNg(QWidget *parent = nullptr);
    ~CustomToolsWidgetNg();

    Q_REQUIRED_RESULT QList<KToggleAction *> actionList() const;
    void initializeView(KActionCollection *ac, const QVector<CustomToolsPlugin *> &localPluginsList);

    void setText(const QString &text);

    void addCustomToolViewInterface(PimCommon::CustomToolsViewInterface *plugin);

public Q_SLOTS:
    void slotToolsWasClosed();
    void slotActivateView(QWidget *w);

Q_SIGNALS:
    void insertText(const QString &url);
    void toolActivated();

private:
    CustomToolsWidgetNgPrivate *const d;
};
}
#endif // CUSTOMTOOLSWIDGETNG_H
