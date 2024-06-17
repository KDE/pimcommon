/*  -*- c++ -*-
    simplestringlisteditor.h

    This file is part of KMail, the KDE mail client.
    SPDX-FileCopyrightText: 2001 Marc Mutz <mutz@kde.org>

    SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QStringList>
#include <QWidget>

#include "pimcommon_export.h"

//
//
// SimpleStringListEditor (a listbox with "add..." and "remove" buttons)
//
//
namespace PimCommon
{
class SimpleStringListEditorPrivate;
/**
 * @brief The SimpleStringListEditor class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT SimpleStringListEditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList stringList READ stringList WRITE setStringList NOTIFY changed USER true)
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
    explicit SimpleStringListEditor(QWidget *parent = nullptr,
                                    ButtonCode buttons = Unsorted,
                                    const QString &addLabel = QString(),
                                    const QString &removeLabel = QString(),
                                    const QString &modifyLabel = QString(),
                                    const QString &addDialogLabel = QString());

    ~SimpleStringListEditor() override;
    /** Sets the list of strings displayed to @p strings */
    void setStringList(const QStringList &strings);

    /** Adds @p strings to the list of displayed strings */
    void appendStringList(const QStringList &strings);

    /** Retrieves the current list of strings */
    [[nodiscard]] QStringList stringList() const;

    /** Sets the text of button @p button to @p text */
    void setButtonText(ButtonCode button, const QString &text);

    void setUpDownAutoRepeat(bool b);
    [[nodiscard]] QSize sizeHint() const override;

    virtual void addNewEntry();
    [[nodiscard]] virtual QString customEntry(const QString &text);

    [[nodiscard]] virtual QString modifyEntry(const QString &text);
    void setAddDialogLabel(const QString &addDialogLabel);
    void setAddDialogTitle(const QString &str);

    void setModifyDialogTitle(const QString &str);
    void setModifyDialogLabel(const QString &str);

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
    PIMCOMMON_NO_EXPORT void slotContextMenu(const QPoint &);
    PIMCOMMON_NO_EXPORT bool containsString(const QString &str);
    std::unique_ptr<SimpleStringListEditorPrivate> const d;
};
}
