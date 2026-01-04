/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

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
    /*!
     */
    explicit RecentAddressWidget(QWidget *parent = nullptr);
    /*!
     */
    ~RecentAddressWidget() override;

    /*!
     */
    void setAddresses(const QStringList &addrs);
    /*!
     */
    void storeAddresses(KConfig *config);
    /*!
     */
    [[nodiscard]] bool wasChanged() const;

protected:
    /*!
     */
    void updateButtonState();
    /*!
     */
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotAddItem();
    PIMCOMMONAKONADI_NO_EXPORT void slotRemoveItem();
    PIMCOMMONAKONADI_NO_EXPORT void slotUpdateAddButton(const QString &str);
    PIMCOMMONAKONADI_NO_EXPORT void slotCustomContextMenuRequested(const QPoint &pos);
    QLineEdit *const mLineEdit;
    QToolButton *const mNewButton;
    QToolButton *const mRemoveButton;
    QListWidget *const mListView;
    bool mDirty = false;
};
}
