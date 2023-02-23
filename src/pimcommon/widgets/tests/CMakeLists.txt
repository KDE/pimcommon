# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
######
add_executable(testspellchecklineedit testspellchecklineedit.cpp)
ecm_mark_as_test(testspellchecklineedit)

target_link_libraries(testspellchecklineedit KF5::PimCommon KPim${KF_MAJOR_VERSION}::PimTextEdit KF${KF_MAJOR_VERSION}::I18n)
######
add_executable(customtoolswidgetng_gui customtoolswidgetng_gui.cpp)
target_link_libraries(customtoolswidgetng_gui
  KF5::PimCommon
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
)

