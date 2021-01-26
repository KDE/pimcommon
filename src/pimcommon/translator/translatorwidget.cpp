/*

  SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorwidget.h"
#include "googletranslator.h"
#include "translatorutil.h"
#include <KBusyIndicatorWidget>
#include <PimCommon/NetworkManager>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSeparator>
#include <QPushButton>

#include <KSharedConfig>
#include <QComboBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QKeyEvent>
#include <QLabel>
#include <QMimeData>
#include <QNetworkConfigurationManager>
#include <QPainter>
#include <QShortcut>
#include <QSplitter>
#include <QToolButton>
#include <QVBoxLayout>

using namespace PimCommon;

class Q_DECL_HIDDEN TranslatorWidget::TranslatorWidgetPrivate
{
public:
    TranslatorWidgetPrivate()
    {
    }

    ~TranslatorWidgetPrivate()
    {
        delete abstractTranslator;
    }

    void initLanguage();
    void fillToCombobox(const QString &lang);

    QMap<QString, QMap<QString, QString>> listLanguage;
    QByteArray data;
    TranslatorTextEdit *inputText = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *translatedText = nullptr;
    TranslatorResultTextEdit *translatorResultTextEdit = nullptr;
    QComboBox *from = nullptr;
    QComboBox *to = nullptr;
    QPushButton *translate = nullptr;
    QPushButton *clear = nullptr;
    PimCommon::GoogleTranslator *abstractTranslator = nullptr;
    KBusyIndicatorWidget *progressIndicator = nullptr;
    QPushButton *invert = nullptr;
    QSplitter *splitter = nullptr;
    bool languageSettingsChanged = false;
    bool standalone = true;
};

void TranslatorWidget::TranslatorWidgetPrivate::fillToCombobox(const QString &lang)
{
    to->clear();
    const QMap<QString, QString> list = listLanguage.value(lang);
    QMap<QString, QString>::const_iterator i = list.constBegin();
    QMap<QString, QString>::const_iterator end = list.constEnd();
    while (i != end) {
        to->addItem(i.key(), i.value());
        ++i;
    }
}

void TranslatorWidget::TranslatorWidgetPrivate::initLanguage()
{
    if (!abstractTranslator) {
        return;
    }
    listLanguage = abstractTranslator->initListLanguage(from);
}

TranslatorResultTextEdit::TranslatorResultTextEdit(QWidget *parent)
    : KPIMTextEdit::PlainTextEditor(parent)
    , mResultFailed(false)
{
    setReadOnly(true);
}

void TranslatorResultTextEdit::setResultFailed(bool failed)
{
    if (mResultFailed != failed) {
        mResultFailed = failed;
        update();
    }
}

void TranslatorResultTextEdit::paintEvent(QPaintEvent *event)
{
    if (mResultFailed) {
        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        p.setPen(Qt::red);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, i18n("Problem when connecting to the translator web site."));
    } else {
        KPIMTextEdit::PlainTextEditor::paintEvent(event);
    }
}

TranslatorTextEdit::TranslatorTextEdit(QWidget *parent)
    : KPIMTextEdit::PlainTextEditor(parent)
{
}

void TranslatorTextEdit::dropEvent(QDropEvent *event)
{
    if (event->source() != this) {
        if (event->mimeData()->hasText()) {
            QTextCursor cursor = textCursor();
            cursor.beginEditBlock();
            cursor.insertText(event->mimeData()->text());
            cursor.endEditBlock();
            event->setDropAction(Qt::CopyAction);
            event->accept();
            Q_EMIT translateText();
            return;
        }
    }
    KPIMTextEdit::PlainTextEditor::dropEvent(event);
}

TranslatorWidget::TranslatorWidget(QWidget *parent)
    : QWidget(parent)
    , d(new TranslatorWidgetPrivate)
{
    init();
}

TranslatorWidget::TranslatorWidget(const QString &text, QWidget *parent)
    : QWidget(parent)
    , d(new TranslatorWidgetPrivate)
{
    init();
    d->inputText->setPlainText(text);
}

TranslatorWidget::~TranslatorWidget()
{
    disconnect(d->inputText, &TranslatorTextEdit::textChanged, this, &TranslatorWidget::slotTextChanged);
    disconnect(d->inputText, &TranslatorTextEdit::translateText, this, &TranslatorWidget::slotTranslate);
    writeConfig();
    delete d;
}

void TranslatorWidget::writeConfig()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), "TranslatorWidget");
    if (d->languageSettingsChanged) {
        myGroup.writeEntry(QStringLiteral("FromLanguage"), d->from->itemData(d->from->currentIndex()).toString());
        myGroup.writeEntry("ToLanguage", d->to->itemData(d->to->currentIndex()).toString());
    }
    myGroup.writeEntry("mainSplitter", d->splitter->sizes());
    myGroup.sync();
}

void TranslatorWidget::readConfig()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), "TranslatorWidget");
    const QString from = myGroup.readEntry(QStringLiteral("FromLanguage"));
    const QString to = myGroup.readEntry(QStringLiteral("ToLanguage"));
    if (from.isEmpty()) {
        return;
    }
    const int indexFrom = d->from->findData(from);
    if (indexFrom != -1) {
        d->from->setCurrentIndex(indexFrom);
    }
    const int indexTo = d->to->findData(to);
    if (indexTo != -1) {
        d->to->setCurrentIndex(indexTo);
    }
    const QList<int> size = {100, 400};
    d->splitter->setSizes(myGroup.readEntry("mainSplitter", size));
    d->invert->setEnabled(from != QLatin1String("auto"));
}

void TranslatorWidget::init()
{
    d->abstractTranslator = new GoogleTranslator();
    d->abstractTranslator->setParentWidget(this);
    connect(d->abstractTranslator, &PimCommon::GoogleTranslator::translateDone, this, &TranslatorWidget::slotTranslateDone);
    connect(d->abstractTranslator, &PimCommon::GoogleTranslator::translateFailed, this, &TranslatorWidget::slotTranslateFailed);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    auto hboxLayout = new QHBoxLayout;
    auto closeBtn = new QToolButton(this);
    closeBtn->setObjectName(QStringLiteral("close-button"));
    closeBtn->setIcon(QIcon::fromTheme(QStringLiteral("dialog-close")));
    closeBtn->setIconSize(QSize(16, 16));
    closeBtn->setToolTip(i18n("Close"));

#ifndef QT_NO_ACCESSIBILITY
    closeBtn->setAccessibleName(i18n("Close"));
#endif
    closeBtn->setAutoRaise(true);
    hboxLayout->addWidget(closeBtn);
    connect(closeBtn, &QToolButton::clicked, this, &TranslatorWidget::slotCloseWidget);

    auto label = new QLabel(i18nc("Translate from language", "From:"));
    hboxLayout->addWidget(label);
    d->from = new QComboBox;
    d->from->setMinimumWidth(50);
    d->from->setObjectName(QStringLiteral("from"));
    hboxLayout->addWidget(d->from);

    label = new QLabel(i18nc("Translate to language", "To:"));
    hboxLayout->addWidget(label);
    d->to = new QComboBox;
    d->to->setMinimumWidth(50);
    d->to->setObjectName(QStringLiteral("to"));

    hboxLayout->addWidget(d->to);

    auto separator = new KSeparator;
    separator->setOrientation(Qt::Vertical);
    hboxLayout->addWidget(separator);

    d->invert = new QPushButton(i18nc("Invert language choices so that from becomes to and to becomes from", "Invert"), this);
    d->invert->setObjectName(QStringLiteral("invert-button"));
    connect(d->invert, &QPushButton::clicked, this, &TranslatorWidget::slotInvertLanguage);
    hboxLayout->addWidget(d->invert);

    d->clear = new QPushButton(i18n("Clear"), this);
    d->clear->setObjectName(QStringLiteral("clear-button"));
#ifndef QT_NO_ACCESSIBILITY
    d->clear->setAccessibleName(i18n("Clear"));
#endif
    connect(d->clear, &QPushButton::clicked, this, &TranslatorWidget::slotClear);
    hboxLayout->addWidget(d->clear);

    d->translate = new QPushButton(i18n("Translate"));
    d->translate->setObjectName(QStringLiteral("translate-button"));
#ifndef QT_NO_ACCESSIBILITY
    d->translate->setAccessibleName(i18n("Translate"));
#endif

    hboxLayout->addWidget(d->translate);
    connect(d->translate, &QPushButton::clicked, this, &TranslatorWidget::slotTranslate);

    if (!qEnvironmentVariableIsEmpty("KDEPIM_DEBUGGING")) {
        auto debugButton = new QPushButton(i18n("Debug"));
        hboxLayout->addWidget(debugButton);
        connect(debugButton, &QPushButton::clicked, this, &TranslatorWidget::slotDebug);
    }

    d->progressIndicator = new KBusyIndicatorWidget(this);
    hboxLayout->addWidget(d->progressIndicator);

    hboxLayout->addItem(new QSpacerItem(5, 5, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum));

    layout->addLayout(hboxLayout);

    d->splitter = new QSplitter;
    d->splitter->setChildrenCollapsible(false);
    d->inputText = new TranslatorTextEdit(this);
    auto editorWidget = new KPIMTextEdit::PlainTextEditorWidget(d->inputText);
    d->inputText->setObjectName(QStringLiteral("inputtext"));
    d->inputText->setPlaceholderText(i18n("Drag text that you want to translate. (Be careful text will be send to Google Server)."));
    connect(d->inputText, &TranslatorTextEdit::textChanged, this, &TranslatorWidget::slotTextChanged);
    connect(d->inputText, &TranslatorTextEdit::translateText, this, &TranslatorWidget::slotTranslate);

    d->splitter->addWidget(editorWidget);
    d->translatorResultTextEdit = new TranslatorResultTextEdit;
    d->translatedText = new KPIMTextEdit::PlainTextEditorWidget(d->translatorResultTextEdit, this);
    d->translatedText->setObjectName(QStringLiteral("translatedtext"));
    d->translatedText->setReadOnly(true);
    d->splitter->addWidget(d->translatedText);

    layout->addWidget(d->splitter);

    d->initLanguage();
    d->from->setCurrentIndex(0); // Fill "to" combobox
    slotFromLanguageChanged(0, true);
    slotTextChanged();
    readConfig();
    connect(d->from, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int val) {
        slotFromLanguageChanged(val, false);
        slotConfigChanged();
    });
    connect(d->to, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() {
        slotConfigChanged();
        slotTranslate();
    });

    hide();
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    d->languageSettingsChanged = false;
}

void TranslatorWidget::slotConfigChanged()
{
    d->languageSettingsChanged = true;
}

void TranslatorWidget::slotTextChanged()
{
    d->translate->setEnabled(!d->inputText->document()->isEmpty());
    d->clear->setEnabled(!d->inputText->document()->isEmpty());
}

void TranslatorWidget::slotFromLanguageChanged(int index, bool initialize)
{
    const QString lang = d->from->itemData(index).toString();
    d->invert->setEnabled(lang != QLatin1String("auto"));
    const QString to = d->to->itemData(d->to->currentIndex()).toString();
    d->to->blockSignals(true);
    d->fillToCombobox(lang);
    d->to->blockSignals(false);
    const int indexTo = d->to->findData(to);
    if (indexTo != -1) {
        d->to->setCurrentIndex(indexTo);
    }
    if (!initialize) {
        slotTranslate();
    }
}

void TranslatorWidget::setTextToTranslate(const QString &text)
{
    d->inputText->setPlainText(text);
    slotTranslate();
}

void TranslatorWidget::slotTranslate()
{
    if (!PimCommon::NetworkManager::self()->networkConfigureManager()->isOnline()) {
        KMessageBox::information(this, i18n("No network connection detected, we cannot translate text."), i18n("No network"));
        return;
    }
    const QString textToTranslate = d->inputText->toPlainText();
    if (textToTranslate.trimmed().isEmpty()) {
        return;
    }

    d->translatorResultTextEdit->clear();

    const QString from = d->from->itemData(d->from->currentIndex()).toString();
    const QString to = d->to->itemData(d->to->currentIndex()).toString();
    d->translate->setEnabled(false);
    d->progressIndicator->show();

    d->abstractTranslator->setFrom(from);
    d->abstractTranslator->setTo(to);
    d->abstractTranslator->setInputText(d->inputText->toPlainText());
    d->abstractTranslator->translate();
}

void TranslatorWidget::slotTranslateDone()
{
    d->translate->setEnabled(true);
    d->progressIndicator->hide();
    d->translatorResultTextEdit->setResultFailed(false);
    d->translatorResultTextEdit->setPlainText(d->abstractTranslator->resultTranslate());
}

void TranslatorWidget::slotTranslateFailed(bool signalFailed, const QString &message)
{
    d->translate->setEnabled(true);
    d->progressIndicator->hide();
    d->translatorResultTextEdit->setResultFailed(signalFailed);
    d->translatorResultTextEdit->clear();
    if (!message.isEmpty()) {
        KMessageBox::error(this, message, i18n("Translate error"));
    }
}

void TranslatorWidget::slotInvertLanguage()
{
    const QString fromLanguage = d->from->itemData(d->from->currentIndex()).toString();
    // don't invert when fromLanguage == auto
    if (fromLanguage == QLatin1String("auto")) {
        return;
    }

    const QString toLanguage = d->to->itemData(d->to->currentIndex()).toString();
    const int indexFrom = d->from->findData(toLanguage);
    if (indexFrom != -1) {
        d->from->setCurrentIndex(indexFrom);
    }
    const int indexTo = d->to->findData(fromLanguage);
    if (indexTo != -1) {
        d->to->setCurrentIndex(indexTo);
    }
    slotTranslate();
}

void TranslatorWidget::setStandalone(bool b)
{
    d->standalone = b;
}

void TranslatorWidget::slotCloseWidget()
{
    if (isHidden()) {
        return;
    }
    d->inputText->clear();
    d->translatorResultTextEdit->clear();
    d->progressIndicator->hide();
    if (d->standalone) {
        hide();
    }
    Q_EMIT toolsWasClosed();
}

bool TranslatorWidget::event(QEvent *e)
{
    // Close the bar when pressing Escape.
    // Not using a QShortcut for this because it could conflict with
    // window-global actions (e.g. Emil Sedgh binds Esc to "close tab").
    // With a shortcut override we can catch this before it gets to kactions.
    if (e->type() == QEvent::ShortcutOverride || e->type() == QEvent::KeyPress) {
        auto kev = static_cast<QKeyEvent *>(e);
        if (kev->key() == Qt::Key_Escape) {
            e->accept();
            slotCloseWidget();
            return true;
        }
    }
    return QWidget::event(e);
}

void TranslatorWidget::slotClear()
{
    d->inputText->clear();
    d->translatorResultTextEdit->clear();
    d->translate->setEnabled(false);
    d->abstractTranslator->clear();
}

void TranslatorWidget::slotDebug()
{
    d->abstractTranslator->debug();
}
