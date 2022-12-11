/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatorconfigurecombowidget.h"
#include "translator/translatorengineloader.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QToolButton>

using namespace PimCommonTextTranslator;
TranslatorConfigureComboWidget::TranslatorConfigureComboWidget(QWidget *parent)
    : QWidget{parent}
    , mEngineComboBox(new QComboBox(this))
    , mConfigureEngine(new QToolButton(parent))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mEngineComboBox->setObjectName(QStringLiteral("mEngineComboBox"));
    mainLayout->addWidget(mEngineComboBox);

    mConfigureEngine->setObjectName(QStringLiteral("mConfigureEngine"));
    mainLayout->addWidget(mConfigureEngine);
    mConfigureEngine->setEnabled(false); // Disable by default
    mConfigureEngine->setIcon(QIcon::fromTheme(QStringLiteral("settings-configure")));
    connect(mConfigureEngine, &QToolButton::clicked, this, &TranslatorConfigureComboWidget::slotConfigureEngine);
}

TranslatorConfigureComboWidget::~TranslatorConfigureComboWidget() = default;

void TranslatorConfigureComboWidget::slotConfigureEngine()
{
    const QString engine = mEngineComboBox->currentData().toString();
    if (PimCommonTextTranslator::TranslatorEngineLoader::self()->hasConfigurationDialog(engine)) {
        PimCommonTextTranslator::TranslatorEngineLoader::self()->showConfigureDialog(engine);
    }
}
