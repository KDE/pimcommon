/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "abstractgenericplugin.h"
#include "pimcommon_export.h"
namespace PimCommon
{
/*!
 * \class GenericPlugin
 * \brief The GenericPlugin class provides a generic plugin base class
 * \inmodule PimCommon
 * \inheaderfile PimCommon/GenericPlugin
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT GenericPlugin : public AbstractGenericPlugin
{
    Q_OBJECT
public:
    /*!
     * Constructs a GenericPlugin.
     * @param parent The parent QObject
     */
    explicit GenericPlugin(QObject *parent = nullptr);
    /*!
     * Destructs the GenericPlugin.
     */
    ~GenericPlugin() override;
};
}
