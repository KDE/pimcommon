/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrection/widgets/lineeditwithautocorrection.h"
#include <TextAutoCorrection/AutoCorrection>

#include <QKeyEvent>

using namespace PimCommon;
class PimCommon::LineEditWithAutoCorrectionPrivate
{
public:
    LineEditWithAutoCorrectionPrivate()
        : mAutoCorrection(new TextAutoCorrection::AutoCorrection())
    {
    }

    ~LineEditWithAutoCorrectionPrivate()
    {
        if (mNeedToDeleteAutoCorrection) {
            delete mAutoCorrection;
        }
    }
    TextAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
    bool mNeedToDeleteAutoCorrection = true;
};

LineEditWithAutoCorrection::LineEditWithAutoCorrection(QWidget *parent, const QString &configFile)
    : PimCommon::SpellCheckLineEdit(parent, configFile)
    , d(new PimCommon::LineEditWithAutoCorrectionPrivate)
{
}

LineEditWithAutoCorrection::~LineEditWithAutoCorrection() = default;

TextAutoCorrection::AutoCorrection *LineEditWithAutoCorrection::autocorrection() const
{
    return d->mAutoCorrection;
}

void LineEditWithAutoCorrection::setAutocorrection(TextAutoCorrection::AutoCorrection *autocorrect)
{
    d->mNeedToDeleteAutoCorrection = false;
    delete d->mAutoCorrection;
    d->mAutoCorrection = autocorrect;
}

void LineEditWithAutoCorrection::setAutocorrectionLanguage(const QString &language)
{
    TextAutoCorrection::AutoCorrectionSettings *settings = d->mAutoCorrection->autoCorrectionSettings();
    settings->setLanguage(language);
    d->mAutoCorrection->setAutoCorrectionSettings(settings);
}

void LineEditWithAutoCorrection::keyPressEvent(QKeyEvent *e)
{
    if (d->mAutoCorrection && d->mAutoCorrection->autoCorrectionSettings()->isEnabledAutoCorrection()) {
        if ((e->key() == Qt::Key_Space) || (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
            if (!textCursor().hasSelection()) {
                int position = textCursor().position();
                // no Html format in subject. => false
                const bool addSpace = d->mAutoCorrection->autocorrect(false, *document(), position);
                QTextCursor cur = textCursor();
                cur.setPosition(position);
                if (e->key() == Qt::Key_Space) {
                    if (addSpace) {
                        cur.insertText(QStringLiteral(" "));
                        setTextCursor(cur);
                    }
                    return;
                }
            }
        }
    }
    PimCommon::SpellCheckLineEdit::keyPressEvent(e);
}
