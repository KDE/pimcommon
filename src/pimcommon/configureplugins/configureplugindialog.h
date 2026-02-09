/*
  SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QDialog>
class QDialogButtonBox;
namespace PimCommon
{
/*!
 * \class PimCommon::ConfigurePluginDialog
 * \brief The ConfigurePluginDialog class provides a dialog for configuring plugins
 * \inmodule PimCommon
 * \inheaderfile PimCommon/ConfigurePluginDialog
 * \author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     */
    explicit ConfigurePluginDialog(QWidget *parent = nullptr);
    /*!
     */
    ~ConfigurePluginDialog() override;

    /*!
     */
    void initLayout(bool addSpacer = false);

protected:
    /*!
     */
    void showHelp(const QString &name, const QString &anchor);
    /*!
     */
    virtual QWidget *createLayout() = 0;
    /*!
     */
    virtual void save() = 0;
    /*!
     */
    virtual void load() = 0;
    /*!
     */
    virtual void reset();

    /*!
     */
    virtual void help();

    /*!
     */
    [[nodiscard]] QDialogButtonBox *buttonBox() const;

private:
    PIMCOMMON_NO_EXPORT void slotHelpClicked();
    PIMCOMMON_NO_EXPORT void slotAccepted();
    PIMCOMMON_NO_EXPORT void slotRestoreDefaultClicked();
    PIMCOMMON_NO_EXPORT void saveConfig();
    PIMCOMMON_NO_EXPORT void readConfig();
    QDialogButtonBox *mButtonBox = nullptr;
};
}
