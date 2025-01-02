/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistakonadisearchemailwarning.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QAction>

using namespace PimCommon;

BlackListAkonadiSearchEmailWarning::BlackListAkonadiSearchEmailWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(false);
    setMessageType(Warning);
    setWordWrap(true);

    setText(i18n("The list was changed. Do you want to save before to make another search ?"));
    auto saveAction = new QAction(i18nc("@action", "Save"), this);
    saveAction->setObjectName("saveblacklist"_L1);
    connect(saveAction, &QAction::triggered, this, &BlackListAkonadiSearchEmailWarning::slotSaveBlackList);
    addAction(saveAction);

    auto searchAction = new QAction(i18nc("@action", "Search"), this);
    searchAction->setObjectName("search"_L1);
    connect(searchAction, &QAction::triggered, this, &BlackListAkonadiSearchEmailWarning::slotSearch);
    addAction(searchAction);

    auto cancelAction = new QAction(i18nc("@action", "Cancel"), this);
    cancelAction->setObjectName("cancel"_L1);
    connect(cancelAction, &QAction::triggered, this, &BlackListAkonadiSearchEmailWarning::animatedHide);
    addAction(cancelAction);
}

BlackListAkonadiSearchEmailWarning::~BlackListAkonadiSearchEmailWarning() = default;

void BlackListAkonadiSearchEmailWarning::slotSaveBlackList()
{
    animatedHide();
    Q_EMIT saveChanges();
}

void BlackListAkonadiSearchEmailWarning::slotSearch()
{
    animatedHide();
    Q_EMIT newSearch();
}

#include "moc_blacklistakonadisearchemailwarning.cpp"
