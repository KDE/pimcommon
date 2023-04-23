/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

#include "config-pimcommon.h"
#include <PimCommon/SpellCheckLineEdit>
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
namespace TextAutoCorrectionCore
{
class AutoCorrection;
}
#else
namespace TextAutoCorrection
{
class AutoCorrection;
}
#endif

namespace PimCommon
{
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

#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    Q_REQUIRED_RESULT TextAutoCorrectionCore::AutoCorrection *autocorrection() const;
    void setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect);
#else
    Q_REQUIRED_RESULT TextAutoCorrection::AutoCorrection *autocorrection() const;
    void setAutocorrection(TextAutoCorrection::AutoCorrection *autocorrect);
#endif
    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    std::unique_ptr<LineEditWithAutoCorrectionPrivate> const d;
};
}
