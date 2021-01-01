/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditakonadi.h"
#include <AkonadiCore/Session>

using namespace PimCommon;

AddresseeLineEditAkonadi::AddresseeLineEditAkonadi()
{
}

AddresseeLineEditAkonadi::~AddresseeLineEditAkonadi()
{
}

Akonadi::Session *AddresseeLineEditAkonadi::akonadiSession() const
{
    if (!m_akonadiSession) {
        m_akonadiSession = new Akonadi::Session("contactsCompletionSession");
    }
    return m_akonadiSession;
}
