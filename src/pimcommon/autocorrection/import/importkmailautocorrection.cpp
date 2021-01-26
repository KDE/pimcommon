/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importkmailautocorrection.h"

#include "pimcommon_debug.h"
#include <QFile>
#include <QXmlStreamReader>
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
            const QStringRef xmlName = xml.name();
            if (xmlName == QLatin1String("UpperCaseExceptions")) {
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
            } else if (xmlName == QLatin1String("TwoUpperLetterExceptions")) {
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
            } else if (xmlName == QLatin1String("DoubleQuote")) {
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
                        xml.skipCurrentElement();
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if (xmlName == QLatin1String("SimpleQuote")) {
                if (loadAttribute == All) {
                    if (xml.readNextStartElement()) {
                        const QStringRef tagname = xml.name();
                        if (tagname == QLatin1String("simplequote")) {
                            const QString simpleQuoteBegin = xml.attributes().value(QStringLiteral("begin")).toString();
                            if (!simpleQuoteBegin.isEmpty()) { // crash when we have old data with bug.
                                mTypographicSingleQuotes.begin = simpleQuoteBegin.at(0);
                            }
                            const QString simpleQuoteEnd = xml.attributes().value(QStringLiteral("end")).toString();
                            if (!simpleQuoteEnd.isEmpty()) { // crash when we have old data with bug.
                                mTypographicSingleQuotes.end = simpleQuoteEnd.at(0);
                            }
                            xml.skipCurrentElement();
                        } else {
                            xml.skipCurrentElement();
                        }
                        xml.skipCurrentElement();
                    }
                } else {
                    xml.skipCurrentElement();
                }
            } else if (xmlName == QLatin1String("SuperScript")) {
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
            } else if (xmlName == QLatin1String("items")) {
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
                // TODO verify
                xml.skipCurrentElement();
            }
        }
    }
    return true;
}
