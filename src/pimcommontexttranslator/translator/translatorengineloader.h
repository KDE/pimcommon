/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
namespace PimCommonTextTranslator
{
class TranslatorEngineLoader : public QObject
{
    Q_OBJECT
public:
    explicit TranslatorEngineLoader(QObject *parent = nullptr);
    ~TranslatorEngineLoader() override;
};
}
