# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommon_widget_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-widget-"
        LINK_LIBRARIES Qt::Test
        Qt::Widgets
        KPim6::PimCommon
)
endmacro()
add_pimcommon_widget_unittest(kactionmenuchangecasetest.cpp)
add_pimcommon_widget_unittest(lineeditwithcompleterngtest.cpp)
add_pimcommon_widget_unittest(purposemenuwidgettest.cpp)
