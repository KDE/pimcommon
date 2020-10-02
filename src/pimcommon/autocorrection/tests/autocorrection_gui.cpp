/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrection_gui.h"
#include "autocorrection/autocorrection.h"
#include "autocorrection/autocorrectionwidget.h"
#include "autocorrection/widgets/lineeditwithautocorrection.h"
#include "settings/pimcommonsettings.h"

#include "pimcommon_debug.h"

#include <KSharedConfig>

#include <QPointer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QCommandLineParser>
#include <QDialogButtonBox>

ConfigureTestDialog::ConfigureTestDialog(PimCommon::AutoCorrection *autoCorrection, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(QStringLiteral("Configure Autocorrection"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfigureTestDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfigureTestDialog::reject);

    buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);

    mWidget = new PimCommon::AutoCorrectionWidget(this);
    mainLayout->addWidget(mWidget);
    mainLayout->addWidget(buttonBox);

    mWidget->setAutoCorrection(autoCorrection);
    mWidget->loadConfig();
    connect(okButton, &QPushButton::clicked, this, &ConfigureTestDialog::slotSaveSettings);
}

ConfigureTestDialog::~ConfigureTestDialog()
{
}

void ConfigureTestDialog::slotSaveSettings()
{
    mWidget->writeConfig();
}

TextEditAutoCorrectionWidget::TextEditAutoCorrectionWidget(PimCommon::AutoCorrection *autoCorrection, QWidget *parent)
    : QTextEdit(parent)
    , mAutoCorrection(autoCorrection)
{
    setAcceptRichText(false);
}

TextEditAutoCorrectionWidget::~TextEditAutoCorrectionWidget()
{
}

void TextEditAutoCorrectionWidget::keyPressEvent(QKeyEvent *e)
{
    if ((e->key() == Qt::Key_Space) || (e->key() == Qt::Key_Enter) || (e->key() == Qt::Key_Return)) {
        if (mAutoCorrection && mAutoCorrection->isEnabledAutoCorrection()) {
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
    PimCommon::PimCommonSettings::self()->setSharedConfig(mConfig);
    PimCommon::PimCommonSettings::self()->load();

    mAutoCorrection = new PimCommon::AutoCorrection;
    QVBoxLayout *lay = new QVBoxLayout(this);
    QToolBar *bar = new QToolBar;
    lay->addWidget(bar);
    bar->addAction(QStringLiteral("Configure..."), this, &AutocorrectionTestWidget::slotConfigure);
    QAction *richText = new QAction(QStringLiteral("HTML mode"), this);
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
        PimCommon::PimCommonSettings::self()->save();
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

    AutocorrectionTestWidget *w = new AutocorrectionTestWidget();
    w->resize(800, 600);

    w->show();
    const int ret = app.exec();
    delete w;
    return ret;
}
