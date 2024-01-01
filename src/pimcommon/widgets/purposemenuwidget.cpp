/*
  SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "purposemenuwidget.h"
#include <KLocalizedString>
#include <Purpose/AlternativesModel>
#include <Purpose/Menu>
#include <QJsonArray>
#include <QTemporaryFile>
#include <QUrl>

using namespace PimCommon;
PurposeMenuWidget::PurposeMenuWidget(QWidget *parentWidget, QObject *parent)
    : QObject(parent)
    , mParentWidget(parentWidget)
{
    mShareMenu = new Purpose::Menu(mParentWidget);
    mShareMenu->setObjectName(QLatin1StringView("purposesharemenu"));
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
    mShareMenu->model()->setInputData(QJsonObject{{QStringLiteral("urls"), QJsonArray{{QUrl::fromLocalFile(mTemporaryShareFile->fileName()).toString()}}},
                                                  {QStringLiteral("mimeType"), {QStringLiteral("text/plain")}}});
    mShareMenu->model()->setPluginType(QStringLiteral("Export"));
    mShareMenu->reload();
}

void PurposeMenuWidget::slotShareActionFinished(const QJsonObject &output, int error, const QString &message)
{
    if (error) {
        Q_EMIT shareError(i18n("There was a problem sharing the document: %1", message));
    } else {
        const QString url = output[QLatin1String("url")].toString();
        if (url.isEmpty()) {
            Q_EMIT shareSuccess(i18n("File was shared."));
        } else {
            Q_EMIT shareSuccess(i18n("<qt>You can find the new request at:<br /><a href='%1'>%1</a> </qt>", url));
        }
    }
}

#include "moc_purposemenuwidget.cpp"
