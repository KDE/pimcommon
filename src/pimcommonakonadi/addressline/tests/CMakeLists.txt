# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
########### next target ###############
add_executable(testaddresseelineedit testaddresseelineedit.cpp)

target_link_libraries(testaddresseelineedit KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Completion)


########### next target ###############
add_executable(completionconfiguredialog_gui completionconfiguredialog_gui.cpp)
target_link_libraries(completionconfiguredialog_gui KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Completion)
