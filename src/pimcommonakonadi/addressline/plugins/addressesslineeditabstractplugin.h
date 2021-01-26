/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDRESSESSLINEEDITABSTRACTPLUGIN_H
#define ADDRESSESSLINEEDITABSTRACTPLUGIN_H

#include "pimcommonakonadi_export.h"
#include <QObject>

namespace PimCommon
{
class AddresseeLineEdit;
/**
 * @brief The AddressessLineEditAbstractPluginInfo struct
 * @author Laurent Montel <montel@kde.org>
 */
struct PIMCOMMONAKONADI_EXPORT AddressessLineEditAbstractPluginInfo {
    QString name;
    QString identifier;
    QString description;
};

/**
 * @brief The AddressessLineEditAbstractPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AddressessLineEditAbstractPlugin : public QObject
{
    Q_OBJECT
public:
    explicit AddressessLineEditAbstractPlugin(QObject *parent = nullptr);
    ~AddressessLineEditAbstractPlugin();

    void setLineEdit(PimCommon::AddresseeLineEdit *linedit);

    virtual QVector<AddressessLineEditAbstractPluginInfo> names() const = 0;
    virtual void start() = 0;
    virtual void cancel() = 0;
    virtual void stop() = 0;

Q_SIGNALS:
    void wasUpdated();

private:
    PimCommon::AddresseeLineEdit *mLinedit = nullptr;
    bool mEnabled = true;
};
}

#endif // ADDRESSESSLINEEDITABSTRACTPLUGIN_H
