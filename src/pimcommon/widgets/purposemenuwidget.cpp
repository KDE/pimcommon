/*
  Copyright (c) 2018-2019 Montel Laurent <montel@kde.org>

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
