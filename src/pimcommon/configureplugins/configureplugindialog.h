/*
  Copyright (c) 2016-2020 Laurent Montel <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef CONFIGUREPLUGINDIALOG_H
#define CONFIGUREPLUGINDIALOG_H

#include <QDialog>
#include "pimcommon_export.h"
class QDialogButtonBox;
namespace PimCommon {
/**
 * @brief The ConfigurePluginDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT ConfigurePluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigurePluginDialog(QWidget *parent = nullptr);
    ~ConfigurePluginDialog();

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
