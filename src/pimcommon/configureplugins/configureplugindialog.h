/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIGUREPLUGINDIALOG_H
#define CONFIGUREPLUGINDIALOG_H

#include "pimcommon_export.h"
#include <QDialog>
class QDialogButtonBox;
namespace PimCommon
{
/**
 * @brief The ConfigurePluginDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigurePluginDialog(QWidget *parent = nullptr);
    ~ConfigurePluginDialog() override;

    void initLayout(bool addSpacer = false);

protected:
    void showHelp(const QString &name, const QString &anchor);
    virtual QWidget *createLayout() = 0;
    virtual void save() = 0;
    virtual void load() = 0;
    virtual void reset();

    virtual void help();

    Q_REQUIRED_RESULT QDialogButtonBox *buttonBox() const;

private:
    void slotHelpClicked();
    void slotAccepted();
    void slotRestoreDefaultClicked();
    void saveConfig();
    void readConfig();
    QDialogButtonBox *mButtonBox = nullptr;
};
}
#endif // CONFIGUREPLUGINDIALOG_H
