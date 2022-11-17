/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammaraction.h"

using namespace PimCommonTextGrammarCheck;

GrammarAction::GrammarAction() = default;

QString GrammarAction::replacement() const
{
    return mReplacement;
}

void GrammarAction::setReplacement(const QString &replacement)
{
    mReplacement = replacement;
}

int GrammarAction::start() const
{
    return mStart;
}

void GrammarAction::setStart(int start)
{
    mStart = start;
}

int GrammarAction::length() const
{
    return mLength;
}

void GrammarAction::setLength(int end)
{
    mLength = end;
}

QStringList GrammarAction::suggestions() const
{
    return mSuggestions;
}

void GrammarAction::setSuggestions(const QStringList &suggestions)
{
    mSuggestions = suggestions;
}

int GrammarAction::blockId() const
{
    return mBlockId;
}

void GrammarAction::setBlockId(int blockId)
{
    mBlockId = blockId;
}

QStringList GrammarAction::infoUrls() const
{
    return mInfoUrls;
}

void GrammarAction::setInfoUrls(const QStringList &urls)
{
    mInfoUrls = urls;
}

QDebug operator<<(QDebug d, const GrammarAction &t)
{
    d << "start " << t.start();
    d << "length " << t.length();
    d << "blockId " << t.blockId();
    d << "suggestion " << t.suggestions();
    d << "replacement " << t.replacement();
    d << "urls " << t.infoUrls();
    return d;
}
