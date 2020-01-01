/*
  Copyright (c) 2016-2020 Laurent Montel <montel@kde.org>

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

#ifndef AbstractGENERICPLUGIN_H
#define AbstractGENERICPLUGIN_H

#include <QObject>
#include "pimcommon_export.h"
class KActionCollection;
namespace PimCommon {
class AbstractGenericPluginInterface;
/**
 * @brief The AbstractGenericPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AbstractGenericPlugin : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGenericPlugin(QObject *parent = nullptr);
    ~AbstractGenericPlugin();

    virtual PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent = nullptr) = 0;
    Q_REQUIRED_RESULT virtual bool hasPopupMenuSupport() const;
    Q_REQUIRED_RESULT virtual bool hasToolBarSupport() const;
    Q_REQUIRED_RESULT virtual bool hasConfigureDialog() const;
    Q_REQUIRED_RESULT virtual bool hasStatusBarSupport() const;

    virtual void showConfigureDialog(QWidget *parent = nullptr);

    void setIsEnabled(bool enabled);
    Q_REQUIRED_RESULT bool isEnabled() const;

Q_SIGNALS:
    void configChanged();

private:
    bool mIsEnabled;
};
}
#endif // AbstractGENERICPLUGIN_H
