/** -*- c++ -*-
 * completionordereditor.cpp
 *
 *  SPDX-FileCopyrightText: 2004 David Faure <faure@kde.org>
 *  SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "completionordereditor.h"
using namespace Qt::Literals::StringLiterals;

#include "completionorderwidget.h"
#include <KLDAPCore/LdapClient>
#include <KLDAPWidgets/LdapClientSearch>

#include <kldapcore/ldapserver.h>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

using namespace PimCommon;
namespace
{
static const char myCompletionOrderEditorGroupName[] = "CompletionOrderEditor";
}
class PimCommon::CompletionOrderEditorPrivate
{
public:
    CompletionOrderEditorPrivate() = default;

    CompletionOrderWidget *mCompletionOrderWidget = nullptr;
};

CompletionOrderEditor::CompletionOrderEditor(KLDAPWidgets::LdapClientSearch *ldapSearch, QWidget *parent)
    : QDialog(parent)
    , d(new PimCommon::CompletionOrderEditorPrivate)
{
    setWindowTitle(i18nc("@title:window", "Edit Completion Order"));
    auto mainLayout = new QVBoxLayout(this);

    d->mCompletionOrderWidget = new CompletionOrderWidget(this);
    d->mCompletionOrderWidget->setObjectName("completionorderwidget"_L1);

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
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myCompletionOrderEditorGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void CompletionOrderEditor::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myCompletionOrderEditorGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void CompletionOrderEditor::slotOk()
{
    d->mCompletionOrderWidget->save();
    accept();
}

#include "moc_completionordereditor.cpp"
