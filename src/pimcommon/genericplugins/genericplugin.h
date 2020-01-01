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

#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include "abstractgenericplugin.h"
#include "pimcommon_export.h"
namespace PimCommon {
/**
 * @brief The GenericPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT GenericPlugin : public AbstractGenericPlugin
{
    Q_OBJECT
public:
    explicit GenericPlugin(QObject *parent = nullptr);
    ~GenericPlugin();
};
}
#endif // GENERICPLUGIN_H
