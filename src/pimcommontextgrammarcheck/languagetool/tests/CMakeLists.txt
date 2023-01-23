# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(languagetool_gui)
target_sources(languagetool_gui PRIVATE main.cpp languagetoolwidget.cpp languagetoolwidget.h)
target_link_libraries(languagetool_gui
    KF${KF_MAJOR_VERSION}::I18n KF5::PimCommonTextGrammarCheck Qt::Network
)

