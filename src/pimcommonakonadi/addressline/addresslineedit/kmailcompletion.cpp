/*
  This file is part of libkdepim.

  SPDX-FileCopyrightText: 2006 Christian Schaarschmidt <schaarsc@gmx.de>
  SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kmailcompletion.h"
#include <QRegularExpression>
#include <QSet>

using namespace PimCommon;

KMailCompletion::KMailCompletion()
{
    setIgnoreCase(true);
}

void KMailCompletion::clear()
{
    m_keyMap.clear();
    KCompletion::clear();
}

QString KMailCompletion::makeCompletion(const QString &string)
{
    QString match = KCompletion::makeCompletion(string);

    // this should be in postProcessMatch, but postProcessMatch is const and will not allow nextMatch
    if (!match.isEmpty()) {
        const QString firstMatch(match);
        while (match.indexOf(QRegularExpression(QStringLiteral("(@)|(<.*>)"))) == -1) {
            /* local email do not require @domain part, if match is an address we'll
             * find last+first <match> in m_keyMap and we'll know that match is
             * already a valid email.
             *
             * Distribution list do not have last+first <match> entry, they will be
             * in mailAddr
             */
            const QStringList &mailAddr = m_keyMap[match]; // get all mailAddr for this keyword
            bool isEmail = false;
            for (QStringList::ConstIterator sit(mailAddr.begin()), sEnd(mailAddr.end()); sit != sEnd; ++sit) {
                if ((*sit).indexOf(QLatin1Char('<') + match + QLatin1Char('>')) != -1 || (*sit) == match) {
                    isEmail = true;
                    break;
                }
            }

            if (!isEmail) {
                // match is a keyword, skip it and try to find match <email@domain>
                match = nextMatch();
                if (firstMatch == match) {
                    match.clear();
                    break;
                }
            } else {
                break;
            }
        }
    }
    return match;
}

void KMailCompletion::addItemWithKeys(const QString &email, int weight, const QStringList *keyWords)
{
    Q_ASSERT(keyWords != nullptr);
    QStringList::ConstIterator end = keyWords->constEnd();
    for (QStringList::ConstIterator it(keyWords->constBegin()); it != end; ++it) {
        QStringList &emailList = m_keyMap[(*it)]; // lookup email-list for given keyword
        if (!emailList.contains(email)) { // add email if not there
            emailList.append(email);
        }
        addItem((*it), weight); // inform KCompletion about keyword
    }
}

void KMailCompletion::postProcessMatches(QStringList *pMatches) const
{
    Q_ASSERT(pMatches != nullptr);
    if (pMatches->isEmpty()) {
        return;
    }

    // KCompletion has found the keywords for us, we can now map them to mail-addr
    QSet<QString> mailAddrDistinct;
    for (QStringList::ConstIterator sit2(pMatches->begin()), sEnd2(pMatches->end()); sit2 != sEnd2; ++sit2) {
        const QStringList &mailAddr = m_keyMap[(*sit2)]; // get all mailAddr for this keyword
        if (mailAddr.isEmpty()) {
            mailAddrDistinct.insert(*sit2);
        } else {
            for (QStringList::ConstIterator sit(mailAddr.begin()), sEnd(mailAddr.end()); sit != sEnd; ++sit) {
                mailAddrDistinct.insert(*sit); // store mailAddr, QSet will make them unique
            }
        }
    }
    pMatches->clear(); // delete keywords
    (*pMatches) += mailAddrDistinct.values(); // add emailAddr
}
