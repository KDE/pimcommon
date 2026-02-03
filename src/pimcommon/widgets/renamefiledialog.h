/*
 * SPDX-FileCopyrightText: 2011-2026 Laurent Montel <montel@kde.org>
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
/*!
 * \class RenameFileDialog
 * \brief The RenameFileDialog class provides a dialog for renaming files
 * \inmodule PimCommon
 * \inheaderfile PimCommon/RenameFileDialog
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT RenameFileDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * Constructs a RenameFileDialog.
     * @param url The URL of the file to rename
     * @param multiFiles Whether this dialog is for multiple files
     * @param parent The parent widget
     */
    explicit RenameFileDialog(const QUrl &url, bool multiFiles, QWidget *parent);
    /*!
     * Destructs the RenameFileDialog.
     */
    ~RenameFileDialog() override;

    enum RenameFileDialogResult {
        RENAMEFILE_IGNORE = 0,
        RENAMEFILE_IGNOREALL = 1,
        RENAMEFILE_RENAME = 2,
        RENAMEFILE_OVERWRITE = 3,
        RENAMEFILE_OVERWRITEALL = 4
    };

    /*!
     * Returns the new name entered by the user.
     * @return The new file URL
     */
    [[nodiscard]] QUrl newName() const;

private:
    PIMCOMMON_NO_EXPORT void slotOverwritePressed();
    PIMCOMMON_NO_EXPORT void slotIgnorePressed();
    PIMCOMMON_NO_EXPORT void slotRenamePressed();
    PIMCOMMON_NO_EXPORT void slotApplyAllPressed();
    PIMCOMMON_NO_EXPORT void slotSuggestNewNamePressed();
    class RenameFileDialogPrivate;
    std::unique_ptr<RenameFileDialogPrivate> const d;
};
}
