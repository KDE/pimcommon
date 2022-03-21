/*
  SPDX-FileCopyrightText: 2010 Casey Link <unnamedrambler@gmail.com>
  SPDX-FileCopyrightText: 2009-2010 Klaralvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

#include <QValidator>

namespace PimCommon
{
/**
  A validator that enforces correct email addresses.
  @see KEmailAddress::isValidSimpleAddress
*/
class PIMCOMMON_EXPORT EmailValidator : public QValidator // krazy:exclude=dpointer
{
    Q_OBJECT
public:
    explicit EmailValidator(QObject *parent = nullptr);

    State validate(QString &str, int &pos) const override;

    void fixup(QString &str) const override;
};
}
