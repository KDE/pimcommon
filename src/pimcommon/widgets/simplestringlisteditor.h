/*  -*- c++ -*-
    simplestringlisteditor.h

    This file is part of KMail, the KDE mail client.
    Copyright (c) 2001 Marc Mutz <mutz@kde.org>

    Copyright (C) 2013-2019 Laurent Montel <montel@kde.org>

    KMail is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    KMail is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    In addition, as a special exception, the copyright holders give
    permission to link the code of this program with any edition of
    the Qt library by Trolltech AS, Norway (or with modified versions
    of Qt that use the same license as Qt), and distribute linked
    combinations including the two.  You must obey the GNU General
    Public License in all respects for all of the code used other than
    Qt.  If you modify this file, you may extend this exception to
    your version of the file, but you are not obligated to do so.  If
    you do not wish to do so, delete this exception statement from
    your version.
*/

#ifndef SIMPLESTRINGLISTEDITOR_H
#define SIMPLESTRINGLISTEDITOR_H

#include <QWidget>
#include <QStringList>

#include "pimcommon_export.h"

class QListWidget;
class QListWidgetItem;

//
//
// SimpleStringListEditor (a listbox with "add..." and "remove" buttons)
//
//
namespace PimCommon {
class SimpleStringListEditorPrivate;
/**
 * @brief The SimpleStringListEditor class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT SimpleStringListEditor : public QWidget
{
    Q_OBJECT
public:
    enum ButtonCode {
        None = 0,
        Add = 1,
        Remove = 2,
        Modify = 4,
        Up = 8,
        Down = 16,
        Custom = 32,
        All = Add | Remove | Modify | Up | Down,
        Unsorted = Add | Remove | Modify
    };

    /** Constructor. Populates the list with @p strings. */
    explicit SimpleStringListEditor(QWidget *parent = nullptr, ButtonCode buttons = Unsorted, const QString &addLabel = QString(), const QString &removeLabel = QString(), const QString &modifyLabel = QString(), const QString &addDialogLabel = QString());

    ~SimpleStringListEditor() override;
    /** Sets the list of strings displayed to @p strings */
    void setStringList(const QStringList &strings);

    /** Adds @p strings to the list of displayed strings */
    void appendStringList(const QStringList &strings);

    /** Retrieves the current list of strings */
    Q_REQUIRED_RESULT QStringList stringList() const;

    /** Sets the text of button @p button to @p text */
    void setButtonText(ButtonCode button, const QString &text);

    void setUpDownAutoRepeat(bool b);
    Q_REQUIRED_RESULT QSize sizeHint() const override;

    virtual void addNewEntry();
    virtual QString customEntry(const QString &text);

    Q_REQUIRED_RESULT virtual QString modifyEntry(const QString &text);
    void setAddDialogLabel(const QString &addDialogLabel);

    void setRemoveDialogLabel(const QString &removeDialogLabel);
Q_SIGNALS:
    /** Connected slots can alter the argument to be added or set the
      argument to QString() to suppress adding.
    */
    void aboutToAdd(QString &);
    void changed();

protected:
    void insertNewEntry(const QString &newEntry);

protected Q_SLOTS:
    void slotAdd();
    void slotRemove();
    void slotModify();
    void slotUp();
    void slotDown();
    void slotCustomize();

    void slotSelectionChanged();

private:
    void slotContextMenu(const QPoint &);
    bool containsString(const QString &str);
    SimpleStringListEditorPrivate *const d;
};
}

#endif // SIMPLESTRINGLISTEDITOR_H
