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
 * \class PimCommon::LineEditWithAutoCorrection
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
     * Destructs the LineEditWithAutoCorrection.
     */
    ~LineEditWithAutoCorrection() override;

    /*!
     * Returns the auto-correction engine.
     * @return The TextAutoCorrectionCore::AutoCorrection instance
     */
    [[nodiscard]] TextAutoCorrectionCore::AutoCorrection *autocorrection() const;
    /*!
     * Sets the auto-correction engine.
     * @param autocorrect The auto-correction engine to use
     */
    void setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect);
    /*!
     * Sets the language for auto-correction.
     * @param language The language code
     */
    void setAutocorrectionLanguage(const QString &language);

protected:
    /*!
     * Handles key press events.
     * @param e The key event
     */
    void keyPressEvent(QKeyEvent *e) override;

private:
    std::unique_ptr<LineEditWithAutoCorrectionPrivate> const d;
};
}
