/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewmessagewidget.h"

#include "whatsnewdialog.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
using namespace PimCommon;
WhatsNewMessageWidget::WhatsNewMessageWidget(QWidget *parent, const QString &applicationName)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(true);
    setMessageType(Information);

    mApplicationName = applicationName;
    setText(i18n("What's new in %2. %1", QStringLiteral("<a href=\"show_whats_new\">%1</a>").arg(i18n("(Show News)")), mApplicationName));
    setPosition(KMessageWidget::Header);
    connect(this, &KMessageWidget::linkActivated, this, &WhatsNewMessageWidget::slotLinkActivated);
}

WhatsNewMessageWidget::~WhatsNewMessageWidget() = default;

void WhatsNewMessageWidget::slotLinkActivated(const QString &contents)
{
    if (contents == "show_whats_new"_L1) {
        WhatsNewDialog dlg(mWhatsNewInfos, this, mApplicationName);
        dlg.updateInformations();
        dlg.exec();
    }
}

void WhatsNewMessageWidget::setWhatsNewInfos(const QList<PimCommon::WhatsNewInfo> &infos)
{
    mWhatsNewInfos = infos;
}

#include "moc_whatsnewmessagewidget.cpp"
