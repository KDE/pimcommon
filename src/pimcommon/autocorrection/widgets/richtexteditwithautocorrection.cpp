/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "richtexteditwithautocorrection.h"
#include "autocorrection/autocorrection.h"

#include <QKeyEvent>

using namespace PimCommon;

class PimCommon::RichTextEditWithAutoCorrectionPrivate
{
public:
    RichTextEditWithAutoCorrectionPrivate()
        : mAutoCorrection(new PimCommon::AutoCorrection())
    {
    }

    ~RichTextEditWithAutoCorrectionPrivate()
    {
        if (mNeedToDelete) {
            delete mAutoCorrection;
        }
    }

    PimCommon::AutoCorrection *mAutoCorrection = nullptr;
    bool mNeedToDelete = true;
};

RichTextEditWithAutoCorrection::RichTextEditWithAutoCorrection(QWidget *parent)
    : KPIMTextEdit::RichTextEditor(parent)
    , d(new PimCommon::RichTextEditWithAutoCorrectionPrivate)
{
}

RichTextEditWithAutoCorrection::~RichTextEditWithAutoCorrection()
{
    delete d;
}

void RichTextEditWithAutoCorrection::setAutocorrection(PimCommon::AutoCorrection *autocorrect)
{
    d->mNeedToDelete = false;
    delete d->mAutoCorrection;
    d->mAutoCorrection = autocorrect;
}

AutoCorrection *RichTextEditWithAutoCorrection::autocorrection() const
{
    return d->mAutoCorrection;
}

void RichTextEditWithAutoCorrection::setAutocorrectionLanguage(const QString &language)
{
    d->mAutoCorrection->setLanguage(language);
}

static bool isSpecial(const QTextCharFormat &charFormat)
{
    return charFormat.isFrameFormat() || charFormat.isImageFormat()
           || charFormat.isListFormat() || charFormat.isTableFormat() || charFormat.isTableCellFormat();
}

void RichTextEditWithAutoCorrection::keyPressEvent(QKeyEvent *e)
{
    if (d->mAutoCorrection && d->mAutoCorrection->isEnabledAutoCorrection()) {
        if ((e->key() == Qt::Key_Space) || (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
            if (!textCursor().hasSelection()) {
                const QTextCharFormat initialTextFormat = textCursor().charFormat();
                const bool richText = acceptRichText();
                int position = textCursor().position();
                const bool addSpace = d->mAutoCorrection->autocorrect(richText, *document(), position);
                QTextCursor cur = textCursor();
                cur.setPosition(position);
                const bool spacePressed = (e->key() == Qt::Key_Space);
                const QChar insertChar = spacePressed ? QLatin1Char(' ') : QLatin1Char('\n');
                if (richText && !isSpecial(initialTextFormat)) {
                    if ((spacePressed && addSpace) || !spacePressed) {
                        cur.insertText(insertChar, initialTextFormat);
                    }
                } else {
                    if ((spacePressed && addSpace) || !spacePressed) {
                        cur.insertText(insertChar);
                    }
                }
                setTextCursor(cur);
                return;
            }
        }
    }
    KPIMTextEdit::RichTextEditor::keyPressEvent(e);
}
