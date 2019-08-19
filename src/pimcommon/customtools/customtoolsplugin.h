/*
  Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

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

#ifndef CUSTOMTOOLSPLUGIN_H
#define CUSTOMTOOLSPLUGIN_H

#include "pimcommon_export.h"
#include <QObject>
class KActionCollection;
namespace PimCommon {
class CustomToolsWidgetNg;
class CustomToolsViewInterface;
class CustomToolsPluginPrivate;
/**
 * @brief The CustomToolsPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsPlugin : public QObject
{
    Q_OBJECT
public:
    explicit CustomToolsPlugin(QObject *parent = nullptr);
    ~CustomToolsPlugin();

    virtual PimCommon::CustomToolsViewInterface *createView(KActionCollection *ac, CustomToolsWidgetNg *parent = nullptr) = 0;
    Q_REQUIRED_RESULT virtual QString customToolName() const = 0;

    Q_REQUIRED_RESULT virtual bool hasConfigureDialog() const;
    virtual void showConfigureDialog(QWidget *parent);

    void emitConfigChanged();

    Q_REQUIRED_RESULT virtual QString description() const;

    void setIsEnabled(bool enabled);
    Q_REQUIRED_RESULT bool isEnabled() const;

private:
    CustomToolsPluginPrivate *const d;
};
}
#endif // CUSTOMTOOLSPLUGIN_H
