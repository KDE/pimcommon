# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(selectmultiselectiondialog_gui selectmultiselectiondialog_gui.cpp)
target_link_libraries(selectmultiselectiondialog_gui
  KF5::PimCommonAkonadi
  KF${KF_MAJOR_VERSION}::I18n
)
