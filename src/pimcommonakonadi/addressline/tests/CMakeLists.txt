# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
########### next target ###############
add_executable(testaddresseelineedit testaddresseelineedit.cpp)

target_link_libraries(testaddresseelineedit KPim6::PimCommonAkonadi KF6::I18n KF6::Completion)


########### next target ###############
add_executable(completionconfiguredialog_gui completionconfiguredialog_gui.cpp)
target_link_libraries(completionconfiguredialog_gui KPim6::PimCommonAkonadi KF6::I18n KF6::Completion)
