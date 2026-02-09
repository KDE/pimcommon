/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class PimCommon::TemplateManager
 * \brief The TemplateManager class manages templates for text composition
 * \inmodule PimCommon
 * \inheaderfile PimCommon/TemplateManager
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT TemplateManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * Constructs a TemplateManager.
     * @param relativeTemplateDir The relative path to the template directory
     * @param sieveTemplateWidget The template list widget to manage
     */
    explicit TemplateManager(const QString &relativeTemplateDir, PimCommon::TemplateListWidget *sieveTemplateWidget);
    /*!
     * Destructs the TemplateManager.
     */
    ~TemplateManager() override;

private:
    PIMCOMMON_NO_EXPORT void slotDirectoryChanged();
    PIMCOMMON_NO_EXPORT void loadTemplates(bool init = false);
    PIMCOMMON_NO_EXPORT void initTemplatesDirectories(const QString &templatesRelativePath);
    [[nodiscard]] PIMCOMMON_NO_EXPORT TemplateInfo loadTemplate(const QString &themePath, const QString &defaultDesktopFileName);

    std::unique_ptr<TemplateManagerPrivate> const d;
};
}
