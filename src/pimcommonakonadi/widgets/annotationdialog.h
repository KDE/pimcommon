/* SPDX-FileCopyrightText: 2010 Thomas McGuire <mcguire@kde.org>

   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include "pimcommonakonadi_export.h"

#include <QDialog>

namespace Akonadi
{
class Item;
}

namespace PimCommon
{
/**
 * @short A dialog for editing annotations of an email.
 *
 * @author Thomas McGuire <mcguire@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AnnotationEditDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Creates a new annotation edit dialog.
     *
     * @param item The item.
     * @param parent The parent widget.
     */
    explicit AnnotationEditDialog(const Akonadi::Item &item, QWidget *parent = nullptr);

    /**
     * Destroys the annotation edit dialog.
     */
    ~AnnotationEditDialog() override;

private:
    PIMCOMMONAKONADI_NO_EXPORT void readConfig();
    PIMCOMMONAKONADI_NO_EXPORT void writeConfig();
    PIMCOMMONAKONADI_NO_EXPORT void slotAccepted();
    PIMCOMMONAKONADI_NO_EXPORT void slotDeleteNote();
    //@cond PRIVATE
    class AnnotationEditDialogPrivate;
    std::unique_ptr<AnnotationEditDialogPrivate> const d;
    //@endcond
};
}
