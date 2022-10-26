/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QHash>
#include <QSet>
#include <QString>

#include "autocorrection/autocorrectionutils.h"
#include "pimcommon_private_export.h"
namespace PimCommon
{
class PIMCOMMON_TESTS_EXPORT ExportAbstractAutocorrection
{
public:
    ExportAbstractAutocorrection();
    virtual ~ExportAbstractAutocorrection();
    virtual bool exportData(const QString &fileName, QString &errorMessagel) = 0;

    void setUpperCaseExceptions(const QSet<QString> &newUpperCaseExceptions);
    void setTwoUpperLetterExceptions(const QSet<QString> &newTwoUpperLetterExceptions);
    void setAutocorrectEntries(const QHash<QString, QString> &newAutocorrectEntries);
    void setSuperScriptEntries(const QHash<QString, QString> &newSuperScriptEntries);
    void setTypographicSingleQuotes(AutoCorrectionUtils::TypographicQuotes newTypographicSingleQuotes);
    void setTypographicDoubleQuotes(AutoCorrectionUtils::TypographicQuotes newTypographicDoubleQuotes);

private:
    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;
    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;
    AutoCorrectionUtils::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrectionUtils::TypographicQuotes mTypographicDoubleQuotes;
};
}
