/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineconfigurewidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

LibreTranslateEngineConfigureWidget::LibreTranslateEngineConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mServerUrl->setObjectName(QStringLiteral("mServerUrl"));
    // TODO
}

LibreTranslateEngineConfigureWidget::~LibreTranslateEngineConfigureWidget() = default;
