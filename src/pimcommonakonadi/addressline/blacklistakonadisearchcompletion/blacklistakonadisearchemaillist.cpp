/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistakonadisearchemaillist.h"

#include <KEmailAddress>
#include <KLocalizedString>
#include <QEvent>
#include <QPainter>
using namespace PimCommon;

BlackListAkonadiSearchEmailList::BlackListAkonadiSearchEmailList(QWidget *parent)
    : QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSortingEnabled(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

BlackListAkonadiSearchEmailList::~BlackListAkonadiSearchEmailList() = default;

void BlackListAkonadiSearchEmailList::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        generalPaletteChanged();
    }
    QListWidget::changeEvent(event);
}

void BlackListAkonadiSearchEmailList::setEmailBlackList(const QStringList &list)
{
    mEmailBlackList = list;
}

QHash<QString, bool> BlackListAkonadiSearchEmailList::blackListItemChanged() const
{
    QHash<QString, bool> result;
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *element = item(i);
        auto blackListItem = static_cast<PimCommon::BlackListAkonadiSearchEmailListItem *>(element);
        bool currentStatus = (blackListItem->checkState() == Qt::Checked);
        if (blackListItem->initializeStatus() != currentStatus) {
            result.insert(blackListItem->text(), currentStatus);
        }
    }
    return result;
}

void BlackListAkonadiSearchEmailList::setExcludeDomains(const QStringList &domain)
{
    mExcludeDomains = domain;
}

int BlackListAkonadiSearchEmailList::setEmailFound(const QStringList &list)
{
    mFirstResult = true;
    clear();
    QStringList emailsAdded;
    QStringList emailsLower;
    QStringList onlyEmails;
    for (const QString &mail : list) {
        bool excludeEmail = false;
        QString email;
        QString name;
        KEmailAddress::extractEmailAddressAndName(mail, email, name);

        const QString mailToLower = mail.toLower();
        const QString emailToLower = email.toLower();
        for (const QString &domain : std::as_const(mExcludeDomains)) {
            if (email.endsWith(domain)) {
                excludeEmail = true;
                break;
            }
        }
        if (!excludeEmail) {
            // Make it static
            for (const QString &excludeEmailRegularExpression : std::as_const(mExcludeEmailsRegularExpressions)) {
                if (!excludeEmailRegularExpression.isEmpty()) {
                    if (email.contains(QRegularExpression(excludeEmailRegularExpression))) {
                        excludeEmail = true;
                        continue;
                    }
                }
            }
        }
        if (excludeEmail) {
            continue;
        }
        if (!emailsAdded.contains(mail) && !emailsLower.contains(mailToLower) && !onlyEmails.contains(emailToLower)) {
            auto item = new BlackListAkonadiSearchEmailListItem(this);
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

void BlackListAkonadiSearchEmailList::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void BlackListAkonadiSearchEmailList::setExcludeEmailsRegularExpressions(const QStringList &newExcludeEmailsRegularExpressions)
{
    mExcludeEmailsRegularExpressions = newExcludeEmailsRegularExpressions;
}

void BlackListAkonadiSearchEmailList::paintEvent(QPaintEvent *event)
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

BlackListAkonadiSearchEmailListItem::BlackListAkonadiSearchEmailListItem(QListWidget *parent)
    : QListWidgetItem(parent)
    , mInitializeStatus(false)
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
}

BlackListAkonadiSearchEmailListItem::~BlackListAkonadiSearchEmailListItem() = default;

bool BlackListAkonadiSearchEmailListItem::initializeStatus() const
{
    return mInitializeStatus;
}

void BlackListAkonadiSearchEmailListItem::setInitializeStatus(bool initializeStatus)
{
    mInitializeStatus = initializeStatus;
}

#include "moc_blacklistakonadisearchemaillist.cpp"
