/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfigurewidget.h"
#include "translatorutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QComboBox>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
using namespace PimCommon;
TranslatorConfigureWidget::TranslatorConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mEngine(new QComboBox(this))
    , mStackedWidget(new QStackedWidget(this))
    , mEmptyWidget(new QWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mEngine->setObjectName(QStringLiteral("mEngine"));
    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);

    auto label = new QLabel(i18n("Engine:"), this);
    label->setObjectName(QStringLiteral("label"));
    hboxLayout->addWidget(label);
    hboxLayout->addWidget(mEngine);

    mStackedWidget->setObjectName(QStringLiteral("mStackedWidget"));
    mainLayout->addWidget(mStackedWidget);

    mStackedWidget->addWidget(mEmptyWidget);

    fillEngine();
}

TranslatorConfigureWidget::~TranslatorConfigureWidget() = default;

void TranslatorConfigureWidget::fillEngine()
{
    TranslatorUtil::fillComboboxSettings(mEngine);
}

void TranslatorConfigureWidget::saveSettings()
{
    TranslatorUtil::saveEngineSettings(mEngine->currentData().toString());
}

void TranslatorConfigureWidget::loadSettings()
{
    const QString engine = TranslatorUtil::loadEngine();
    const int index = mEngine->findData(engine);
    if (index != -1) {
        mEngine->setCurrentIndex(index);
    }
}

void TranslatorConfigureWidget::switchEngine()
{
    // TODO
}
