/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_export.h"
#include <QStringList>
#include <QWidget>
class KConfig;
class QListWidget;
class QLineEdit;
class QToolButton;

namespace PimCommon
{
/**
 * @brief The RecentAddressWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT RecentAddressWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecentAddressWidget(QWidget *parent = nullptr);
    ~RecentAddressWidget() override;

    void setAddresses(const QStringList &addrs);
    void storeAddresses(KConfig *config);
    Q_REQUIRED_RESULT bool wasChanged() const;

protected:
    void updateButtonState();
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    void slotAddItem();
    void slotRemoveItem();
    void slotUpdateAddButton(const QString &str);
    QLineEdit *const mLineEdit;
    QToolButton *const mNewButton;
    QToolButton *const mRemoveButton;
    QListWidget *const mListView;
    bool mDirty = false;
};
}
