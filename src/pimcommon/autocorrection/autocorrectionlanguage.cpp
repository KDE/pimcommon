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

#include "autocorrectionlanguage.h"
#include <QLocale>
#include <QSet>

using namespace PimCommon;

static bool stripCountryCode(QString *languageCode)
{
    const int idx = languageCode->indexOf(QLatin1Char('_'));
    if (idx != -1) {
        *languageCode = languageCode->left(idx);
        return true;
    }
    return false;
}

AutoCorrectionLanguage::AutoCorrectionLanguage(QWidget *parent)
    : QComboBox(parent)
{
    QLocale cLocale(QLocale::C);
    QSet<QString> insertedLanguages;
    const QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);
    for (const QLocale &lang : allLocales) {
        QString languageCode = lang.name();
        if (lang != cLocale) {
            const QString nativeName = lang.nativeLanguageName();
            // For some languages the native name might be empty.
            // In this case use the non native language name as fallback.
            // See: QTBUG-51323
            QString languageName = nativeName.isEmpty() ? QLocale::languageToString(lang.language()) : nativeName;
            languageName = languageName.toLower();
            if (!insertedLanguages.contains(languageName)) {
                addItem(languageName, languageCode);
                insertedLanguages << languageName;
            } else if (stripCountryCode(&languageCode)) {
                if (!insertedLanguages.contains(languageName)) {
                    addItem(languageName, languageCode);
                    insertedLanguages << languageName;
                }
            }
        }
    }

    QString defaultLang;
    if (!QLocale::system().uiLanguages().isEmpty()) {
        defaultLang = QLocale::system().uiLanguages().at(0);
        if (defaultLang == QLatin1Char('C')) {
            defaultLang = QStringLiteral("en_US");
        }
    }
    const int index = findData(defaultLang);
    setCurrentIndex(index);
    model()->sort(0);
}

AutoCorrectionLanguage::~AutoCorrectionLanguage()
{
}

QString AutoCorrectionLanguage::language() const
{
    return itemData(currentIndex()).toString();
}

void AutoCorrectionLanguage::setLanguage(const QString &language)
{
    const int index = findData(language);
    setCurrentIndex(index);
}
