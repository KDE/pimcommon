/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QObject>

namespace PimCommon
{
class AddresseeLineEdit;
/*!
 * \brief The AddressessLineEditAbstractPluginInfo struct contains plugin information
 * \inmodule PimCommonAkonadi
 * \author Laurent Montel <montel@kde.org>
 */
struct PIMCOMMONAKONADI_EXPORT AddressessLineEditAbstractPluginInfo {
    QString name;
    QString identifier;
    QString description;
};

/*!
 * \class PimCommon::AddressessLineEditAbstractPlugin
 * \brief The AddressessLineEditAbstractPlugin class is the base class for addressee line edit plugins
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/AddressessLineEditAbstractPlugin
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AddressessLineEditAbstractPlugin : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs an AddressessLineEditAbstractPlugin.
     * @param parent The parent QObject
     */
    explicit AddressessLineEditAbstractPlugin(QObject *parent = nullptr);
    /*!
     * Destructs the AddressessLineEditAbstractPlugin.
     */
    ~AddressessLineEditAbstractPlugin() override;

    /*!
     * Sets the line edit widget for this plugin.
     * @param linedit The AddresseeLineEdit widget
     */
    void setLineEdit(PimCommon::AddresseeLineEdit *linedit);

    /*!
     * Returns the list of plugin names and information.
     * @return A list of AddressessLineEditAbstractPluginInfo structures
     */
    virtual QList<AddressessLineEditAbstractPluginInfo> names() const = 0;
    /*!
     * Starts the plugin.
     */
    virtual void start() = 0;
    /*!
     * Cancels the plugin operation.
     */
    virtual void cancel() = 0;
    /*!
     * Stops the plugin.
     */
    virtual void stop() = 0;

Q_SIGNALS:
    /*!
     * Emitted when the plugin has been updated.
     */
    void wasUpdated();

private:
    PimCommon::AddresseeLineEdit *mLinedit = nullptr;
};
}
