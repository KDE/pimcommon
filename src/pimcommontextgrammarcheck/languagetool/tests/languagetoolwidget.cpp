/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolwidget.h"
#include "languagetool/languagetoolgetlistoflanguagejob.h"
#include "languagetool/languagetoolmanager.h"
#include "languagetool/languagetoolresultjob.h"

#include "languagetool/languagetoolparser.h"
#include "languagetool/languagetoolresultwidget.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QTextBlock>
#include <QTextEdit>
#include <QVBoxLayout>

LanguageToolWidget::LanguageToolWidget(QWidget *parent)
    : QWidget(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    mNetworkAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    mNetworkAccessManager->setStrictTransportSecurityEnabled(true);
    mNetworkAccessManager->enableStrictTransportSecurityStore(true);
    auto mainLayout = new QVBoxLayout(this);

    auto button = new QPushButton(QStringLiteral("Check Grammar"), this);
    mainLayout->addWidget(button);

    auto languageButton = new QPushButton(QStringLiteral("Get List Of Languages"), this);
    mainLayout->addWidget(languageButton);

    mInput = new QTextEdit(this);
    mainLayout->addWidget(mInput);

    mResultWidget = new PimCommonTextGrammarCheck::LanguageToolResultWidget(this);
    mainLayout->addWidget(mResultWidget);
    connect(mResultWidget, &PimCommonTextGrammarCheck::LanguageToolResultWidget::replaceText, this, &LanguageToolWidget::slotReplaceText);

    connect(button, &QPushButton::clicked, this, &LanguageToolWidget::slotCheckGrammar);
    connect(languageButton, &QPushButton::clicked, this, &LanguageToolWidget::slotGetListOfLanguages);
}

LanguageToolWidget::~LanguageToolWidget() = default;

void LanguageToolWidget::slotReplaceText(const PimCommonTextGrammarCheck::GrammarAction &act)
{
    QTextBlock block = mInput->document()->findBlockByNumber(act.blockId() - 1);
    if (block.isValid()) {
        QTextCursor cur(block);
        const int position = cur.position() + act.start();
        cur.setPosition(position);
        cur.setPosition(position + act.length(), QTextCursor::KeepAnchor);
        cur.insertText(act.replacement());
    }
}

void LanguageToolWidget::slotCheckGrammar()
{
    auto job = new PimCommonTextGrammarCheck::LanguageToolResultJob(this);
    job->setUrl(QStringLiteral("https://api.languagetoolplus.com/v2/check"));
    job->setNetworkAccessManager(mNetworkAccessManager);
    job->setText(mInput->toPlainText());
    job->setLanguage(QStringLiteral("fr"));
    connect(job, &PimCommonTextGrammarCheck::LanguageToolResultJob::finished, this, &LanguageToolWidget::slotResultFinished);
    connect(job, &PimCommonTextGrammarCheck::LanguageToolResultJob::error, this, &LanguageToolWidget::slotError);
    job->start();
}

void LanguageToolWidget::slotGetListOfLanguages()
{
    auto job = new PimCommonTextGrammarCheck::LanguageToolGetListOfLanguageJob(this);
    job->setUrl(QStringLiteral("https://api.languagetoolplus.com/v2/languages"));
    job->setNetworkAccessManager(mNetworkAccessManager);
    connect(job, &PimCommonTextGrammarCheck::LanguageToolGetListOfLanguageJob::finished, this, &LanguageToolWidget::slotGetLanguagesFinished);
    connect(job, &PimCommonTextGrammarCheck::LanguageToolGetListOfLanguageJob::error, this, &LanguageToolWidget::slotGetLanguagesError);
    job->start();
}

void LanguageToolWidget::slotError()
{
    qDebug() << " error !!!!";
}

void LanguageToolWidget::slotGetLanguagesError()
{
    qDebug() << " error !!!!";
}

void LanguageToolWidget::slotGetLanguagesFinished(const QString &result)
{
    qDebug() << " result " << result;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonArray fields = doc.array();
    qDebug() << " fields =" << fields;
}

void LanguageToolWidget::slotResultFinished(const QString &result)
{
    qDebug() << " result" << result;
    mResultWidget->setText(mInput->toPlainText());
    PimCommonTextGrammarCheck::LanguageToolParser parser;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonObject fields = doc.object();
    mResultWidget->applyGrammarResult(parser.parseResult(fields));
}
