/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QUrl>
#include <QWidget>
class QLabel;
namespace PimCommon
{
class CheckNewVersionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckNewVersionWidget(QWidget *parent = nullptr);
    ~CheckNewVersionWidget() override;

    void checkNewVersion();

    void setUrl(const QUrl &url);

private:
    void slotFoundNewVersion(bool found);
    QLabel *const mCheckVersionResultLabel;
    QUrl mUrl;
};
}
