/*
  Copyright (c) 2013-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef TEMPLATEMANAGER_H
#define TEMPLATEMANAGER_H

#include "pimcommon_export.h"
#include <QObject>

namespace PimCommon {
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
    ~TemplateManager();

private:
    void slotDirectoryChanged();
    void loadTemplates(bool init = false);
    void initTemplatesDirectories(const QString &templatesRelativePath);
    TemplateInfo loadTemplate(const QString &themePath, const QString &defaultDesktopFileName);

    TemplateManagerPrivate *const d;
};
}

#endif // TEMPLATEMANAGER_H
