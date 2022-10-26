/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exportkmailautocorrection.h"
#include "pimcommon_debug.h"
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QXmlStreamWriter>

using namespace PimCommon;
ExportKMailAutocorrection::ExportKMailAutocorrection() = default;

ExportKMailAutocorrection::~ExportKMailAutocorrection() = default;

bool PimCommon::ExportKMailAutocorrection::exportData(const QString &language, const QString &fileName, QString &errorMessage)
{
    Q_UNUSED(errorMessage);
    const QString fname = fileName.isEmpty() ? QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1String("/autocorrect/custom-")
            + (language == QLatin1String("en_US") ? QStringLiteral("autocorrect") : language) + QLatin1String(".xml")
                                             : fileName;
    QFileInfo fileInfo(fname);
    QDir().mkpath(fileInfo.absolutePath());
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCDebug(PIMCOMMON_LOG) << "We can't save in file :" << fname;
        return false;
    }

    QXmlStreamWriter streamWriter(&file);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeDTD(QStringLiteral("<!DOCTYPE autocorrection>"));

    streamWriter.writeStartElement(QStringLiteral("Word"));

    streamWriter.writeStartElement(QStringLiteral("items"));
    QHashIterator<QString, QString> i(mAutocorrectEntries);
    while (i.hasNext()) {
        i.next();
        streamWriter.writeStartElement(QStringLiteral("item"));
        streamWriter.writeAttribute(QStringLiteral("find"), i.key());
        streamWriter.writeAttribute(QStringLiteral("replace"), i.value());
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("UpperCaseExceptions"));
    QSet<QString>::const_iterator upper = mUpperCaseExceptions.constBegin();
    while (upper != mUpperCaseExceptions.constEnd()) {
        streamWriter.writeStartElement(QStringLiteral("word"));
        streamWriter.writeAttribute(QStringLiteral("exception"), *upper);
        ++upper;
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("TwoUpperLetterExceptions"));
    QSet<QString>::const_iterator twoUpper = mTwoUpperLetterExceptions.constBegin();
    while (twoUpper != mTwoUpperLetterExceptions.constEnd()) {
        streamWriter.writeStartElement(QStringLiteral("word"));
        streamWriter.writeAttribute(QStringLiteral("exception"), *twoUpper);
        ++twoUpper;
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("DoubleQuote"));
    streamWriter.writeStartElement(QStringLiteral("doublequote"));
    streamWriter.writeAttribute(QStringLiteral("begin"), mTypographicDoubleQuotes.begin);
    streamWriter.writeAttribute(QStringLiteral("end"), mTypographicDoubleQuotes.end);
    streamWriter.writeEndElement();
    streamWriter.writeEndElement();

    streamWriter.writeStartElement(QStringLiteral("SimpleQuote"));
    streamWriter.writeStartElement(QStringLiteral("simplequote"));
    streamWriter.writeAttribute(QStringLiteral("begin"), mTypographicSingleQuotes.begin);
    streamWriter.writeAttribute(QStringLiteral("end"), mTypographicSingleQuotes.end);
    streamWriter.writeEndElement();
    streamWriter.writeEndElement();

    streamWriter.writeEndDocument();
    return true;
}
