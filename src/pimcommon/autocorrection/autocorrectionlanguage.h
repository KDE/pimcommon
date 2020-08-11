/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
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
