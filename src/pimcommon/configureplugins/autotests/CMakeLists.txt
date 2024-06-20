# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable( configurepluginswidgettest configurepluginswidgettest.cpp configurepluginswidgettest.h)
add_test(NAME configurepluginswidgettest COMMAND configurepluginswidgettest)
ecm_mark_as_test(kmail-configurepluginswidgettest)
target_link_libraries(configurepluginswidgettest Qt::Test KF6::I18n Qt::Widgets
    KF6::ConfigCore KF6::TextWidgets KPim6::PimCommon)


add_executable( configurepluginslistwidgettest configurepluginslistwidgettest.cpp configurepluginslistwidgettest.h)
add_test(NAME configurepluginslistwidgettest COMMAND configurepluginslistwidgettest)
ecm_mark_as_test(kmail-configurepluginslistwidgettest)
target_link_libraries(configurepluginslistwidgettest Qt::Test KF6::I18n Qt::Widgets
    KF6::ConfigCore KF6::TextWidgets KPim6::PimCommon KF6::ItemViews)
