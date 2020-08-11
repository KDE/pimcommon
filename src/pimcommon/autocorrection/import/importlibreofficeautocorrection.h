/*
  SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef IMPORTLIBREOFFICEAUTOCORRECTION_H
#define IMPORTLIBREOFFICEAUTOCORRECTION_H

#include "importabstractautocorrection.h"

class QTemporaryDir;
class KZip;
class QDomDocument;
class QFile;
class KArchiveDirectory;

namespace PimCommon {
class ImportLibreOfficeAutocorrection : public ImportAbstractAutocorrection
{
public:
    explicit ImportLibreOfficeAutocorrection(QWidget *parent = nullptr);
    ~ImportLibreOfficeAutocorrection() override;

    Q_REQUIRED_RESULT bool import(const QString &fileName, ImportAbstractAutocorrection::LoadAttribute loadAttribute = All) override;

private:
    enum Type {
        DOCUMENT,
        SENTENCE,
        WORD
    };

    void importAutoCorrectionFile();
    void closeArchive();
    bool loadDomElement(QDomDocument &doc, QFile *file);
    bool importFile(Type type, const KArchiveDirectory *archiveDirectory);
    KZip *mArchive = nullptr;
    QTemporaryDir *mTempDir = nullptr;
};
}

#endif // IMPORTLIBREOFFICEAUTOCORRECTION_H
