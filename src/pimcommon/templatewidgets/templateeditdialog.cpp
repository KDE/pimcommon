/*
  SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templateeditdialog.h"
#include <KPIMTextEdit/PlainTextEditorWidget>
#include <KPIMTextEdit/PlainTextEditor>
#include <Libkdepim/LineEditCatchReturnKey>

#include <KLocalizedString>
#include <QLineEdit>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <KSharedConfig>
#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace PimCommon;

TemplateEditDialog::TemplateEditDialog(QWidget *parent, bool defaultTemplate)
    : QDialog(parent)
{
    setWindowTitle(defaultTemplate ? i18n("Default template") : i18n("Template"));
    auto mainLayout = new QVBoxLayout(this);
    QDialogButtonBox *buttonBox = nullptr;
    if (defaultTemplate) {
        buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &TemplateEditDialog::reject);
    } else {
        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        mOkButton = buttonBox->button(QDialogButtonBox::Ok);
        mOkButton->setDefault(true);
        mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &TemplateEditDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &TemplateEditDialog::reject);
        mOkButton->setFocus();
    }
    auto w = new QWidget;
    mainLayout->addWidget(w);
    mainLayout->addWidget(buttonBox);

    auto vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);

    auto hbox = new QHBoxLayout;
    auto label = new QLabel(i18n("Name:"));
    hbox->addWidget(label);

    mTemplateNameEdit = new QLineEdit;
    new KPIM::LineEditCatchReturnKey(mTemplateNameEdit, this);
    mTemplateNameEdit->setClearButtonEnabled(!defaultTemplate);
    mTemplateNameEdit->setReadOnly(defaultTemplate);
    hbox->addWidget(mTemplateNameEdit);

    vbox->addLayout(hbox);

    mTextEdit = new KPIMTextEdit::PlainTextEditorWidget;
    mTextEdit->setReadOnly(defaultTemplate);
    vbox->addWidget(mTextEdit);

    w->setLayout(vbox);
    if (!defaultTemplate) {
        if (mOkButton) {
            mOkButton->setEnabled(false);
        }
        connect(mTemplateNameEdit, &QLineEdit::textChanged, this, &TemplateEditDialog::slotTemplateChanged);
        connect(mTextEdit->editor(), &QPlainTextEdit::textChanged, this, &TemplateEditDialog::slotTemplateChanged);
        mTemplateNameEdit->setFocus();
    }
    readConfig();
}

TemplateEditDialog::~TemplateEditDialog()
{
    writeConfig();
}

void TemplateEditDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "TemplateEditDialog");
    group.writeEntry("Size", size());
}

void TemplateEditDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "TemplateEditDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(600, 400));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void TemplateEditDialog::slotTemplateChanged()
{
    mOkButton->setEnabled(!mTemplateNameEdit->text().trimmed().isEmpty() && !mTextEdit->editor()->toPlainText().trimmed().isEmpty());
}

void TemplateEditDialog::setScript(const QString &text)
{
    mTextEdit->setPlainText(text);
}

QString TemplateEditDialog::script() const
{
    return mTextEdit->toPlainText();
}

void TemplateEditDialog::setTemplateName(const QString &name)
{
    mTemplateNameEdit->setText(name);
}

QString TemplateEditDialog::templateName() const
{
    return mTemplateNameEdit->text();
}
