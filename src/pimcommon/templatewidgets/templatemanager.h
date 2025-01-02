/*
  SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QObject>
#include <memory>

namespace PimCommon
{
class TemplateListWidget;
struct TemplateInfo {
    QString name;
    QString script;
    [[nodiscard]] bool isValid() const
    {
        return !name.isEmpty() && !script.isEmpty();
    }

    void debug() const;
};
class TemplateManagerPrivate;
/**
 * @brief The TemplateManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT TemplateManager : public QObject
{
    Q_OBJECT
public:
    explicit TemplateManager(const QString &relativeTemplateDir, PimCommon::TemplateListWidget *sieveTemplateWidget);
    ~TemplateManager() override;

private:
    PIMCOMMON_NO_EXPORT void slotDirectoryChanged();
    PIMCOMMON_NO_EXPORT void loadTemplates(bool init = false);
    PIMCOMMON_NO_EXPORT void initTemplatesDirectories(const QString &templatesRelativePath);
    [[nodiscard]] PIMCOMMON_NO_EXPORT TemplateInfo loadTemplate(const QString &themePath, const QString &defaultDesktopFileName);

    std::unique_ptr<TemplateManagerPrivate> const d;
};
}
