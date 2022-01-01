/*
  SPDX-FileCopyrightText: 2013-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

#include <KCoreConfigSkeleton>

class QWidget;
class QGroupBox;
class QCheckBox;
class QButtonGroup;
class QLineEdit;
class KConfigSkeletonItem;
class KUrlRequester;
class QSpinBox;
class QComboBox;

namespace PimCommon
{
class SimpleStringListEditor;
namespace ConfigureImmutableWidgetUtils
{
void checkLockDown(QWidget *w, const KConfigSkeletonItem *item);
PIMCOMMON_EXPORT void populateButtonGroup(QGroupBox *box, QButtonGroup *group, int orientation, const KCoreConfigSkeleton::ItemEnum *e);
PIMCOMMON_EXPORT void populateCheckBox(QCheckBox *b, const KCoreConfigSkeleton::ItemBool *e);
PIMCOMMON_EXPORT void loadWidget(QCheckBox *b, const KCoreConfigSkeleton::ItemBool *e);
PIMCOMMON_EXPORT void loadWidget(QGroupBox *box, QButtonGroup *group, const KCoreConfigSkeleton::ItemEnum *e);
PIMCOMMON_EXPORT void loadWidget(QLineEdit *b, const KCoreConfigSkeleton::ItemString *e);
PIMCOMMON_EXPORT void loadWidget(KUrlRequester *b, const KCoreConfigSkeleton::ItemString *e);
PIMCOMMON_EXPORT void loadWidget(QSpinBox *b, const KCoreConfigSkeleton::ItemInt *e);
PIMCOMMON_EXPORT void loadWidget(PimCommon::SimpleStringListEditor *b, const KCoreConfigSkeleton::ItemStringList *e);
PIMCOMMON_EXPORT void loadWidget(QSpinBox *b, const KCoreConfigSkeleton::ItemUInt *e);
PIMCOMMON_EXPORT void loadWidget(QComboBox *b, const KCoreConfigSkeleton::ItemEnum *e);
PIMCOMMON_EXPORT void loadWidget(QGroupBox *b, const KCoreConfigSkeleton::ItemBool *e);

PIMCOMMON_EXPORT void saveComboBox(QComboBox *b, KCoreConfigSkeleton::ItemEnum *e);
PIMCOMMON_EXPORT void saveSpinBox(QSpinBox *b, KCoreConfigSkeleton::ItemUInt *e);
PIMCOMMON_EXPORT void saveSpinBox(QSpinBox *b, KCoreConfigSkeleton::ItemInt *e);
PIMCOMMON_EXPORT void saveCheckBox(QCheckBox *b, KCoreConfigSkeleton::ItemBool *e);
PIMCOMMON_EXPORT void saveLineEdit(QLineEdit *b, KCoreConfigSkeleton::ItemString *e);
PIMCOMMON_EXPORT void saveUrlRequester(KUrlRequester *b, KCoreConfigSkeleton::ItemString *e);
PIMCOMMON_EXPORT void saveSimpleStringListEditor(PimCommon::SimpleStringListEditor *b, KCoreConfigSkeleton::ItemStringList *e);
PIMCOMMON_EXPORT void saveGroupBox(QGroupBox *b, KCoreConfigSkeleton::ItemBool *e);

PIMCOMMON_EXPORT void saveButtonGroup(QButtonGroup *group, KCoreConfigSkeleton::ItemEnum *e);
}
}
