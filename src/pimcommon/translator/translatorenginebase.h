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

    void setParentWidget(QWidget *parent);
    Q_REQUIRED_RESULT QString resultTranslate() const;
    void setInputText(const QString &text);
    void setFrom(const QString &language);
    void setTo(const QString &language);

    void debug();
    void clear();

Q_SIGNALS:
    void translateDone();
    void translateFailed(bool result, const QString &errorMessage = QString());

protected:
    QString mJsonData;
    QString mJsonDebug;
    QString mInputText;
    QString mFrom;
    QString mTo;
    QString mResult;
    bool mDebug = false;

private:
    QWidget *mParentWidget = nullptr;
};
}
