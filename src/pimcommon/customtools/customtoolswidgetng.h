/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CUSTOMTOOLSWIDGETNG_H
#define CUSTOMTOOLSWIDGETNG_H

#include "pimcommon_export.h"
#include <QWidget>
class KToggleAction;
class KActionCollection;
namespace PimCommon
{
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
    ~CustomToolsWidgetNg() override;

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
