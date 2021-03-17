/*
  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importlibreofficeautocorrection.h"
#include "pimcommon_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <KZip>
#include <QDomDocument>
#include <QFile>
#include <QTemporaryDir>

using namespace PimCommon;

ImportLibreOfficeAutocorrection::ImportLibreOfficeAutocorrection(QWidget *parent)
    : ImportAbstractAutocorrection(parent)
{
}

ImportLibreOfficeAutocorrection::~ImportLibreOfficeAutocorrection()
{
    closeArchive();
}

void ImportLibreOfficeAutocorrection::closeArchive()
{
    if (mArchive) {
        if (mArchive->isOpen()) {
            mArchive->close();
        }
        delete mArchive;
        mArchive = nullptr;
    }

    delete mTempDir;
    mTempDir = nullptr;
}

bool ImportLibreOfficeAutocorrection::import(const QString &fileName, LoadAttribute loadAttribute)
{
    // We Don't have it in LibreOffice
    if (loadAttribute == SuperScript) {
        return false;
    }
    closeArchive();
    mArchive = new KZip(fileName);
    const bool result = mArchive->open(QIODevice::ReadOnly);
    if (result) {
        importAutoCorrectionFile();
        return true;
    } else {
        KMessageBox::error(mParent, i18n("Archive cannot be opened in read mode."), i18n("Import LibreOffice Autocorrection File"));
        return false;
    }
}

void ImportLibreOfficeAutocorrection::importAutoCorrectionFile()
{
    mTempDir = new QTemporaryDir();
    const KArchiveDirectory *archiveDirectory = mArchive->directory();
    // Replace word
    importFile(DOCUMENT, archiveDirectory);

    // No tread as end of line
    importFile(SENTENCE, archiveDirectory);

    // Two upper letter
    importFile(WORD, archiveDirectory);
}

bool ImportLibreOfficeAutocorrection::importFile(Type type, const KArchiveDirectory *archiveDirectory)
{
    const KArchiveEntry *documentList = nullptr;

    QString archiveFileName;
    switch (type) {
    case DOCUMENT:
        archiveFileName = QStringLiteral("DocumentList.xml");
        break;
    case SENTENCE:
        archiveFileName = QStringLiteral("SentenceExceptList.xml");
        break;
    case WORD:
        archiveFileName = QStringLiteral("WordExceptList.xml");
        break;
    default:
        return false;
    }
    documentList = archiveDirectory->entry(archiveFileName);
    if (documentList && documentList->isFile()) {
        const auto archiveFile = static_cast<const KArchiveFile *>(documentList);
        archiveFile->copyTo(mTempDir->path());
        QFile file(mTempDir->path() + QLatin1Char('/') + archiveFileName);
        if (!file.open(QIODevice::ReadOnly)) {
            qCWarning(PIMCOMMON_LOG) << "Impossible to open " << file.fileName();
        }
        QDomDocument doc;
        if (loadDomElement(doc, &file)) {
            QDomElement list = doc.documentElement();
            if (list.isNull()) {
                qCDebug(PIMCOMMON_LOG) << "No list defined in " << type;
            } else {
                for (QDomElement e = list.firstChildElement(); !e.isNull(); e = e.nextSiblingElement()) {
                    const QString tag = e.tagName();
                    if (tag == QLatin1String("block-list:block")) {
                        switch (type) {
                        case DOCUMENT:
                            if (e.hasAttribute(QStringLiteral("block-list:abbreviated-name")) && e.hasAttribute(QStringLiteral("block-list:name"))) {
                                mAutocorrectEntries.insert(e.attribute(QStringLiteral("block-list:abbreviated-name")),
                                                           e.attribute(QStringLiteral("block-list:name")));
                            }
                            break;
                        case SENTENCE:
                            if (e.hasAttribute(QStringLiteral("block-list:abbreviated-name"))) {
                                mTwoUpperLetterExceptions.insert(e.attribute(QStringLiteral("block-list:abbreviated-name")));
                            }

                            break;
                        case WORD:
                            if (e.hasAttribute(QStringLiteral("block-list:abbreviated-name"))) {
                                mUpperCaseExceptions.insert(e.attribute(QStringLiteral("block-list:abbreviated-name")));
                            }
                            break;
                        }
                    } else {
                        qCDebug(PIMCOMMON_LOG) << " unknown tag " << tag;
                    }
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

bool ImportLibreOfficeAutocorrection::loadDomElement(QDomDocument &doc, QFile *file)
{
    QString errorMsg;
    int errorRow;
    int errorCol;
    if (!doc.setContent(file, &errorMsg, &errorRow, &errorCol)) {
        qCDebug(PIMCOMMON_LOG) << "Unable to load document.Parse error in line " << errorRow << ", col " << errorCol << ": " << errorMsg;
        return false;
    }
    return true;
}
