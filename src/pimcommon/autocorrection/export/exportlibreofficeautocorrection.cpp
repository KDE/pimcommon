/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exportlibreofficeautocorrection.h"
#include <KZip>

using namespace PimCommon;

ExportLibreOfficeAutocorrection::ExportLibreOfficeAutocorrection() = default;

ExportLibreOfficeAutocorrection::~ExportLibreOfficeAutocorrection() = default;

bool ExportLibreOfficeAutocorrection::exportData(const QString &language, const QString &fileName, QString &errorMessage)
{
    // TODO
    return false;
}

bool ExportLibreOfficeAutocorrection::exportDocumentList()
{
    // archiveFileName = QStringLiteral("DocumentList.xml");
#if 0
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

#endif
    return false;
}

bool ExportLibreOfficeAutocorrection::exportSentenceExceptList()
{
    // archiveFileName = QStringLiteral("SentenceExceptList.xml");
    return false;
}

bool ExportLibreOfficeAutocorrection::exportWordExceptList()
{
    // archiveFileName = QStringLiteral("WordExceptList.xml");
    return false;
}
