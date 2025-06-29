# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(selectmultiselectiondialog_gui selectmultiselectiondialog_gui.cpp)
target_link_libraries(
    selectmultiselectiondialog_gui
    KPim6::PimCommonAkonadi
    KF6::I18n
)
