/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "genericgrantleeformatter.h"

#include <grantlee/engine.h>

using namespace PimCommon;

class PimCommon::GenericGrantleeFormatterPrivate
{
public:
    GenericGrantleeFormatterPrivate()
    {
        mEngine = new Grantlee::Engine;
    }

    GenericGrantleeFormatterPrivate(const QString &defaultHtmlMain, const QString &themePath)
        : mThemePath(themePath)
        , mDefaultMainFile(defaultHtmlMain)
    {
        initializeEngine();
    }

    ~GenericGrantleeFormatterPrivate()
    {
        delete mEngine;
        mTemplateLoader.clear();
    }

    void setContent(const QString &content);
    void setDefaultHtmlMainFile(const QString &name);
    void initializeEngine();
    void refreshTemplate();
    void changeGrantleePath(const QString &path);
    void insertToContext(const QString &key, const QVariantHash &mapping);
    QString render(const QVariantHash &mapping) const;

    QString mThemePath;
    QString mDefaultMainFile;
    Grantlee::Engine *mEngine = nullptr;
    QString mErrorMessage;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> mTemplateLoader;
    Grantlee::Template mSelfcontainedTemplate;
};

void GenericGrantleeFormatterPrivate::setContent(const QString &content)
{
    mSelfcontainedTemplate = mEngine->newTemplate(content, QStringLiteral("content"));
    if (mSelfcontainedTemplate->error()) {
        mErrorMessage = mSelfcontainedTemplate->errorString() + QLatin1String("<br>");
    }
}

void GenericGrantleeFormatterPrivate::setDefaultHtmlMainFile(const QString &name)
{
    if (mDefaultMainFile != name) {
        mDefaultMainFile = name;
        refreshTemplate();
    }
}

void GenericGrantleeFormatterPrivate::initializeEngine()
{
    mEngine = new Grantlee::Engine;
    mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader);

    changeGrantleePath(mThemePath);
}

void GenericGrantleeFormatterPrivate::refreshTemplate()
{
    mSelfcontainedTemplate = mEngine->loadByName(mDefaultMainFile);
    if (mSelfcontainedTemplate->error()) {
        mErrorMessage += mSelfcontainedTemplate->errorString() + QLatin1String("<br>");
    }
}

void GenericGrantleeFormatterPrivate::changeGrantleePath(const QString &path)
{
    if (!mTemplateLoader) {
        mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader);
    }
    mTemplateLoader->setTemplateDirs(QStringList() << path);
    mEngine->addTemplateLoader(mTemplateLoader);

    refreshTemplate();
}

QString GenericGrantleeFormatterPrivate::render(const QVariantHash &mapping) const
{
    Grantlee::Context context(mapping);
    const QString contentHtml = mSelfcontainedTemplate->render(&context);
    return contentHtml;
}

GenericGrantleeFormatter::GenericGrantleeFormatter(const QString &defaultHtmlMain, const QString &themePath, QObject *parent)
    : QObject(parent)
    , d(new PimCommon::GenericGrantleeFormatterPrivate(defaultHtmlMain, themePath))
{
}

GenericGrantleeFormatter::GenericGrantleeFormatter(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::GenericGrantleeFormatterPrivate)
{
}

GenericGrantleeFormatter::~GenericGrantleeFormatter()
{
    delete d;
}

void GenericGrantleeFormatter::setDefaultHtmlMainFile(const QString &name)
{
    d->setDefaultHtmlMainFile(name);
}

void GenericGrantleeFormatter::changeGrantleePath(const QString &path)
{
    d->changeGrantleePath(path);
}

QString GenericGrantleeFormatter::errorMessage() const
{
    return d->mErrorMessage;
}

QString GenericGrantleeFormatter::render(const QVariantHash &mapping) const
{
    return d->render(mapping);
}

void GenericGrantleeFormatter::setContent(const QString &content)
{
    d->setContent(content);
}

void GenericGrantleeFormatter::refreshTemplate()
{
    d->refreshTemplate();
}
