/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kactionmenuchangecase.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
using namespace PimCommon;
class PimCommon::KActionMenuChangeCasePrivate
{
public:
    KActionMenuChangeCasePrivate() = default;

    QAction *mUpperCase = nullptr;
    QAction *mSentenceCase = nullptr;
    QAction *mLowerCase = nullptr;
    QAction *mReverseCase = nullptr;
};

KActionMenuChangeCase::KActionMenuChangeCase(QObject *parent)
    : KActionMenu(parent)
    , d(new PimCommon::KActionMenuChangeCasePrivate)
{
    setText(i18n("Change Case"));
    d->mUpperCase = new QAction(i18n("Uppercase"), this);
    connect(d->mUpperCase, &QAction::triggered, this, &KActionMenuChangeCase::upperCase);

    d->mSentenceCase = new QAction(i18n("Sentence case"), this);
    connect(d->mSentenceCase, &QAction::triggered, this, &KActionMenuChangeCase::sentenceCase);

    d->mLowerCase = new QAction(i18n("Lowercase"), this);
    connect(d->mLowerCase, &QAction::triggered, this, &KActionMenuChangeCase::lowerCase);

    d->mReverseCase = new QAction(i18n("Reverse Case"), this);
    connect(d->mReverseCase, &QAction::triggered, this, &KActionMenuChangeCase::reverseCase);

    addAction(d->mUpperCase);
    addAction(d->mLowerCase);
    addAction(d->mSentenceCase);
    addAction(d->mReverseCase);
}

KActionMenuChangeCase::~KActionMenuChangeCase() = default;

QAction *KActionMenuChangeCase::upperCaseAction() const
{
    return d->mUpperCase;
}

QAction *KActionMenuChangeCase::sentenceCaseAction() const
{
    return d->mSentenceCase;
}

QAction *KActionMenuChangeCase::lowerCaseAction() const
{
    return d->mLowerCase;
}

QAction *KActionMenuChangeCase::reverseCaseAction() const
{
    return d->mReverseCase;
}

void KActionMenuChangeCase::appendInActionCollection(KActionCollection *ac)
{
    if (ac) {
        ac->addAction(QStringLiteral("change_to_uppercase"), d->mUpperCase);
        ac->addAction(QStringLiteral("change_to_sentencecase"), d->mSentenceCase);
        ac->addAction(QStringLiteral("change_to_lowercase"), d->mLowerCase);
        ac->addAction(QStringLiteral("change_to_reversecase"), d->mReverseCase);
    }
}
