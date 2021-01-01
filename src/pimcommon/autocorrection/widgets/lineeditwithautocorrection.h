/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SUBJECTLINEEDITWITHAUTOCORRECTION_H
#define SUBJECTLINEEDITWITHAUTOCORRECTION_H

#include "pimcommon_export.h"

#include <PimCommon/SpellCheckLineEdit>

namespace PimCommon {
class AutoCorrection;
class LineEditWithAutoCorrectionPrivate;
/**
 * @brief The LineEditWithAutoCorrection class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT LineEditWithAutoCorrection : public PimCommon::SpellCheckLineEdit
{
    Q_OBJECT
public:
    explicit LineEditWithAutoCorrection(QWidget *parent, const QString &configFile);
    ~LineEditWithAutoCorrection() override;

    Q_REQUIRED_RESULT PimCommon::AutoCorrection *autocorrection() const;

    void setAutocorrection(PimCommon::AutoCorrection *autocorrect);
    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    LineEditWithAutoCorrectionPrivate *const d;
};
}

#endif // SUBJECTLINEEDITWITHAUTOCORRECTION_H
