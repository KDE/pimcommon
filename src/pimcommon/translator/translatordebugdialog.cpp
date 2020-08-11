/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatordebugdialog.h"
#include "util/pimutil.h"
#include <KPIMTextEdit/PlainTextEditorWidget>

#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

TranslatorDebugDialog::TranslatorDebugDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Translator Debug"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    mUser1Button = new QPushButton(this);
    buttonBox->addButton(mUser1Button, QDialogButtonBox::ActionRole);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TranslatorDebugDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TranslatorDebugDialog::reject);
    mUser1Button->setText(i18n("Save As..."));
    connect(mUser1Button, &QPushButton::clicked, this, &TranslatorDebugDialog::slotSaveAs);

    mEdit = new KPIMTextEdit::PlainTextEditorWidget(this);
    mEdit->setReadOnly(true);
    mainLayout->addWidget(mEdit);
    mainLayout->addWidget(buttonBox);

    readConfig();
    mUser1Button->setEnabled(!mEdit->isEmpty());
}

TranslatorDebugDialog::~TranslatorDebugDialog()
{
    writeConfig();
}

void TranslatorDebugDialog::setDebug(const QString &debugStr)
{
    mEdit->setPlainText(debugStr);
    mUser1Button->setEnabled(!debugStr.isEmpty());
}

void TranslatorDebugDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "TranslatorDebugDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(800, 600));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void TranslatorDebugDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "TranslatorDebugDialog");
    group.writeEntry("Size", size());
}

void TranslatorDebugDialog::slotSaveAs()
{
    const QString filter = i18n("All Files (*)");
    PimCommon::Util::saveTextAs(mEdit->toPlainText(), filter, this);
}
