/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommon_export.h"
#include "whatsnewinfo.h"
#include <KLazyLocalizedString>
namespace PimCommon
{
class PIMCOMMON_EXPORT WhatsNewTranslationsBase
{
public:
    WhatsNewTranslationsBase();
    virtual ~WhatsNewTranslationsBase();
    [[nodiscard]] virtual QList<WhatsNewInfo> createWhatsNewInfo() const;
    [[nodiscard]] QString newFeaturesMD5() const;

private:
    [[nodiscard]] virtual QList<KLazyLocalizedString> lastNewFeatures() const;
};
}
