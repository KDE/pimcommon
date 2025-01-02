/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

namespace Akonadi
{
class Session;
}

namespace PimCommon
{
/**
 * @brief The AddresseeLineEditAkonadi class
 * @author Laurent Montel <montel@kde.org>
 */
class AddresseeLineEditAkonadi
{
public:
    explicit AddresseeLineEditAkonadi();
    ~AddresseeLineEditAkonadi();

    [[nodiscard]] Akonadi::Session *akonadiSession() const;

private:
    mutable Akonadi::Session *m_akonadiSession = nullptr;
};
}
