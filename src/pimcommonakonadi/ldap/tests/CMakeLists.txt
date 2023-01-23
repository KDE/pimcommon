# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
########### next target ###############
add_executable(ldapsearchdialog_gui ldapsearchdialog_gui.cpp)
target_link_libraries(ldapsearchdialog_gui KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::CoreAddons Qt::Widgets KF${KF_MAJOR_VERSION}::Contacts)

