/*
 * Copyright (c) 2011-2020 Laurent Montel <montel@kde.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *  In addition, as a special exception, the copyright holders give
 *  permission to link the code of this program with any edition of
 *  the Qt library by Trolltech AS, Norway (or with modified versions
 *  of Qt that use the same license as Qt), and distribute linked
 *  combinations including the two.  You must obey the GNU General
 *  Public License in all respects for all of the code used other than
 *  Qt.  If you modify this file, you may extend this exception to
 *  your version of the file, but you are not obligated to do so.  If
 *  you do not wish to do so, delete this exception statement from
 *  your version.
 */

#include "spellchecklineedit.h"
#include <QStyleOptionFrame>
#include <QKeyEvent>
#include <QStyle>
#include <QMimeData>

using namespace PimCommon;

SpellCheckLineEdit::SpellCheckLineEdit(QWidget *parent, const QString &configFile)
    : KPIMTextEdit::RichTextEditor(parent)
{
    setSpellCheckingConfigFileName(configFile);
    setSearchSupport(false);
    setAllowTabSupport(false);
    setAcceptRichText(false);
    setTabChangesFocus(true);
    // widget may not be resized vertically
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    setLineWrapMode(NoWrap);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCheckSpellingEnabled(true);
    document()->adjustSize();

    document()->setDocumentMargin(2);
}

SpellCheckLineEdit::~SpellCheckLineEdit()
{
}

void SpellCheckLineEdit::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Enter
        || e->key() == Qt::Key_Return
        || e->key() == Qt::Key_Down) {
        Q_EMIT focusDown();
        return;
    } else if (e->key() == Qt::Key_Up) {
        Q_EMIT focusUp();
        return;
    }
    RichTextEditor::keyPressEvent(e);
}

QSize SpellCheckLineEdit::sizeHint() const
{
    QFontMetrics fm(font());

    const int h = document()->size().toSize().height() - fm.descent() + 2 * frameWidth();

    QStyleOptionFrame opt;
    opt.initFrom(this);
    opt.rect = QRect(0, 0, 100, h);
    opt.lineWidth = lineWidth();
    opt.midLineWidth = 0;
    opt.state |= QStyle::State_Sunken;

    QSize s = style()->sizeFromContents(QStyle::CT_LineEdit, &opt, QSize(100, h), this);

    return s;
}

QSize SpellCheckLineEdit::minimumSizeHint() const
{
    return sizeHint();
}

void SpellCheckLineEdit::insertFromMimeData(const QMimeData *source)
{
    if (!source) {
        return;
    }

    setFocus();

    // Copy text from the clipboard (paste)
    QString pasteText = source->text();

    // is there any text in the clipboard?
    if (!pasteText.isEmpty()) {
        // replace \r with \n to make xterm pastes happy
        pasteText.replace(QLatin1Char('\r'), QLatin1Char('\n'));
        // remove blank lines
        while (pasteText.contains(QLatin1String("\n\n"))) {
            pasteText.replace(QLatin1String("\n\n"), QLatin1String("\n"));
        }

        QRegExp reTopSpace(QStringLiteral("^ *\n"));
        while (pasteText.contains(reTopSpace)) {
            pasteText.remove(reTopSpace);
        }

        QRegExp reBottomSpace(QStringLiteral("\n *$"));
        while (pasteText.contains(reBottomSpace)) {
            pasteText.remove(reBottomSpace);
        }

        // does the text contain at least one newline character?
        pasteText.replace(QLatin1Char('\n'), QLatin1Char(' '));

        insertPlainText(pasteText);
        ensureCursorVisible();
        return;
    } else {
        RichTextEditor::insertFromMimeData(source);
    }
}
