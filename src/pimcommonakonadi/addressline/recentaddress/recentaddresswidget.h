/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#ifndef RECENTADDRESSWIDGET_H
#define RECENTADDRESSWIDGET_H

#include "pimcommonakonadi_export.h"
#include <QWidget>
#include <QStringList>
class KConfig;
class QListWidget;
class QLineEdit;
class QToolButton;

namespace PimCommon {
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
    QToolButton *mNewButton = nullptr;
    QToolButton *mRemoveButton = nullptr;
    QListWidget *mListView = nullptr;
    QLineEdit *mLineEdit = nullptr;
    bool mDirty = false;
};
}
#endif // RECENTADDRESSWIDGET_H
