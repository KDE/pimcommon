/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <KActionMenu>
class QAction;
class KActionCollection;
namespace PimCommon
{
class KActionMenuChangeCasePrivate;
/*!
 * \class PimCommon::KActionMenuChangeCase
 * \brief The KActionMenuChangeCase class provides an action menu for changing text case
 * \inmodule PimCommon
 * \inheaderfile PimCommon/KActionMenuChangeCase
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT KActionMenuChangeCase : public KActionMenu
{
    Q_OBJECT
public:
    /*!
     * Constructs a KActionMenuChangeCase.
     * @param parent The parent QObject
     */
    explicit KActionMenuChangeCase(QObject *parent = nullptr);
    /*!
     * Destructs the KActionMenuChangeCase.
     */
    ~KActionMenuChangeCase() override;

    /*!
     * Returns the action for converting text to uppercase.
     * @return A QAction for uppercase conversion
     */
    [[nodiscard]] QAction *upperCaseAction() const;

    /*!
     * Returns the action for converting text to sentence case.
     * @return A QAction for sentence case conversion
     */
    [[nodiscard]] QAction *sentenceCaseAction() const;

    /*!
     * Returns the action for converting text to lowercase.
     * @return A QAction for lowercase conversion
     */
    [[nodiscard]] QAction *lowerCaseAction() const;

    /*!
     * Returns the action for reversing text case.
     * @return A QAction for case reversal
     */
    [[nodiscard]] QAction *reverseCaseAction() const;

    /*!
     * Appends the actions to the given action collection.
     * @param ac The KActionCollection to add actions to
     */
    void appendInActionCollection(KActionCollection *ac);

Q_SIGNALS:
    /*!
     * Emitted when uppercase conversion is triggered.
     */
    void upperCase();
    /*!
     * Emitted when sentence case conversion is triggered.
     */
    void sentenceCase();
    /*!
     * Emitted when lowercase conversion is triggered.
     */
    void lowerCase();
    /*!
     * Emitted when case reversal is triggered.
     */
    void reverseCase();

private:
    std::unique_ptr<KActionMenuChangeCasePrivate> const d;
};
}
