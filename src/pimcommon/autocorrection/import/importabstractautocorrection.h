/*
  Copyright (c) 2012-2020 Laurent Montel <montel@kde.org>

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

#ifndef IMPORTABSTRACTAUTOCORRECTION_H
#define IMPORTABSTRACTAUTOCORRECTION_H

#include <QSet>
#include <QString>
#include <QHash>

#include "autocorrection/autocorrection.h"

namespace PimCommon {
class ImportAbstractAutocorrection
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
    QWidget *mParent = nullptr;
};
}

#endif // IMPORTABSTRACTAUTOCORRECTION_H
