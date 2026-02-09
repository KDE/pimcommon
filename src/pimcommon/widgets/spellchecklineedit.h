/*
 * SPDX-FileCopyrightText: 2011-2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once
#include "pimcommon_export.h"
#include <TextCustomEditor/RichTextEditor>

class QMimeData;
namespace PimCommon
{
/*!
 * \class PimCommon::SpellCheckLineEdit
 * \brief The SpellCheckLineEdit class provides a line editor with spell checking capabilities
 * \inmodule PimCommon
 * \inheaderfile PimCommon/SpellCheckLineEdit
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT SpellCheckLineEdit : public TextCustomEditor::RichTextEditor
{
    Q_OBJECT

public:
    /*!
     * Constructs a SpellCheckLineEdit object.
     * \a parent of widget
     * \a configFile config file name for spell checking
     */
    explicit SpellCheckLineEdit(QWidget *parent, const QString &configFile);
    /*!
     * Destructor
     */
    ~SpellCheckLineEdit() override;

protected:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *) override;
    void insertFromMimeData(const QMimeData *source) override;

Q_SIGNALS:
    /*!
     * Emitted when the user uses the up arrow in the first line. The application
     * should then put the focus on the widget above the text edit.
     */
    void focusUp();

    /*!
     * Emitted when the user uses the down arrow in the last line. The application
     * should then put the focus on the widget below the text edit.
     */
    void focusDown();
};
}
