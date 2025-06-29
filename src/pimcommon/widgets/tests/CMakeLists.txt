# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
######
add_executable(testspellchecklineedit testspellchecklineedit.cpp)
ecm_mark_as_test(testspellchecklineedit)

target_link_libraries(
    testspellchecklineedit
    KPim6::PimCommon
    KF6::I18n
)
######
add_executable(
    customtoolswidgetng_gui
    customtoolswidgetng_gui.cpp
    customtoolswidgetng_gui.h
)
target_link_libraries(
    customtoolswidgetng_gui
    KPim6::PimCommon
    KF6::XmlGui
    KF6::I18n
)
