/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef IMPORTABSTRACTAUTOCORRECTION_H
#define IMPORTABSTRACTAUTOCORRECTION_H

#include <QSet>
#include <QString>
#include <QHash>

#include "autocorrection/autocorrection.h"
#include "pimcommon_private_export.h"
namespace PimCommon {
class PIMCOMMON_TESTS_EXPORT ImportAbstractAutocorrection
{
    Q_GADGET
public:
    enum LoadAttribute {
        All = 0,
        SuperScript
    };
    Q_ENUM(LoadAttribute)

    explicit ImportAbstractAutocorrection(QWidget *parent);
    virtual ~ImportAbstractAutocorrection();

    virtual bool import(const QString &fileName, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) = 0;

    Q_REQUIRED_RESULT QSet<QString> upperCaseExceptions() const;
    Q_REQUIRED_RESULT QSet<QString> twoUpperLetterExceptions() const;
    Q_REQUIRED_RESULT QHash<QString, QString> autocorrectEntries() const;
    Q_REQUIRED_RESULT QHash<QString, QString> superScriptEntries() const;

    Q_REQUIRED_RESULT AutoCorrection::TypographicQuotes typographicSingleQuotes() const;
    Q_REQUIRED_RESULT AutoCorrection::TypographicQuotes typographicDoubleQuotes() const;

    Q_REQUIRED_RESULT int maxFindStringLenght() const;

    Q_REQUIRED_RESULT int minFindStringLenght() const;

protected:
    int mMaxFindStringLenght = 0;
    int mMinFindStringLenght = 0;
    QSet<QString> mUpperCaseExceptions;
    QSet<QString> mTwoUpperLetterExceptions;
    QHash<QString, QString> mAutocorrectEntries;
    QHash<QString, QString> mSuperScriptEntries;
    AutoCorrection::TypographicQuotes mTypographicSingleQuotes;
    AutoCorrection::TypographicQuotes mTypographicDoubleQuotes;
    QWidget *const mParent;
};
}

#endif // IMPORTABSTRACTAUTOCORRECTION_H
