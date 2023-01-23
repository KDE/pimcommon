# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(grammalecte_gui)
target_sources(grammalecte_gui PRIVATE main.cpp grammalectewidget.cpp)
target_link_libraries(grammalecte_gui
    KF${KF_MAJOR_VERSION}::I18n KF5::PimCommonTextGrammarCheck
)

