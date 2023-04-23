/*
  SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrection_gui.h"
#include <PimCommon/LineEditWithAutoCorrection>
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
#include <TextAutoCorrectionCore/AutoCorrection>
#include <TextAutoCorrectionWidgets/AutoCorrectionWidget>
#include <textautocorrectioncore/textautocorrectionsettings.h>
#else
#include <TextAutoCorrection/AutoCorrection>
#include <textautocorrection/textautocorrectionsettings.h>
#endif

#include <QAction>
#include <QApplication>
#include <QCommandLineParser>
#include <QDialogButtonBox>
#include <QKeyEvent>
#include <QPointer>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
ConfigureTestDialog::ConfigureTestDialog(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent)
#else
ConfigureTestDialog::ConfigureTestDialog(TextAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent)
#endif
    : QDialog(parent)
{
    setWindowTitle(QStringLiteral("Configure Autocorrection"));
    auto mainLayout = new QVBoxLayout(this);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfigureTestDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfigureTestDialog::reject);

    buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    mWidget = new TextAutoCorrectionWidgets::AutoCorrectionWidget(this);
#else
    mWidget = new TextAutoCorrection::AutoCorrectionWidget(this);
#endif
    mainLayout->addWidget(mWidget);
    mainLayout->addWidget(buttonBox);

    mWidget->setAutoCorrection(autoCorrection);
    mWidget->loadConfig();
    connect(okButton, &QPushButton::clicked, this, &ConfigureTestDialog::slotSaveSettings);
}

ConfigureTestDialog::~ConfigureTestDialog() = default;

void ConfigureTestDialog::slotSaveSettings()
{
    mWidget->writeConfig();
}

#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
TextEditAutoCorrectionWidget::TextEditAutoCorrectionWidget(TextAutoCorrectionCore::AutoCorrection *autoCorrection, QWidget *parent)
#else
TextEditAutoCorrectionWidget::TextEditAutoCorrectionWidget(TextAutoCorrection::AutoCorrection *autoCorrection, QWidget *parent)
#endif
    : QTextEdit(parent)
    , mAutoCorrection(autoCorrection)
{
    setAcceptRichText(false);
}

TextEditAutoCorrectionWidget::~TextEditAutoCorrectionWidget() = default;

void TextEditAutoCorrectionWidget::keyPressEvent(QKeyEvent *e)
{
    if ((e->key() == Qt::Key_Space) || (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
        if (mAutoCorrection && mAutoCorrection->autoCorrectionSettings()->isEnabledAutoCorrection()) {
            const QTextCharFormat initialTextFormat = textCursor().charFormat();
            int position = textCursor().position();
            mAutoCorrection->autocorrect(acceptRichText(), *document(), position);
            QTextCursor cur = textCursor();
            cur.setPosition(position);

            const QChar insertChar = (e->key() == Qt::Key_Space) ? QLatin1Char(' ') : QLatin1Char('\n');
            cur.insertText(insertChar, initialTextFormat);
            setTextCursor(cur);
            return;
        }
    }
    QTextEdit::keyPressEvent(e);
}

AutocorrectionTestWidget::AutocorrectionTestWidget(QWidget *parent)
    : QWidget(parent)
    , mConfig(KSharedConfig::openConfig(QStringLiteral("autocorrectionguirc")))
{
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setSharedConfig(mConfig);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->load();
    mAutoCorrection = new TextAutoCorrectionCore::AutoCorrection;
#else
    TextAutoCorrection::TextAutoCorrectionSettings::self()->setSharedConfig(mConfig);
    TextAutoCorrection::TextAutoCorrectionSettings::self()->load();
    mAutoCorrection = new TextAutoCorrection::AutoCorrection;
#endif

    auto lay = new QVBoxLayout(this);
    auto bar = new QToolBar;
    lay->addWidget(bar);
    bar->addAction(QStringLiteral("Configure..."), this, &AutocorrectionTestWidget::slotConfigure);
    auto richText = new QAction(QStringLiteral("HTML mode"), this);
    richText->setCheckable(true);
    connect(richText, &QAction::toggled, this, &AutocorrectionTestWidget::slotChangeMode);
    bar->addAction(richText);

    mSubject = new PimCommon::LineEditWithAutoCorrection(this, QStringLiteral("autocorrectionguirc"));
    mSubject->setAutocorrection(mAutoCorrection);
    lay->addWidget(mSubject);

    mEdit = new TextEditAutoCorrectionWidget(mAutoCorrection);
    lay->addWidget(mEdit);
}

AutocorrectionTestWidget::~AutocorrectionTestWidget()
{
    mAutoCorrection->writeConfig();
    delete mAutoCorrection;
}

void AutocorrectionTestWidget::slotChangeMode(bool mode)
{
    mEdit->setAcceptRichText(mode);
}

void AutocorrectionTestWidget::slotConfigure()
{
    QPointer<ConfigureTestDialog> dlg = new ConfigureTestDialog(mAutoCorrection, this);
    if (dlg->exec()) {
#if HAVE_TEXT_AUTOCORRECTION_WIDGETS
        TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->save();
#else
        TextAutoCorrection::TextAutoCorrectionSettings::self()->save();
#endif
    }
    delete dlg;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    auto w = new AutocorrectionTestWidget();
    w->resize(800, 600);

    w->show();
    const int ret = app.exec();
    delete w;
    return ret;
}
