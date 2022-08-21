/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
namespace PimCommon
{
class TranslatorEngineBase : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorEngineBase(QObject *parent = nullptr);
    ~TranslatorEngineBase() override;
};
}
