# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
########### next target ###############
add_executable(ldapsearchdialog_gui ldapsearchdialog_gui.cpp)
target_link_libraries(
    ldapsearchdialog_gui
    KPim6::PimCommonAkonadi
    KF6::I18n
    KF6::CoreAddons
    Qt::Widgets
    KF6::Contacts
)
