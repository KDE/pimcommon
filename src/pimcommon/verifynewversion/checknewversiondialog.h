/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>

namespace PimCommon
{
class CheckNewVersionWidget;
class CheckNewVersionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckNewVersionDialog(QWidget *parent = nullptr);
    ~CheckNewVersionDialog() override;

    void checkNewVersion();

private:
    CheckNewVersionWidget *const mVerifyNewVersionWidget;
};
}
