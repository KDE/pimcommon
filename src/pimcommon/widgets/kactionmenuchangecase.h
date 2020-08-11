/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KACTIONMENUCHANGECASE_H
#define KACTIONMENUCHANGECASE_H

#include <KActionMenu>
#include "pimcommon_export.h"
class QAction;
class KActionCollection;
namespace PimCommon {
class KActionMenuChangeCasePrivate;
/**
 * @brief The KActionMenuChangeCase class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT KActionMenuChangeCase : public KActionMenu
{
    Q_OBJECT
public:
    explicit KActionMenuChangeCase(QObject *parent = nullptr);
    ~KActionMenuChangeCase();

    Q_REQUIRED_RESULT QAction *upperCaseAction() const;

    Q_REQUIRED_RESULT QAction *sentenceCaseAction() const;

    Q_REQUIRED_RESULT QAction *lowerCaseAction() const;

    Q_REQUIRED_RESULT QAction *reverseCaseAction() const;

    void appendInActionCollection(KActionCollection *ac);

Q_SIGNALS:
    void upperCase();
    void sentenceCase();
    void lowerCase();
    void reverseCase();

private:
    KActionMenuChangeCasePrivate *const d;
};
}

#endif // KACTIONMENUCHANGECASE_H
