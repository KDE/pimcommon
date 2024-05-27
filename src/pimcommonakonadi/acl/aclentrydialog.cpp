/*
 * SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
 * SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kdab.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "aclentrydialog_p.h"
#include "aclutils_p.h"

#include <PimCommonAkonadi/AddresseeLineEdit>

#include <Akonadi/EmailAddressSelectionDialog>

#include <KLocalizedString>

#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

using namespace PimCommon;

class AclEntryDialog::AclEntryDialogPrivate
{
public:
    AclEntryDialogPrivate(AclEntryDialog *qq)
        : q(qq)
    {
    }

    void slotChanged();
    void slotSelectAddresses();

    AclEntryDialog *const q;
    QButtonGroup *mButtonGroup = nullptr;
    PimCommon::AddresseeLineEdit *mUserIdLineEdit = nullptr;
    QVBoxLayout *mButtonLayout = nullptr;
    KIMAP::Acl::Rights mCustomPermissions;
    QPushButton *mOkButton = nullptr;
};

void AclEntryDialog::AclEntryDialogPrivate::slotChanged()
{
    mOkButton->setEnabled(!mUserIdLineEdit->text().trimmed().isEmpty() && mButtonGroup->checkedButton() != nullptr);
}

void AclEntryDialog::AclEntryDialogPrivate::slotSelectAddresses()
{
    Akonadi::EmailAddressSelectionDialog dlg;

    if (!dlg.exec()) {
        return;
    }

    const QString text = !dlg.selectedAddresses().isEmpty() ? dlg.selectedAddresses().at(0).quotedEmail() : QString();

    mUserIdLineEdit->setText(text);
}

AclEntryDialog::AclEntryDialog(QWidget *parent)
    : QDialog(parent)
    , d(new AclEntryDialogPrivate(this))
{
    auto mainLayout = new QVBoxLayout(this);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    d->mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    d->mOkButton->setDefault(true);
    d->mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AclEntryDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AclEntryDialog::reject);

    auto page = new QWidget(this);
    mainLayout->addWidget(page);
    mainLayout->addWidget(buttonBox);

    auto layout = new QGridLayout(page);
    layout->setContentsMargins({});

    auto label = new QLabel(i18nc("@label:textbox", "&User identifier:"), page);
    layout->addWidget(label, 0, 0);

    d->mUserIdLineEdit = new PimCommon::AddresseeLineEdit(page);
    layout->addWidget(d->mUserIdLineEdit, 0, 1);
    label->setBuddy(d->mUserIdLineEdit);
    d->mUserIdLineEdit->setWhatsThis(i18nc("@info:whatsthis",
                                           "The User Identifier is the login of the user on the IMAP server. "
                                           "This can be a simple user name or the full email address of the user; "
                                           "the login for your own account on the server will tell you which one it is."));

    auto button = new QPushButton(i18nc("select an email address", "Se&lect..."), page);
    layout->addWidget(button, 0, 2);

    auto groupBox = new QGroupBox(i18n("Permissions"), page);
    d->mButtonLayout = new QVBoxLayout(groupBox);

    d->mButtonGroup = new QButtonGroup(groupBox);

    for (unsigned int i = 0; i < AclUtils::standardPermissionsCount(); ++i) {
        const KIMAP::Acl::Rights aclRightPermissions = AclUtils::permissionsForIndex(i);

        auto radioButton = new QRadioButton(AclUtils::permissionsToUserString(aclRightPermissions), groupBox);
        d->mButtonLayout->addWidget(radioButton);
        d->mButtonGroup->addButton(radioButton, aclRightPermissions);
    }

    d->mButtonLayout->addStretch(1);
    layout->addWidget(groupBox, 1, 0, 1, 3);

    label = new QLabel(i18nc("@label:textbox", "<b>Note: </b>Renaming requires write permissions on the parent folder."), page);
    layout->addWidget(label, 2, 0, 1, 3);
    layout->setRowStretch(2, 10);

    connect(d->mUserIdLineEdit, &AddresseeLineEdit::textChanged, this, [this]() {
        d->slotChanged();
    });
    connect(button, &QPushButton::clicked, this, [this]() {
        d->slotSelectAddresses();
    });
    connect(d->mButtonGroup, &QButtonGroup::buttonClicked, this, [this]() {
        d->slotChanged();
    });

    d->mOkButton->setEnabled(false);

    d->mUserIdLineEdit->setFocus();
}

AclEntryDialog::~AclEntryDialog() = default;

void AclEntryDialog::setUserId(const QString &userId)
{
    d->mUserIdLineEdit->setText(userId);

    d->mOkButton->setEnabled(!userId.isEmpty());
}

QString AclEntryDialog::userId() const
{
    return d->mUserIdLineEdit->text();
}

void AclEntryDialog::setPermissions(KIMAP::Acl::Rights permissions)
{
    QAbstractButton *button = d->mButtonGroup->button(KIMAP::Acl::normalizedRights(permissions));

    if (button) {
        button->setChecked(true);
    } else {
        auto radioButton = new QRadioButton(AclUtils::permissionsToUserString(permissions));

        d->mButtonLayout->addWidget(radioButton);
        d->mButtonGroup->addButton(radioButton, permissions);
    }

    d->mCustomPermissions = permissions;
}

KIMAP::Acl::Rights AclEntryDialog::permissions() const
{
    QAbstractButton *button = d->mButtonGroup->checkedButton();

    if (!button) {
        return d->mCustomPermissions;
    }

    return KIMAP::Acl::denormalizedRights(static_cast<KIMAP::Acl::Rights>(d->mButtonGroup->id(button)));
}

#include "moc_aclentrydialog_p.cpp"
