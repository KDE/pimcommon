/*
  Copyright (c) 2012-2020 Laurent Montel <montel@kde.org>

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

#ifndef AutoCorrectionWidget_H
#define AutoCorrectionWidget_H

#include "pimcommon_export.h"
#include "pimcommon/autocorrection.h"
#include <QWidget>

class QTreeWidgetItem;

namespace Ui {
class AutoCorrectionWidget;
}

namespace PimCommon {
class AutoCorrectionWidgetPrivate;
/**
 * @brief The AutoCorrectionWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMON_EXPORT AutoCorrectionWidget : public QWidget
{
    Q_OBJECT

public:
    enum ImportFileType {
        LibreOffice,
        KMail
    };

    explicit AutoCorrectionWidget(QWidget *parent = nullptr);
    ~AutoCorrectionWidget();
    void setAutoCorrection(AutoCorrection *autoCorrect);
    void loadConfig();
    void writeConfig();
    void resetToDefault();

private Q_SLOTS:
    /* tab 2 */
    void enableSingleQuotes(bool state);
    void enableDoubleQuotes(bool state);
    void selectSingleQuoteCharOpen();
    void selectSingleQuoteCharClose();
    void setDefaultSingleQuotes();
    void selectDoubleQuoteCharOpen();
    void selectDoubleQuoteCharClose();
    void setDefaultDoubleQuotes();

    /* tab 3 */
    void enableAdvAutocorrection(bool state);
    void addAutocorrectEntry();
    void removeAutocorrectEntry();
    void setFindReplaceText(QTreeWidgetItem *, int);
    void enableAddRemoveButton();

    /* tab 4 */
    void abbreviationChanged(const QString &text);
    void twoUpperLetterChanged(const QString &text);
    void addAbbreviationEntry();
    void removeAbbreviationEntry();
    void addTwoUpperLetterEntry();
    void removeTwoUpperLetterEntry();

    void slotEnableDisableAbreviationList();
    void slotEnableDisableTwoUpperEntry();

    void slotImportAutoCorrection(QAction *act);

    void changeLanguage(int);
    void updateAddRemoveButton();

    void slotExportAutoCorrection();

Q_SIGNALS:
    void changed();

private:
    void emitChanged();
    void addAutoCorrectEntries();
    void loadAutoCorrectionAndException();
    void loadGlobalAutoCorrectionAndException();
    void setLanguage(const QString &lang);

    AutoCorrectionWidgetPrivate *const d;
};
}

#endif // AutoCorrectionWidget_H
