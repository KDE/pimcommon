/*
 * SPDX-FileCopyrightText: 2011-2023 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QDialog>
#include <QUrl>

#include "pimcommon_export.h"

namespace PimCommon
{
class RenameFileDialogPrivate;
/**
 * @brief The RenameFileDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT RenameFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RenameFileDialog(const QUrl &url, bool multiFiles, QWidget *parent);
    ~RenameFileDialog() override;

    enum RenameFileDialogResult {
        RENAMEFILE_IGNORE = 0,
        RENAMEFILE_IGNOREALL = 1,
        RENAMEFILE_RENAME = 2,
        RENAMEFILE_OVERWRITE = 3,
        RENAMEFILE_OVERWRITEALL = 4
    };

    [[nodiscard]] QUrl newName() const;

private:
    PIMCOMMON_NO_EXPORT void slotOverwritePressed();
    PIMCOMMON_NO_EXPORT void slotIgnorePressed();
    PIMCOMMON_NO_EXPORT void slotRenamePressed();
    PIMCOMMON_NO_EXPORT void slotApplyAllPressed();
    PIMCOMMON_NO_EXPORT void slotSuggestNewNamePressed();
    //@cond PRIVATE
    class RenameFileDialogPrivate;
    std::unique_ptr<RenameFileDialogPrivate> const d;
};
}
