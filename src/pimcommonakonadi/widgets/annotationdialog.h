/* SPDX-FileCopyrightText: 2010 Thomas McGuire <mcguire@kde.org>

   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef MESSAGECORE_ANNOTATIONDIALOG_H
#define MESSAGECORE_ANNOTATIONDIALOG_H

#include "pimcommonakonadi_export.h"

#include <QDialog>

namespace Akonadi {
class Item;
}

namespace PimCommon {
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
    ~AnnotationEditDialog();

private:
    void readConfig();
    void writeConfig();
    void slotAccepted();
    void slotDeleteNote();
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};
}

#endif
