/*
 * SPDX-FileCopyrightText: 2011-2021 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef RENAMEFILEDIALOG_H
#define RENAMEFILEDIALOG_H

#include <QDialog>
#include <QUrl>

#include "pimcommon_export.h"

namespace PimCommon {
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
    ~RenameFileDialog();

    enum RenameFileDialogResult {
        RENAMEFILE_IGNORE = 0,
        RENAMEFILE_IGNOREALL = 1,
        RENAMEFILE_RENAME = 2,
        RENAMEFILE_OVERWRITE = 3,
        RENAMEFILE_OVERWRITEALL = 4
    };

    Q_REQUIRED_RESULT QUrl newName() const;

private:
    void slotOverwritePressed();
    void slotIgnorePressed();
    void slotRenamePressed();
    void slotApplyAllPressed();
    void slotSuggestNewNamePressed();
    //@cond PRIVATE
    class RenameFileDialogPrivate;
    RenameFileDialogPrivate *const d;
};
}

#endif /* RENAMEFILEDIALOG_H */
