/*
  SPDX-FileCopyrightText: 2013-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

#include <PimCommon/SpellCheckLineEdit>
namespace TextAutoCorrectionCore
{
class AutoCorrection;
}

namespace PimCommon
{
class LineEditWithAutoCorrectionPrivate;
/*!
 * \class LineEditWithAutoCorrection
 * \brief The LineEditWithAutoCorrection class provides a line editor with auto-correction support
 * \inmodule PimCommon
 * \inheaderfile PimCommon/LineEditWithAutoCorrection
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT LineEditWithAutoCorrection : public PimCommon::SpellCheckLineEdit
{
    Q_OBJECT
public:
    /*!
     * Constructs a LineEditWithAutoCorrection.
     * @param parent The parent widget
     * @param configFile The configuration file for auto-correction
     */
    explicit LineEditWithAutoCorrection(QWidget *parent, const QString &configFile);
    /*!
     */
    ~LineEditWithAutoCorrection() override;

    /*!
     */
    [[nodiscard]] TextAutoCorrectionCore::AutoCorrection *autocorrection() const;
    /*!
     */
    void setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect);
    /*!
     */
    void setAutocorrectionLanguage(const QString &language);

protected:
    /*!
     */
    void keyPressEvent(QKeyEvent *e) override;

private:
    std::unique_ptr<LineEditWithAutoCorrectionPrivate> const d;
};
}
