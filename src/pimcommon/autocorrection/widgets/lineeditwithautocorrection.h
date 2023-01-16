/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

#include <PimCommon/SpellCheckLineEdit>
#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
namespace TextAutoCorrection
{
class AutoCorrection;
}
#else
namespace PimCommonAutoCorrection
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

#ifdef HAVE_KTEXTADDONS_TEXT_AUTOCORRECTION_SUPPORT
    Q_REQUIRED_RESULT TextAutoCorrection::AutoCorrection *autocorrection() const;
    void setAutocorrection(TextAutoCorrection::AutoCorrection *autocorrect);
#else
    void setAutocorrection(PimCommonAutoCorrection::AutoCorrection *autocorrect);
    Q_REQUIRED_RESULT PimCommonAutoCorrection::AutoCorrection *autocorrection() const;
#endif

    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    std::unique_ptr<LineEditWithAutoCorrectionPrivate> const d;
};
}
