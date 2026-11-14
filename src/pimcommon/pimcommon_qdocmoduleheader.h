/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

// Module header for qdoc PCH
#include "configureplugins/configureplugindialog.h"
#include "configureplugins/configurepluginswidget.h"
#include "customtools/customtoolsplugin.h"
#include "customtools/customtoolspluginmanager.h"
#include "customtools/customtoolsviewinterface.h"
#include "customtools/customtoolswidgetng.h"
#include "genericplugins/abstractgenericplugin.h"
#include "genericplugins/abstractgenericplugininterface.h"
#include "genericplugins/genericplugin.h"
#include "genericplugins/genericpluginmanager.h"
#include "genericplugins/pluginutil.h"
#include "network/networkmanager.h"
#include "pimcommon_private_export.h"
#include "shareserviceurl/shareserviceurlmanager.h"
#include "templatewidgets/templateeditdialog.h"
#include "templatewidgets/templatelistwidget.h"
#include "templatewidgets/templatemanager.h"
#include "util/broadcaststatus.h"
#include "util/pimutil.h"
#include "widgets/configureimmutablewidgetutils.h"
#include "widgets/customlogwidget.h"
#include "widgets/customtreeview.h"
#include "widgets/kactionmenuchangecase.h"
#include "widgets/lineeditwithcompleterng.h"
#include "widgets/purposemenumessagewidget.h"
#include "widgets/purposemenuwidget.h"
#include "widgets/renamefiledialog.h"
#include "widgets/simplestringlisteditor.h"
#include "widgets/spellchecklineedit.h"
