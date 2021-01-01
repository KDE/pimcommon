/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemaillist.h"
#include "pimcommonakonadi_debug.h"

#include <QPainter>
#include <QEvent>
#include <KLocalizedString>
#include <KEmailAddress>
using namespace PimCommon;

BlackListBalooEmailList::BlackListBalooEmailList(QWidget *parent)
    : QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSortingEnabled(true);
}

BlackListBalooEmailList::~BlackListBalooEmailList()
{
}

void BlackListBalooEmailList::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        generalPaletteChanged();
    }
    QListWidget::changeEvent(event);
}

void BlackListBalooEmailList::setEmailBlackList(const QStringList &list)
{
    mEmailBlackList = list;
}

QHash<QString, bool> BlackListBalooEmailList::blackListItemChanged() const
{
    QHash<QString, bool> result;
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *element = item(i);
        auto *blackListItem = static_cast<PimCommon::BlackListBalooEmailListItem *>(element);
        bool currentStatus = (blackListItem->checkState() == Qt::Checked);
        if (blackListItem->initializeStatus() != currentStatus) {
            result.insert(blackListItem->text(), currentStatus);
        }
    }
    return result;
}

void BlackListBalooEmailList::setExcludeDomain(const QStringList &domain)
{
    mExcludeDomain = domain;
}

int BlackListBalooEmailList::setEmailFound(const QStringList &list)
{
    mFirstResult = true;
    clear();
    QStringList emailsAdded;
    QStringList emailsLower;
    QStringList onlyEmails;
    for (const QString &mail : list) {
        bool excludeDomain = false;
        QString email, name;
        KEmailAddress::extractEmailAddressAndName(mail, email, name);

        const QString mailToLower = mail.toLower();
        const QString emailToLower = email.toLower();
        for (const QString &domain : qAsConst(mExcludeDomain)) {
            if (email.endsWith(domain)) {
                excludeDomain = true;
                break;
            }
        }
        if (excludeDomain) {
            continue;
        }
        if (!emailsAdded.contains(mail) && !emailsLower.contains(mailToLower) && !onlyEmails.contains(emailToLower)) {
            auto *item = new BlackListBalooEmailListItem(this);
            if (mEmailBlackList.contains(mail)) {
                item->setCheckState(Qt::Checked);
                item->setInitializeStatus(true);
            } else {
                item->setCheckState(Qt::Unchecked);
            }
            item->setText(mail);
            emailsAdded << mail;
            emailsLower << mailToLower;
            onlyEmails << emailToLower;
        }
    }
    return count();
}

void BlackListBalooEmailList::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void BlackListBalooEmailList::paintEvent(QPaintEvent *event)
{
    if (mFirstResult && (!model() || model()->rowCount() == 0)) {
        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, i18n("No result found"));
    } else {
        QListWidget::paintEvent(event);
    }
}

BlackListBalooEmailListItem::BlackListBalooEmailListItem(QListWidget *parent)
    : QListWidgetItem(parent)
    , mInitializeStatus(false)
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
}

BlackListBalooEmailListItem::~BlackListBalooEmailListItem()
{
}

bool BlackListBalooEmailListItem::initializeStatus() const
{
    return mInitializeStatus;
}

void BlackListBalooEmailListItem::setInitializeStatus(bool initializeStatus)
{
    mInitializeStatus = initializeStatus;
}
