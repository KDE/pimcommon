/*
 * SPDX-FileCopyrightText: 2011-2022 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once
#include "pimcommon_export.h"
#include <KPIMTextEdit/RichTextEditor>

class QMimeData;
namespace PimCommon
{
/**
 * @brief The SpellCheckLineEdit class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT SpellCheckLineEdit : public KPIMTextEdit::RichTextEditor
{
    Q_OBJECT

public:
    /**
     * Constructs a SpellCheckLineEdit object.
     * @param parent of widget
     * @param configFile config file name for spell checking
     */
    explicit SpellCheckLineEdit(QWidget *parent, const QString &configFile);
    /**
     * Destructor
     */
    ~SpellCheckLineEdit() override;

protected:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *) override;
    void insertFromMimeData(const QMimeData *source) override;

Q_SIGNALS:
    /**
     * Emitted when the user uses the up arrow in the first line. The application
     * should then put the focus on the widget above the text edit.
     */
    void focusUp();

    void focusDown();
};
}
