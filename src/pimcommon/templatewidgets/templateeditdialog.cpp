/*
  SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templateeditdialog.h"
#include <KLineEditEventHandler>
#include <TextCustomEditor/PlainTextEditor>
#include <TextCustomEditor/PlainTextEditorWidget>

#include <KLocalizedString>
#include <QLineEdit>

#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

using namespace PimCommon;
namespace
{
static const char myTemplateEditDialogConfigGroupName[] = "TemplateEditDialog";
}
TemplateEditDialog::TemplateEditDialog(QWidget *parent, bool defaultTemplate)
    : QDialog(parent)
    , mTextEdit(new TextCustomEditor::PlainTextEditorWidget(this))
    , mTemplateNameEdit(new QLineEdit(this))
{
    setWindowTitle(defaultTemplate ? i18nc("@title:window", "Default template") : i18nc("@title:window", "Template"));
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
    vbox->setContentsMargins({});

    auto hbox = new QHBoxLayout;
    auto label = new QLabel(i18nc("@label:textbox", "Name:"));
    hbox->addWidget(label);

    KLineEditEventHandler::catchReturnKey(mTemplateNameEdit);
    mTemplateNameEdit->setClearButtonEnabled(!defaultTemplate);
    mTemplateNameEdit->setReadOnly(defaultTemplate);
    hbox->addWidget(mTemplateNameEdit);

    vbox->addLayout(hbox);

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

void TemplateEditDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTemplateEditDialogConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TemplateEditDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTemplateEditDialogConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
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

#include "moc_templateeditdialog.cpp"
