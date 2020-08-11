/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef BALOOCOMPLETIONEMAILTEST_H
#define BALOOCOMPLETIONEMAILTEST_H

#include <QObject>

class BalooCompletionEmailTest : public QObject
{
    Q_OBJECT
public:
    explicit BalooCompletionEmailTest(QObject *parent = nullptr);
    ~BalooCompletionEmailTest();

private Q_SLOTS:
    void returnEmptyListWhenEmailListIsEmpty();
    void shouldReturnSameListWhenNotExclude();
    void shouldReturnSameListIfBlackListDoesntInterceptEmail();
    void shouldReturnUniqueEmail();
    void shouldReturnEmptyListWhenAllBlackListed();
    void shouldExcludeDomain();
    void shouldReturnEmailListWhenDomainListIsNotNull();
    void shouldDontDuplicateEmailWhenUseCase();
    void shouldExcludeDuplicateEntryWithDisplayName();
    void shouldExcludeDuplicateEntryWithDisplayNameAddAddressWithDifferentCase();
    void shouldExcludeDuplicateEntryWithDifferentDisplayNameAddAddressWithDifferentCase();
    void shouldExcludeEmptyNameWithDisplayNameForSameAddress();
};

#endif // BALOOCOMPLETIONEMAILTEST_H
