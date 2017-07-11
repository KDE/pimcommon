/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LINEEDITPASSWORD_H
#define LINEEDITPASSWORD_H

#include <QWidget>
#include "pimcommon_export.h"
class QLineEdit;
class QAction;
namespace PimCommon
{
class LineEditPasswordPrivate;
class PIMCOMMON_EXPORT LineEditPassword : public QWidget
{
    Q_OBJECT
public:
    /**
     * Constructs a lineedit password widget.
     * @since 5.37
     *
     * @param parent Passed to lower level constructor.
     */
    explicit LineEditPassword(QWidget *parent = nullptr);
    /**
      * Destructs the lineedit password widget.
      */
    ~LineEditPassword();

    /**
     * Assign password
     */
    void setPassword(const QString &p);

    /**
     * Returns the password entered.
     */
    QString password() const;


    /**
     * Returns the QAction (@internal)
     */
    QAction *toggleEchoModeAction() const;

    /**
     * Returns the lineedit widget.
     */
    QLineEdit *passwordLineEdit() const;

private:
    class LineEditPasswordPrivate;
    LineEditPasswordPrivate *const d;
};
}

#endif // LINEEDITPASSWORD_H
