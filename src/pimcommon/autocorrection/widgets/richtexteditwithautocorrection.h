/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef RICHTEXTEDITWITHAUTOCORRECTION_H
#define RICHTEXTEDITWITHAUTOCORRECTION_H

#include "pimcommon_export.h"
#include <KPIMTextEdit/RichTextEditor>

namespace PimCommon
{
class AutoCorrection;
class RichTextEditWithAutoCorrectionPrivate;
/**
 * @brief The RichTextEditWithAutoCorrection class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT RichTextEditWithAutoCorrection : public KPIMTextEdit::RichTextEditor
{
    Q_OBJECT
public:
    explicit RichTextEditWithAutoCorrection(QWidget *parent = nullptr);
    ~RichTextEditWithAutoCorrection() override;

    Q_REQUIRED_RESULT PimCommon::AutoCorrection *autocorrection() const;

    void setAutocorrection(PimCommon::AutoCorrection *autocorrect);

    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    RichTextEditWithAutoCorrectionPrivate *const d;
};
}

#endif // RICHTEXTEDITWITHAUTOCORRECTION_H
