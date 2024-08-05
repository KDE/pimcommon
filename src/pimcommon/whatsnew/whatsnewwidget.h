/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommon_private_export.h"
#include "whatsnewcomboboxwidget.h"
#include "whatsnewinfo.h"
#include <QWidget>
class QTextBrowser;
namespace PimCommon
{
class PIMCOMMON_TESTS_EXPORT WhatsNewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WhatsNewWidget(QWidget *parent = nullptr);
    ~WhatsNewWidget() override;

    void updateInformations();

private:
    [[nodiscard]] PIMCOMMON_NO_EXPORT int currentVersion() const;
    [[nodiscard]] PIMCOMMON_NO_EXPORT QString generateStartEndHtml(const QString &str) const;
    [[nodiscard]] PIMCOMMON_NO_EXPORT QString importantChangeStr() const;
    [[nodiscard]] PIMCOMMON_NO_EXPORT QString featuresChangeStr() const;
    [[nodiscard]] PIMCOMMON_NO_EXPORT QString bugFixingChangeStr() const;
    PIMCOMMON_NO_EXPORT void slotVersionChanged(int i);
    [[nodiscard]] PIMCOMMON_NO_EXPORT QString createVersionInformation(const WhatsNewInfo &info);
    PIMCOMMON_NO_EXPORT void fillTranslations();
    [[nodiscard]] PIMCOMMON_NO_EXPORT QString generateVersionHeader(int type) const;
    PIMCOMMON_NO_EXPORT void fillComboBox();

    QList<WhatsNewInfo> mWhatsNewInfo;
    QTextBrowser *const mLabelInfo;
    WhatsNewComboBoxWidget *const mWhatsNewComboBoxWidget;
};
}
