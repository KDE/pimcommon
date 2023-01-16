/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrection/widgets/lineeditwithautocorrection.h"
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
#include <TextAutoCorrection/AutoCorrection>
#else
#include <PimCommonAutoCorrection/AutoCorrection>
#endif

#include <QKeyEvent>

using namespace PimCommon;
class PimCommon::LineEditWithAutoCorrectionPrivate
{
public:
    LineEditWithAutoCorrectionPrivate()
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
        : mAutoCorrection(new TextAutoCorrection::AutoCorrection())
#else
        : mAutoCorrection(new PimCommonAutoCorrection::AutoCorrection())
#endif
    {
    }

    ~LineEditWithAutoCorrectionPrivate()
    {
        if (mNeedToDeleteAutoCorrection) {
            delete mAutoCorrection;
        }
    }
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    TextAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
#else
    PimCommonAutoCorrection::AutoCorrection *mAutoCorrection = nullptr;
#endif
    bool mNeedToDeleteAutoCorrection = true;
};

LineEditWithAutoCorrection::LineEditWithAutoCorrection(QWidget *parent, const QString &configFile)
    : PimCommon::SpellCheckLineEdit(parent, configFile)
    , d(new PimCommon::LineEditWithAutoCorrectionPrivate)
{
}

LineEditWithAutoCorrection::~LineEditWithAutoCorrection() = default;

#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
TextAutoCorrection::AutoCorrection *LineEditWithAutoCorrection::autocorrection() const
#else
PimCommonAutoCorrection::AutoCorrection *LineEditWithAutoCorrection::autocorrection() const
#endif
{
    return d->mAutoCorrection;
}

#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
void LineEditWithAutoCorrection::setAutocorrection(TextAutoCorrection::AutoCorrection *autocorrect)
#else
void LineEditWithAutoCorrection::setAutocorrection(PimCommonAutoCorrection::AutoCorrection *autocorrect)
#endif
{
    d->mNeedToDeleteAutoCorrection = false;
    delete d->mAutoCorrection;
    d->mAutoCorrection = autocorrect;
}

void LineEditWithAutoCorrection::setAutocorrectionLanguage(const QString &language)
{
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    TextAutoCorrection::AutoCorrectionSettings *settings = d->mAutoCorrection->autoCorrectionSettings();
#else
    PimCommonAutoCorrection::AutoCorrectionSettings *settings = d->mAutoCorrection->autoCorrectionSettings();
#endif
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
