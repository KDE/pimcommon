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
     * Constructs a ConfigurePluginDialog.
     * @param parent The parent widget
     */
    explicit ConfigurePluginDialog(QWidget *parent = nullptr);
    /*!
     * Destructs the ConfigurePluginDialog.
     */
    ~ConfigurePluginDialog() override;

    /*!
     * Initializes the dialog layout.
     * @param addSpacer Whether to add a spacer to the layout
     */
    void initLayout(bool addSpacer = false);

protected:
    /*!
     * Shows help for the dialog.
     * @param name The help document name
     * @param anchor The anchor within the help document
     */
    void showHelp(const QString &name, const QString &anchor);
    /*!
     * Creates the main layout widget for the dialog.
     * @return A QWidget containing the dialog layout
     */
    virtual QWidget *createLayout() = 0;
    /*!
     * Saves the configuration from the dialog.
     */
    virtual void save() = 0;
    /*!
     * Loads the configuration into the dialog.
     */
    virtual void load() = 0;
    /*!
     * Resets the configuration to default values.
     */
    virtual void reset();

    /*!
     * Shows the help dialog.
     */
    virtual void help();

    /*!
     * Returns the dialog button box.
     * @return The QDialogButtonBox for this dialog
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
