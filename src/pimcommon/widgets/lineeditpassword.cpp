/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  based on lineedit in kpassworddialog.cpp

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "lineeditpassword.h"

#include <KLocalizedString>
#include <QIcon>
#include <QAction>
#include <QHBoxLayout>
#include <QLineEdit>

using namespace PimCommon;

class PimCommon::LineEditPassword::LineEditPasswordPrivate : public QObject
{
    Q_OBJECT
public:
    LineEditPasswordPrivate(LineEditPassword *qq)
        : q(qq)
    {

    }
    void initialize();
    void toggleEchoMode();
    void showToggleEchoModeAction(const QString &text);

    QLineEdit *mPasswordLineEdit = nullptr;
    QAction *mToggleEchoModeAction = nullptr;
    bool mIsToggleEchoModeAvailable = true;
    LineEditPassword *q;
};

void LineEditPassword::LineEditPasswordPrivate::initialize()
{
    QIcon visibilityIcon = QIcon::fromTheme(QStringLiteral("visibility"), QIcon(QStringLiteral(":/icons/visibility.svg")));
    mToggleEchoModeAction = mPasswordLineEdit->addAction(visibilityIcon, QLineEdit::TrailingPosition);
    mToggleEchoModeAction->setObjectName(QStringLiteral("visibilityAction"));
    mToggleEchoModeAction->setVisible(false);
    mToggleEchoModeAction->setToolTip(i18n("Change the visibility of the password"));

    connect(mToggleEchoModeAction, &QAction::triggered, this, &LineEditPassword::LineEditPasswordPrivate::toggleEchoMode);
    connect(mPasswordLineEdit, &QLineEdit::textChanged, this, &LineEditPassword::LineEditPasswordPrivate::showToggleEchoModeAction);
}

void LineEditPassword::LineEditPasswordPrivate::showToggleEchoModeAction(const QString &text)
{
    mToggleEchoModeAction->setVisible(mIsToggleEchoModeAvailable && (mPasswordLineEdit->echoMode() == QLineEdit::Normal || !text.isEmpty()));
}

void LineEditPassword::LineEditPasswordPrivate::toggleEchoMode()
{
    if (mPasswordLineEdit->echoMode() == QLineEdit::Password) {
        mPasswordLineEdit->setEchoMode(QLineEdit::Normal);
        mToggleEchoModeAction->setIcon(QIcon::fromTheme(QStringLiteral("hint"), QIcon(QStringLiteral(":/icons/hint.svg"))));
    } else if (mPasswordLineEdit->echoMode() == QLineEdit::Normal) {
        mPasswordLineEdit->setEchoMode(QLineEdit::Password);
        mToggleEchoModeAction->setIcon(QIcon::fromTheme(QStringLiteral("visibility"), QIcon(QStringLiteral(":/icons/visibility.svg"))));
    }
}

LineEditPassword::LineEditPassword(QWidget *parent)
    : QWidget(parent)
    , d(new LineEditPasswordPrivate(this))
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);
    d->mPasswordLineEdit = new QLineEdit(this);
    d->mPasswordLineEdit->setObjectName(QStringLiteral("passwordlineedit"));
    d->mPasswordLineEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(d->mPasswordLineEdit);
    d->initialize();
}

LineEditPassword::~LineEditPassword()
{
    delete d;
}

void LineEditPassword::setPassword(const QString &p)
{
    d->mIsToggleEchoModeAvailable = p.isEmpty();
    d->mPasswordLineEdit->setText(p);
}

QString LineEditPassword::password() const
{
    return d->mPasswordLineEdit->text();
}


QLineEdit *LineEditPassword::passwordLineEdit() const
{
    return d->mPasswordLineEdit;
}

QAction *LineEditPassword::toggleEchoModeAction() const
{
    return d->mToggleEchoModeAction;
}

#include "lineeditpassword.moc"
