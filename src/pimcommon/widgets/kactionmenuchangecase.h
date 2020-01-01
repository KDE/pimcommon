/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
