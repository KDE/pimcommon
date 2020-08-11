/*
  SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "purposemenuwidget.h"
#include <Purpose/AlternativesModel>
#include <PurposeWidgets/Menu>
#include <QJsonArray>
#include <QTemporaryFile>
#include <KMessageBox>
#include <KLocalizedString>
#include <QUrl>

using namespace PimCommon;
PurposeMenuWidget::PurposeMenuWidget(QWidget *parentWidget, QObject *parent)
    : QObject(parent)
    , mParentWidget(parentWidget)
{
    mShareMenu = new Purpose::Menu(mParentWidget);
    mShareMenu->setObjectName(QStringLiteral("purposesharemenu"));
    mShareMenu->model()->setPluginType(QStringLiteral("Export"));
    connect(mShareMenu, &Purpose::Menu::aboutToShow, this, &PurposeMenuWidget::slotInitializeShareMenu);
    connect(mShareMenu, &Purpose::Menu::finished, this, &PurposeMenuWidget::slotShareActionFinished);
}

PurposeMenuWidget::~PurposeMenuWidget()
{
    delete mTemporaryShareFile;
}

QMenu *PurposeMenuWidget::menu() const
{
    return mShareMenu;
}

void PurposeMenuWidget::slotInitializeShareMenu()
{
    delete mTemporaryShareFile;
    mTemporaryShareFile = new QTemporaryFile();
    mTemporaryShareFile->open();
    mTemporaryShareFile->setPermissions(QFile::ReadUser);
    mTemporaryShareFile->write(text());
    mTemporaryShareFile->close();
    mShareMenu->model()->setInputData(QJsonObject {
        { QStringLiteral("urls"), QJsonArray { {QUrl::fromLocalFile(mTemporaryShareFile->fileName()).toString()} } },
        { QStringLiteral("mimeType"), { QStringLiteral("text/plain") } }
    });
    mShareMenu->reload();
}

void PurposeMenuWidget::slotShareActionFinished(const QJsonObject &output, int error, const QString &message)
{
    if (error) {
        KMessageBox::error(mParentWidget, i18n("There was a problem sharing the document: %1", message),
                           i18n("Share"));
    } else {
        const QString url = output[QLatin1String("url")].toString();
        if (url.isEmpty()) {
            KMessageBox::information(mParentWidget, i18n("File was shared."));
        } else {
            KMessageBox::information(mParentWidget, i18n("<qt>You can find the new request at:<br /><a href='%1'>%1</a> </qt>", url),
                                     QString(), QString(), KMessageBox::AllowLink);
        }
    }
}
