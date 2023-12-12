/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "needupdateversionmainwidget.h"
#include "needupdateversion/needupdateversionutils.h"
#include "needupdateversion/needupdateversionwidget.h"
#include <QTextEdit>
#include <QVBoxLayout>

NeedUpdateVersionMainWidget::NeedUpdateVersionMainWidget(QWidget *parent)
    : QWidget{parent}
    , mNeedUpdateVersionWidget(new PimCommon::NeedUpdateVersionWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(mNeedUpdateVersionWidget);

    auto textEditor = new QTextEdit(this);
    mainLayout->addWidget(textEditor);
    checkVersion();
}

NeedUpdateVersionMainWidget::~NeedUpdateVersionMainWidget() = default;

void NeedUpdateVersionMainWidget::checkVersion()
{
    mNeedUpdateVersionWidget->setObsoleteVersion(PimCommon::NeedUpdateVersionUtils::obsoleteVersionStatus(QStringLiteral("22.04.1"), QDate::currentDate()));
}
#include "moc_needupdateversionmainwidget.cpp"
