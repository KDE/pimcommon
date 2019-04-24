/*
  Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>

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
        : mEngine(new Grantlee::Engine)
    {
    }

    QString mThemePath;
    QString mDefaultMainFile;
    std::unique_ptr<Grantlee::Engine> mEngine;
    QString mErrorMessage;
    QSharedPointer<Grantlee::FileSystemTemplateLoader> mTemplateLoader;
    Grantlee::Template mTemplate;
};


GenericGrantleeFormatter::GenericGrantleeFormatter(const QString &defaultHtmlMain, const QString &themePath, QObject *parent)
    : QObject(parent)
    , d(new PimCommon::GenericGrantleeFormatterPrivate)
{
    d->mThemePath = themePath;
    d->mDefaultMainFile = defaultHtmlMain;
    changeGrantleePath(d->mThemePath);
}

GenericGrantleeFormatter::GenericGrantleeFormatter(QObject *parent)
    : QObject(parent)
    , d(new PimCommon::GenericGrantleeFormatterPrivate)
{
}

GenericGrantleeFormatter::~GenericGrantleeFormatter() = default;

void GenericGrantleeFormatter::setDefaultHtmlMainFile(const QString &name)
{
    if (d->mDefaultMainFile != name) {
        d->mDefaultMainFile = name;
        refreshTemplate();
    }
}

void GenericGrantleeFormatter::changeGrantleePath(const QString &path)
{
    if (!d->mTemplateLoader) {
        d->mTemplateLoader.reset(new Grantlee::FileSystemTemplateLoader);
    }
    d->mTemplateLoader->setTemplateDirs(QStringList() << path);
    d->mEngine->addTemplateLoader(d->mTemplateLoader);

    refreshTemplate();
}

QString GenericGrantleeFormatter::errorMessage() const
{
    return d->mErrorMessage;
}

QString GenericGrantleeFormatter::render(const QVariantHash &mapping) const
{
    Grantlee::Context context(mapping);
    const QString contentHtml = d->mTemplate->render(&context);
    return contentHtml;
}

void GenericGrantleeFormatter::setContent(const QString &content)
{
    d->mTemplate = d->mEngine->newTemplate(content, QStringLiteral("content"));
    if (d->mTemplate->error()) {
        d->mErrorMessage = d->mTemplate->errorString() + QLatin1String("<br>");
    }
}

void GenericGrantleeFormatter::refreshTemplate()
{
    d->mTemplate = d->mEngine->loadByName(d->mDefaultMainFile);
    if (d->mTemplate->error()) {
        d->mErrorMessage += d->mTemplate->errorString() + QLatin1String("<br>");
    }
}
