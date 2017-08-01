/*
  Copyright (c) 2012-2017 Montel Laurent <montel@kde.org>

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

#include "importkmailautocorrection.h"

#include <QFile>
#include <QDomDocument>
#include <QXmlStreamReader>
#include "pimcommon_debug.h"
using namespace PimCommon;

ImportKMailAutocorrection::ImportKMailAutocorrection(QWidget *parent)
    : ImportAbstractAutocorrection(parent)
{
}

ImportKMailAutocorrection::~ImportKMailAutocorrection()
{

}

bool ImportKMailAutocorrection::import(const QString &fileName, LoadAttribute loadAttribute)
{
    QFile xmlFile(fileName);
    if (!xmlFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    QXmlStreamReader xml(&xmlFile);
    mMaxFindStringLenght = 0;
    mMinFindStringLenght = 0;
    if (xml.readNextStartElement()) {
        while (xml.readNextStartElement()) {
            if (xml.name() == QLatin1String("UpperCaseExceptions")) {
                if (loadAttribute == All) {
                    while (xml.readNextStartElement()) {
                        const QStringRef tagname = xml.name();
                        if (tagname == QLatin1String("word")) {
                            if (xml.attributes().hasAttribute(QStringLiteral("exception"))) {
                                const QString exception = xml.attributes().value(QStringLiteral("exception")).toString();
                                mUpperCaseExceptions += exception;
                                xml.skipCurrentElement();
                            }
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if(xml.name() == QLatin1String("TwoUpperLetterExceptions")) {
                if (loadAttribute == All) {
                    while (xml.readNextStartElement()) {
                        const QStringRef tagname = xml.name();
                        if (tagname == QLatin1String("word")) {
                            if (xml.attributes().hasAttribute(QStringLiteral("exception"))) {
                                const QString exception = xml.attributes().value(QStringLiteral("exception")).toString();
                                mTwoUpperLetterExceptions += exception;
                                xml.skipCurrentElement();
                            }
                        } else {
                            xml.skipCurrentElement();
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if(xml.name() == QLatin1String("DoubleQuote")) {
                if (loadAttribute == All) {
                    if (xml.readNextStartElement()) {
                        const QStringRef tagname = xml.name();
                        if (tagname == QLatin1String("doublequote")) {
                            mTypographicDoubleQuotes.begin = xml.attributes().value(QStringLiteral("begin")).toString().at(0);
                            mTypographicDoubleQuotes.end = xml.attributes().value(QStringLiteral("end")).toString().at(0);
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if(xml.name() == QLatin1String("SimpleQuote")) {
                if (loadAttribute == All) {
                    if (xml.readNextStartElement()) {
                        const QStringRef tagname = xml.name();
                        if (tagname == QLatin1String("simplequote")) {
                            mTypographicSingleQuotes.begin = xml.attributes().value(QStringLiteral("begin")).toString().at(0);
                            mTypographicSingleQuotes.end = xml.attributes().value(QStringLiteral("end")).toString().at(0);
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if(xml.name() == QLatin1String("SuperScript")) {
                if (loadAttribute == All || loadAttribute == SuperScript) {
                    while (xml.readNextStartElement()) {
                        const QStringRef tagname = xml.name();
                        if (tagname == QLatin1String("item")) {
                            const QString find = xml.attributes().value(QStringLiteral("find")).toString();
                            const QString super = xml.attributes().value(QStringLiteral("super")).toString();
                            mSuperScriptEntries.insert(find, super);
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                    }

                } else {
                    xml.skipCurrentElement();
                }
            } else if(xml.name() == QLatin1String("items")) {
                if (loadAttribute == All) {
                    while (xml.readNextStartElement()) {
                        const QStringRef tagname = xml.name();
                        if (tagname == QLatin1String("item")) {
                            const QString find = xml.attributes().value(QStringLiteral("find")).toString();
                            const QString replace = xml.attributes().value(QStringLiteral("replace")).toString();
                            const int findLenght(find.length());
                            mMaxFindStringLenght = qMax(findLenght, mMaxFindStringLenght);
                            mMinFindStringLenght = qMin(findLenght, mMinFindStringLenght);
                            mAutocorrectEntries.insert(find, replace);
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else {
                //TODO verify
                xml.skipCurrentElement();
            }
        }
    }
    return true;
}

