/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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

    [[nodiscard]] QList<KToggleAction *> actionList() const;
    void initializeView(KActionCollection *ac, const QList<CustomToolsPlugin *> &localPluginsList);

    void setText(const QString &text);

    void addCustomToolViewInterface(PimCommon::CustomToolsViewInterface *plugin);

public Q_SLOTS:
    void slotToolsWasClosed();
    void slotActivateView(QWidget *w);

Q_SIGNALS:
    void insertText(const QString &url);
    void toolActivated();

private:
    std::unique_ptr<CustomToolsWidgetNgPrivate> const d;
};
}
