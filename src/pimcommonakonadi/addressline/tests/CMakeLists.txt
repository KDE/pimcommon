# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
########### next target ###############
add_executable(testaddresseelineedit testaddresseelineedit.cpp)

target_link_libraries(testaddresseelineedit KF5::PimCommonAkonadi KF5::I18n KF5::Completion)


########### next target ###############
add_executable(completionconfiguredialog_gui completionconfiguredialog_gui.cpp)
target_link_libraries(completionconfiguredialog_gui KF5::PimCommonAkonadi KF5::I18n KF5::Completion)
