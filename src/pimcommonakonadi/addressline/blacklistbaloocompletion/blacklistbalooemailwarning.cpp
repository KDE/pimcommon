/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailwarning.h"
#include <KLocalizedString>
#include <QAction>

using namespace PimCommon;

BlackListBalooEmailWarning::BlackListBalooEmailWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(false);
    setMessageType(Warning);
    setWordWrap(true);

    setText(i18n("The list was changed. Do you want to save before to make another search ?"));
    auto saveAction = new QAction(i18n("Save"), this);
    saveAction->setObjectName(QStringLiteral("saveblacklist"));
    connect(saveAction, &QAction::triggered, this, &BlackListBalooEmailWarning::slotSaveBlackList);
    addAction(saveAction);

    auto searchAction = new QAction(i18n("Search"), this);
    searchAction->setObjectName(QStringLiteral("search"));
    connect(searchAction, &QAction::triggered, this, &BlackListBalooEmailWarning::slotSearch);
    addAction(searchAction);
}

BlackListBalooEmailWarning::~BlackListBalooEmailWarning() = default;

void BlackListBalooEmailWarning::slotSaveBlackList()
{
    animatedHide();
    Q_EMIT saveChanges();
}

void BlackListBalooEmailWarning::slotSearch()
{
    animatedHide();
    Q_EMIT newSearch();
}
