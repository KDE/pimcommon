/*******************************************************************************
**
** SPDX-FileCopyrightText: 2005 Till Adam <adam@kde.org>
**
** SPDX-License-Identifier: GPL-2.0-or-later
**
*******************************************************************************/

#include "pimutil.h"
using namespace Qt::Literals::StringLiterals;

#include "imapresourcesettings.h"

#include <KEmailAddress>
#include <KLocalizedString>
#include <KMessageBox>
#include <QDesktopServices>
#include <QFileDialog>

#include <QCoreApplication>
#include <QPointer>
#include <QStandardPaths>
#include <QTextStream>
#include <QUrlQuery>
#include <QWidget>

#include <cerrno>

OrgKdeAkonadiImapSettingsInterface *PimCommon::Util::createImapSettingsInterface(const QString &ident)
{
    if (isImapResource(ident)) {
        return new OrgKdeAkonadiImapSettingsInterface("org.freedesktop.Akonadi.Resource."_L1 + ident,
                                                      QStringLiteral("/Settings"),
                                                      QDBusConnection::sessionBus());
    } else {
        return nullptr;
    }
}

void PimCommon::Util::saveTextAs(const QString &text, const QString &filter, QWidget *parent, const QUrl &url, const QString &caption)
{
    QPointer<QFileDialog> fdlg(new QFileDialog(parent, QString(), url.path(), filter));
    if (!caption.isEmpty()) {
        fdlg->setWindowTitle(caption);
    }
    fdlg->setAcceptMode(QFileDialog::AcceptSave);
    if (fdlg->exec() == QDialog::Accepted) {
        const QString fileName = fdlg->selectedFiles().at(0);
        if (!saveToFile(fileName, text)) {
            KMessageBox::error(parent,
                               i18n("Could not write the file %1:\n"
                                    "\"%2\" is the detailed error description.",
                                    fileName,
                                    QString::fromLocal8Bit(strerror(errno))),
                               i18nc("@title:window", "Save File Error"));
        }
    }
    delete fdlg;
}

bool PimCommon::Util::saveToFile(const QString &filename, const QString &text)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream out(&file);
    out << text;
    file.close();
    return true;
}

QString PimCommon::Util::loadToFile(const QString &filter, QWidget *parent, const QUrl &url, const QString &caption)
{
    QPointer<QFileDialog> fdlg(new QFileDialog(parent, QString(), url.path(), filter));
    if (!caption.isEmpty()) {
        fdlg->setWindowTitle(caption);
    }
    fdlg->setAcceptDrops(QFileDialog::AcceptOpen);
    QString result;
    if (fdlg->exec() == QDialog::Accepted) {
        const QString fileName = fdlg->selectedFiles().at(0);
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            KMessageBox::error(parent,
                               i18n("Could not read the file %1:\n"
                                    "\"%2\" is the detailed error description.",
                                    fileName,
                                    QString::fromLocal8Bit(strerror(errno))),
                               i18nc("@title:window", "Load File Error"));
        } else {
            result = QString::fromUtf8(file.readAll());
            file.close();
        }
    }
    delete fdlg;
    return result;
}

bool PimCommon::Util::isImapResource(const QString &identifier)
{
    return identifier.startsWith(KOLAB_RESOURCE_IDENTIFIER) || identifier.startsWith(IMAP_RESOURCE_IDENTIFIER)
        || identifier.startsWith(GMAIL_RESOURCE_IDENTIFIER);
}

QUrl PimCommon::Util::generateHelpUrl(const QString &docfile, const QString &anchor)
{
    QUrl generatedUrl;
    if (!docfile.isEmpty()) {
        QUrl url;
        url = QUrl(QStringLiteral("help:/")).resolved(QUrl(docfile));
        if (!anchor.isEmpty()) {
            QUrlQuery query(url);
            query.addQueryItem(QStringLiteral("anchor"), anchor);
            url.setQuery(query);
        }
        generatedUrl = std::move(url);
    }
    return generatedUrl;
}

void PimCommon::Util::invokeHelp(const QString &docfile, const QString &anchor)
{
    const QUrl url = generateHelpUrl(docfile, anchor);
    if (!url.isEmpty()) {
        // launch khelpcenter, or a browser for URIs not handled by khelpcenter
        QDesktopServices::openUrl(url);
    }
}

QStringList PimCommon::Util::generateEmailList(const QStringList &list)
{
    QString str;
    const auto numberOfElement{list.count()};
    for (int i = 0; i < numberOfElement; i++) {
        QString tmpStr = list.at(i);
        if (!tmpStr.trimmed().isEmpty()) {
            if (!str.isEmpty()) {
                str.append(", "_L1);
            }
            str.append(tmpStr);
        }
    }
    const QStringList emails = KEmailAddress::splitAddressList(str);
    return emails;
}
