/** -*- c++ -*-
 * completionordereditor.cpp
 *
 *  SPDX-FileCopyrightText: 2004 David Faure <faure@kde.org>
 *  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "completionordereditor.h"
#include "completionorderwidget.h"
#include <KLDAP/LdapClient>
#include <KLDAP/LdapClientSearch>

#include <kldap/ldapserver.h>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace PimCommon;

class PimCommon::CompletionOrderEditorPrivate
{
public:
    CompletionOrderEditorPrivate() = default;

    CompletionOrderWidget *mCompletionOrderWidget = nullptr;
};

CompletionOrderEditor::CompletionOrderEditor(KLDAP::LdapClientSearch *ldapSearch, QWidget *parent)
    : QDialog(parent)
    , d(new PimCommon::CompletionOrderEditorPrivate)
{
    setWindowTitle(i18nc("@title:window", "Edit Completion Order"));
    auto mainLayout = new QVBoxLayout(this);

    d->mCompletionOrderWidget = new CompletionOrderWidget(this);
    d->mCompletionOrderWidget->setObjectName(QStringLiteral("completionorderwidget"));

    mainLayout->addWidget(d->mCompletionOrderWidget);

    d->mCompletionOrderWidget->setLdapClientSearch(ldapSearch);

    d->mCompletionOrderWidget->loadCompletionItems();

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CompletionOrderEditor::slotOk);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CompletionOrderEditor::reject);
    mainLayout->addWidget(buttonBox);

    readConfig();
}

CompletionOrderEditor::~CompletionOrderEditor()
{
    writeConfig();
}

void CompletionOrderEditor::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "CompletionOrderEditor");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void CompletionOrderEditor::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "CompletionOrderEditor");
    group.writeEntry("Size", size());
    group.sync();
}

void CompletionOrderEditor::slotOk()
{
    d->mCompletionOrderWidget->save();
    accept();
}
