/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
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
