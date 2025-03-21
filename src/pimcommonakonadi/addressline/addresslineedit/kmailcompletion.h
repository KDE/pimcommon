/*
  This file is part of libkdepim.

  SPDX-FileCopyrightText: 2006 Christian Schaarschmidt <schaarsc@gmx.de>
  SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KCompletion>

#include <QMap>
#include <QString>
#include <QStringList>

namespace PimCommon
{
/**
 * KMailCompletion allows lookup of email addresses by keyword.
 * This is used for lookup by nickname, since we don't want the nickname to appear in the final email.
 * E.g. you have a nickname "idiot" for your boss, you want to type "idiot" but you want the completion
 * to offer "Full Name <email@domain>", without the nickname being visible.
 */
class KMailCompletion : public KCompletion
{
    Q_OBJECT

public:
    KMailCompletion();

    /**
     * clears internal keyword map and calls KCompletion::clear.
     */
    void clear() override;

    /**
     * uses KCompletion::makeCompletion to find email addresses which starts
     * with string. ignores keywords.
     *
     * @returns email address
     */
    [[nodiscard]] QString makeCompletion(const QString &string) override;

    /**
     * specify keywords for email.
     *
     * Items may be added with KCompletion::addItem, those will only be
     * returned as match if they are in one of these formats:
     * \li contains localpart@domain
     * \li contains <email>
     * or if they have also been added with this function.
     */
    void addItemWithKeys(const QString &email, int weight, const QStringList *keyWords);

    /**
     * use internal map to replace all keywords in pMatches with corresponding
     * email addresses.
     */
    void postProcessMatches(QStringList *pMatches) const override;

    // We are not using allWeightedMatches() anywhere, therefore we don't need
    // to override the other postProcessMatches() function
    using KCompletion::postProcessMatches;

private:
    QMap<QString, QStringList> m_keyMap;
};
}
