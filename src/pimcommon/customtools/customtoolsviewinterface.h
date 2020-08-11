/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CUSTOMTOOLSVIEWINTERFACE_H
#define CUSTOMTOOLSVIEWINTERFACE_H

#include "pimcommon_export.h"

#include <QWidget>
class KToggleAction;
namespace PimCommon {
/**
 * @brief The CustomToolsViewInterface class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT CustomToolsViewInterface : public QWidget
{
    Q_OBJECT
public:
    explicit CustomToolsViewInterface(QWidget *parent = nullptr);
    ~CustomToolsViewInterface() override;

    virtual void setText(const QString &text);
    virtual KToggleAction *action() const;

Q_SIGNALS:
    void insertText(const QString &text);
    void toolsWasClosed();
    void activateView(QWidget *);
};
}
#endif // CUSTOMTOOLSVIEWINTERFACE_H
