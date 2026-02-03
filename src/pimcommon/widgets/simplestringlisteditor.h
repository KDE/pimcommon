/*  -*- c++ -*-
    simplestringlisteditor.h

    This file is part of KMail, the KDE mail client.
    SPDX-FileCopyrightText: 2001 Marc Mutz <mutz@kde.org>

    SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class SimpleStringListEditor
 * \brief The SimpleStringListEditor class provides a widget for editing a list of strings with add and remove buttons
 * \inmodule PimCommon
 * \inheaderfile PimCommon/SimpleStringListEditor
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT SimpleStringListEditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList stringList READ stringList WRITE setStringList NOTIFY changed USER true)
public:
    enum ButtonCode : uint8_t {
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

    /*!
     * Constructs a SimpleStringListEditor.
     * @param parent The parent widget
     * @param buttons The buttons to display
     * @param addLabel The label for the add button
     * @param removeLabel The label for the remove button
     * @param modifyLabel The label for the modify button
     * @param addDialogLabel The label for the add dialog
     */
    explicit SimpleStringListEditor(QWidget *parent = nullptr,
                                    ButtonCode buttons = Unsorted,
                                    const QString &addLabel = QString(),
                                    const QString &removeLabel = QString(),
                                    const QString &modifyLabel = QString(),
                                    const QString &addDialogLabel = QString());

    /*!
     * Destructs the SimpleStringListEditor.
     */
    ~SimpleStringListEditor() override;
    /*!
     * Sets the list of strings displayed.
     * @param strings The list of strings to display
     */
    void setStringList(const QStringList &strings);

    /*!
     * Adds strings to the list of displayed strings.
     * @param strings The list of strings to add
     */
    void appendStringList(const QStringList &strings);

    /*!
     * Returns the current list of strings.
     * @return The list of strings
     */
    [[nodiscard]] QStringList stringList() const;

    /*!
     * Sets the text of a button.
     * @param button The button code
     * @param text The text to display on the button
     */
    void setButtonText(ButtonCode button, const QString &text);

    /*!
     * Sets whether buttons auto-repeat when held down.
     * @param b true to enable auto-repeat, false otherwise
     */
    void setUpDownAutoRepeat(bool b);
    /*!
     * Returns the size hint for this widget.
     * @return The size hint
     */
    [[nodiscard]] QSize sizeHint() const override;

    /*!
     * Adds a new entry to the list.
     */
    virtual void addNewEntry();
    /*!
     * Handles custom entry input.
     * @param text The text to process
     * @return The processed entry
     */
    [[nodiscard]] virtual QString customEntry(const QString &text);

    /*!
     * Handles modification of an entry.
     * @param text The text to modify
     * @return The modified text
     */
    [[nodiscard]] virtual QString modifyEntry(const QString &text);
    /*!
     * Sets the label for the add dialog.
     * @param addDialogLabel The label text
     */
    void setAddDialogLabel(const QString &addDialogLabel);
    /*!
     * Sets the title for the add dialog.
     * @param str The title text
     */
    void setAddDialogTitle(const QString &str);

    /*!
     * Sets the title for the modify dialog.
     * @param str The title text
     */
    void setModifyDialogTitle(const QString &str);
    /*!
     * Sets the label for the modify dialog.
     * @param str The label text
     */
    void setModifyDialogLabel(const QString &str);

    /*!
     * Sets the label for the remove dialog.
     * @param removeDialogLabel The label text
     */
    void setRemoveDialogLabel(const QString &removeDialogLabel);

Q_SIGNALS:
    /*!
     * Emitted before adding an entry. Connected slots can alter the entry or suppress it by setting to QString().
     * @param entry The entry about to be added
     */
    void aboutToAdd(QString &);
    /*!
     * Emitted when the list has changed.
     */
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
