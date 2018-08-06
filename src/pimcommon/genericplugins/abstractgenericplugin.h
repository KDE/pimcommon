/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

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
class PIMCOMMON_EXPORT AbstractGenericPlugin : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGenericPlugin(QObject *parent = nullptr);
    ~AbstractGenericPlugin();

    virtual PimCommon::AbstractGenericPluginInterface *createInterface(KActionCollection *ac, QObject *parent = nullptr) = 0;
    Q_REQUIRED_RESULT virtual bool hasPopupMenuSupport() const;
    Q_REQUIRED_RESULT virtual bool hasToolBarSupport() const;
    Q_REQUIRED_RESULT virtual bool hasConfigureDialog() const;
    Q_REQUIRED_RESULT virtual bool hasStatusBarSupport() const;

    virtual void showConfigureDialog(QWidget *parent = nullptr);

    void setIsEnabled(bool enabled);
    Q_REQUIRED_RESULT bool isEnabled() const;

private:
    bool mIsEnabled;
};
}
#endif // AbstractGENERICPLUGIN_H
