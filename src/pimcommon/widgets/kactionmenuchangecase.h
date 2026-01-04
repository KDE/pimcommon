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
 * \brief The KActionMenuChangeCase class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT KActionMenuChangeCase : public KActionMenu
{
    Q_OBJECT
public:
    explicit KActionMenuChangeCase(QObject *parent = nullptr);
    ~KActionMenuChangeCase() override;

    [[nodiscard]] QAction *upperCaseAction() const;

    [[nodiscard]] QAction *sentenceCaseAction() const;

    [[nodiscard]] QAction *lowerCaseAction() const;

    [[nodiscard]] QAction *reverseCaseAction() const;

    void appendInActionCollection(KActionCollection *ac);

Q_SIGNALS:
    void upperCase();
    void sentenceCase();
    void lowerCase();
    void reverseCase();

private:
    std::unique_ptr<KActionMenuChangeCasePrivate> const d;
};
}
