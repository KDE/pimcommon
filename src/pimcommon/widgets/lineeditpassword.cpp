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

    QIcon passwordIcon;
    QIcon visibleIcon;

    QLineEdit *passwordLineEdit = nullptr;
    QAction *toggleEchoModeAction = nullptr;
    bool isToggleEchoModeAvailable = true;
    LineEditPassword *q;
};

void LineEditPassword::LineEditPasswordPrivate::initialize()
{
    QIcon visibilityIcon = QIcon::fromTheme(QStringLiteral("visibility"), QIcon(QStringLiteral(":/icons/visibility.svg")));
    toggleEchoModeAction = passwordLineEdit->addAction(visibilityIcon, QLineEdit::TrailingPosition);
    toggleEchoModeAction->setObjectName(QStringLiteral("visibilityAction"));
    toggleEchoModeAction->setVisible(false);
    toggleEchoModeAction->setToolTip(i18n("Change the visibility of the password"));

    connect(toggleEchoModeAction, &QAction::triggered, this, &LineEditPassword::LineEditPasswordPrivate::toggleEchoMode);
    connect(passwordLineEdit, &QLineEdit::textChanged, this, &LineEditPassword::LineEditPasswordPrivate::showToggleEchoModeAction);
}

void LineEditPassword::LineEditPasswordPrivate::showToggleEchoModeAction(const QString &text)
{
    toggleEchoModeAction->setVisible(isToggleEchoModeAvailable && (passwordLineEdit->echoMode() == QLineEdit::Normal || !text.isEmpty()));
}

void LineEditPassword::LineEditPasswordPrivate::toggleEchoMode()
{
    if (passwordLineEdit->echoMode() == QLineEdit::Password) {
        passwordLineEdit->setEchoMode(QLineEdit::Normal);
        if (passwordIcon.isNull()) {
            passwordIcon = QIcon::fromTheme(QStringLiteral("hint"), QIcon(QStringLiteral(":/icons/hint.svg")));
        }
        toggleEchoModeAction->setIcon(passwordIcon);
    } else if (passwordLineEdit->echoMode() == QLineEdit::Normal) {
        if (visibleIcon.isNull()) {
            visibleIcon = QIcon::fromTheme(QStringLiteral("visibility"), QIcon(QStringLiteral(":/icons/visibility.svg")));
        }
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        toggleEchoModeAction->setIcon(visibleIcon);
    }
}

LineEditPassword::LineEditPassword(QWidget *parent)
    : QWidget(parent)
    , d(new LineEditPasswordPrivate(this))
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);
    d->passwordLineEdit = new QLineEdit(this);
    d->passwordLineEdit->setObjectName(QStringLiteral("passwordlineedit"));
    d->passwordLineEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(d->passwordLineEdit);
    d->initialize();
}

LineEditPassword::~LineEditPassword()
{
    delete d;
}

void LineEditPassword::setPassword(const QString &p)
{
    d->isToggleEchoModeAvailable = p.isEmpty();
    d->passwordLineEdit->setText(p);
}

QString LineEditPassword::password() const
{
    return d->passwordLineEdit->text();
}

QLineEdit *LineEditPassword::passwordLineEdit() const
{
    return d->passwordLineEdit;
}

QAction *LineEditPassword::toggleEchoModeAction() const
{
    return d->toggleEchoModeAction;
}

#include "lineeditpassword.moc"
