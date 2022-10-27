/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exportlibreofficeautocorrection.h"
#include "pimcommon_debug.h"
#include <KZip>
#include <QTemporaryFile>
#include <QXmlStreamWriter>

using namespace PimCommon;

ExportLibreOfficeAutocorrection::ExportLibreOfficeAutocorrection() = default;

ExportLibreOfficeAutocorrection::~ExportLibreOfficeAutocorrection()
{
    delete mZip;
}

bool ExportLibreOfficeAutocorrection::exportData(const QString &language, const QString &fileName, QString &errorMessage)
{
    mZip = new KZip(QStringLiteral("/tmp/blabla.dat"));
    bool result = mZip->open(QIODevice::WriteOnly);
    if (!result) {
        qCWarning(PIMCOMMON_LOG) << "Impossible to open " << fileName;
        return false;
    }
    if (!exportDocumentList()) {
        qDebug() << " 111111111111";
        return false;
    }
    if (!exportSentenceExceptList()) {
        qDebug() << " 1111111111112222222";
        return false;
    }
    if (!exportWordExceptList()) {
        qDebug() << " 111111111111333333333";
        return false;
    }
    if (!exportManifest()) {
        qDebug() << " 111111111111444444";
        return false;
    }
    mZip->close();
    delete mZip;
    mZip = nullptr;
    return true;
}

bool ExportLibreOfficeAutocorrection::exportDocumentList()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();
    QXmlStreamWriter streamWriter(&temporaryShareFile);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(QStringLiteral("block-list:block-list"));

    QHashIterator<QString, QString> i(mAutocorrectEntries);
    while (i.hasNext()) {
        i.next();
        streamWriter.writeStartElement(QStringLiteral("block-list:block"));
        streamWriter.writeAttribute(QStringLiteral("block-list:abbreviated-name"), i.key());
        streamWriter.writeAttribute(QStringLiteral("block-list:name"), i.value());
        streamWriter.writeEndElement();
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();
    mZip->addLocalFile(temporaryShareFile.fileName(), QStringLiteral("DocumentList.xml"));
    return true;
}

bool ExportLibreOfficeAutocorrection::exportSentenceExceptList()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();

    QXmlStreamWriter streamWriter(&temporaryShareFile);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(QStringLiteral("block-list:block-list"));

    QSet<QString>::const_iterator upper = mUpperCaseExceptions.constBegin();
    while (upper != mUpperCaseExceptions.constEnd()) {
        streamWriter.writeStartElement(QStringLiteral("block-list:block"));
        streamWriter.writeAttribute(QStringLiteral("block-list:abbreviated-name"), *upper);
        streamWriter.writeEndElement();
        ++upper;
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();

    mZip->addLocalFile(temporaryShareFile.fileName(), QStringLiteral("SentenceExceptList.xml"));
    return true;
}

bool ExportLibreOfficeAutocorrection::exportWordExceptList()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();

    QXmlStreamWriter streamWriter(&temporaryShareFile);

    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(QStringLiteral("block-list:block-list"));

    QSet<QString>::const_iterator twoUpper = mTwoUpperLetterExceptions.constBegin();
    while (twoUpper != mTwoUpperLetterExceptions.constEnd()) {
        streamWriter.writeStartElement(QStringLiteral("block-list:block"));
        streamWriter.writeAttribute(QStringLiteral("block-list:abbreviated-name"), *twoUpper);
        streamWriter.writeEndElement();
        ++twoUpper;
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();

    mZip->addLocalFile(temporaryShareFile.fileName(), QStringLiteral("WordExceptList.xml"));
    return true;
}

bool ExportLibreOfficeAutocorrection::exportManifest()
{
    QTemporaryFile temporaryShareFile;
    temporaryShareFile.open();

    QXmlStreamWriter streamWriter(&temporaryShareFile);
    streamWriter.setAutoFormatting(true);
    streamWriter.setAutoFormattingIndent(2);
    streamWriter.writeStartDocument();

    streamWriter.writeStartElement(QStringLiteral("manifest:manifest"));

    QSet<QString>::const_iterator twoUpper = mTwoUpperLetterExceptions.constBegin();
    while (twoUpper != mTwoUpperLetterExceptions.constEnd()) {
        streamWriter.writeStartElement(QStringLiteral("manifest:file-entry"));
        streamWriter.writeAttribute(QStringLiteral("manifest:full-path"), *twoUpper);
        streamWriter.writeAttribute(QStringLiteral("manifest:media-type"), *twoUpper);
        streamWriter.writeEndElement();
        ++twoUpper;
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    temporaryShareFile.close();

    mZip->addLocalFile(temporaryShareFile.fileName(), QStringLiteral("manifest.xml"));
    // TODO
    return true;
}
