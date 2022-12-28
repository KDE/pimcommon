/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteurlrequesterwidget.h"
#include <KLocalizedString>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

using namespace PimCommonTextGrammarCheck;
GrammalecteUrlRequesterWidget::GrammalecteUrlRequesterWidget(QWidget *parent)
    : QWidget{parent}
    , mLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mLineEdit->setObjectName(QStringLiteral("mLineEdit"));
    mainLayout->addWidget(mLineEdit);

    auto selectUrlButton = new QToolButton(this);
    selectUrlButton->setObjectName(QStringLiteral("selectUrlButton"));
    mainLayout->addWidget(selectUrlButton);

    connect(selectUrlButton, &QToolButton::clicked, this, [this]() {
        // TODO
    });
}

GrammalecteUrlRequesterWidget::~GrammalecteUrlRequesterWidget() = default;
