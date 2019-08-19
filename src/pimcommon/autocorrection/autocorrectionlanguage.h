/*
  Copyright (c) 2012-2019 Montel Laurent <montel@kde.org>

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

#ifndef AutoCorrectionLanguage_H
#define AutoCorrectionLanguage_H

#include <QComboBox>
#include "pimcommon_export.h"

namespace PimCommon {
/**
 * @brief The AutoCorrectionLanguage class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AutoCorrectionLanguage : public QComboBox
{
public:
    explicit AutoCorrectionLanguage(QWidget *parent);
    ~AutoCorrectionLanguage();

    /**
    * @brief language
    * @return specified language
    */
    Q_REQUIRED_RESULT QString language() const;

    /**
     * @brief setLanguage
     * @param language define specified language
     */
    void setLanguage(const QString &language);
};
}
#endif // AutoCorrectionLanguage_H
