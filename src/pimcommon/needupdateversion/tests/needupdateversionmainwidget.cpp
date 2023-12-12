/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "needupdateversionmainwidget.h"
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
}

NeedUpdateVersionMainWidget::~NeedUpdateVersionMainWidget() = default;
