/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "addresseelineeditakonadi.h"
#include <Akonadi/Session>

using namespace PimCommon;

AddresseeLineEditAkonadi::AddresseeLineEditAkonadi() = default;

AddresseeLineEditAkonadi::~AddresseeLineEditAkonadi() = default;

Akonadi::Session *AddresseeLineEditAkonadi::akonadiSession() const
{
    if (!m_akonadiSession) {
        m_akonadiSession = new Akonadi::Session("contactsCompletionSession");
    }
    return m_akonadiSession;
}
