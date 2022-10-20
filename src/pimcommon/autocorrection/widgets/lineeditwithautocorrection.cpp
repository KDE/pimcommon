/*
  SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrection/widgets/lineeditwithautocorrection.h"
#include "autocorrection/autocorrection.h"

#include <QKeyEvent>

using namespace PimCommon;
class PimCommon::LineEditWithAutoCorrectionPrivate
{
public:
    LineEditWithAutoCorrectionPrivate()
        : mAutoCorrection(new PimCommon::AutoCorrection())
    {
    }

    ~LineEditWithAutoCorrectionPrivate()
    {
        if (mNeedToDeleteAutoCorrection) {
            delete mAutoCorrection;
        }
    }

    PimCommon::AutoCorrection *mAutoCorrection = nullptr;
    bool mNeedToDeleteAutoCorrection = true;
};

LineEditWithAutoCorrection::LineEditWithAutoCorrection(QWidget *parent, const QString &configFile)
    : PimCommon::SpellCheckLineEdit(parent, configFile)
    , d(new PimCommon::LineEditWithAutoCorrectionPrivate)
{
}

LineEditWithAutoCorrection::~LineEditWithAutoCorrection() = default;

AutoCorrection *LineEditWithAutoCorrection::autocorrection() const
{
    return d->mAutoCorrection;
}

void LineEditWithAutoCorrection::setAutocorrection(PimCommon::AutoCorrection *autocorrect)
{
    d->mNeedToDeleteAutoCorrection = false;
    delete d->mAutoCorrection;
    d->mAutoCorrection = autocorrect;
}

void LineEditWithAutoCorrection::setAutocorrectionLanguage(const QString &language)
{
    d->mAutoCorrection->setLanguage(language);
}

void LineEditWithAutoCorrection::keyPressEvent(QKeyEvent *e)
{
    if (d->mAutoCorrection && d->mAutoCorrection->isEnabledAutoCorrection()) {
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
