/*
  SPDX-FileCopyrightText: 2010 Casey Link <unnamedrambler@gmail.com>
  SPDX-FileCopyrightText: 2009-2010 Klaralvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emailvalidator.h"

#include <KEmailAddress>
#include <QRegularExpression>

using namespace PimCommon;

EmailValidator::EmailValidator(QObject *parent)
    : QValidator(parent)
{
}

QValidator::State EmailValidator::validate(QString &str, int &pos) const
{
    Q_UNUSED(pos)

    if (KEmailAddress::isValidSimpleAddress(str)) {
        return QValidator::Acceptable;
    }
    QRegularExpression re(QStringLiteral("\\s"));
    QRegularExpressionMatch match = re.match(str);
    if (match.hasMatch()) {
        return QValidator::Invalid;
    }
    return QValidator::Intermediate;
}

void EmailValidator::fixup(QString &str) const
{
    str = str.trimmed();
}
