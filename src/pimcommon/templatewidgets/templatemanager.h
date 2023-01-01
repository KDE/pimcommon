/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

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
    Q_REQUIRED_RESULT bool isValid() const
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
    void slotDirectoryChanged();
    void loadTemplates(bool init = false);
    void initTemplatesDirectories(const QString &templatesRelativePath);
    TemplateInfo loadTemplate(const QString &themePath, const QString &defaultDesktopFileName);

    std::unique_ptr<TemplateManagerPrivate> const d;
};
}
