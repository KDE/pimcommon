# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
######
add_executable(testspellchecklineedit testspellchecklineedit.cpp)
ecm_mark_as_test(testspellchecklineedit)

target_link_libraries(testspellchecklineedit KF5::PimCommon KF5::PimTextEdit KF5::I18n)
######
add_executable(customtoolswidgetng_gui customtoolswidgetng_gui.cpp)
target_link_libraries(customtoolswidgetng_gui
  KF5::PimCommon
  KF5::XmlGui
  KF5::I18n
)

