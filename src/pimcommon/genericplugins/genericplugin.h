/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
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
