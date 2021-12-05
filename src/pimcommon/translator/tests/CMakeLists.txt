# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(translator_gui translator_gui.cpp)
target_link_libraries(translator_gui
  KF5::PimCommon KF5::PimTextEdit KF5::I18n
)

