/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ADDRESSEELINEEDITAKONADI_H
#define ADDRESSEELINEEDITAKONADI_H

namespace Akonadi {
class Session;
}

namespace PimCommon {
/**
 * @brief The AddresseeLineEditAkonadi class
 * @author Laurent Montel <montel@kde.org>
 */
class AddresseeLineEditAkonadi
{
public:
    explicit AddresseeLineEditAkonadi();
    ~AddresseeLineEditAkonadi();

    Akonadi::Session *akonadiSession() const;

private:
    mutable Akonadi::Session *m_akonadiSession = nullptr;
};
}

#endif // ADDRESSEELINEEDITAKONADI_H
