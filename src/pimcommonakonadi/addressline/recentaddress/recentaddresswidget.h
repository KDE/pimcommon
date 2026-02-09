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
/*!
 * \class PimCommon::RecentAddressWidget
 * \brief The RecentAddressWidget class provides a widget for managing recent addresses
 * \inmodule PimCommonAkonadi
 * \inheaderfile PimCommonAkonadi/RecentAddressWidget
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT RecentAddressWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a RecentAddressWidget.
     * @param parent The parent widget
     */
    explicit RecentAddressWidget(QWidget *parent = nullptr);
    /*!
     * Destructs the RecentAddressWidget.
     */
    ~RecentAddressWidget() override;

    /*!
     * Sets the addresses to display.
     * @param addrs The list of addresses
     */
    void setAddresses(const QStringList &addrs);
    /*!
     * Stores the addresses to configuration.
     * @param config The KConfig object to store to
     */
    void storeAddresses(KConfig *config);
    /*!
     * Checks if the address list was modified.
     * @return true if addresses were changed, false otherwise
     */
    [[nodiscard]] bool wasChanged() const;

protected:
    /*!
     * Updates the state of action buttons.
     */
    void updateButtonState();
    /*!
     * Handles events for this widget and its children.
     * @param o The object that received the event
     * @param e The event
     * @return true if the event was handled, false otherwise
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
