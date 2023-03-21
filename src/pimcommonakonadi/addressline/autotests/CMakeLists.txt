# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommonakonadi_addressline_unittest  _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addressline-"
        LINK_LIBRARIES Qt::Test
        KF${KF_MAJOR_VERSION}::Contacts
        Qt::Widgets
        KPim${KF_MAJOR_VERSION}::PimCommonAkonadi
        Qt::DBus
        KF${KF_MAJOR_VERSION}::Codecs
        KF${KF_MAJOR_VERSION}::ConfigCore
        KF${KF_MAJOR_VERSION}::Completion
        KF${KF_MAJOR_VERSION}::I18n
    )
endmacro()

add_pimcommonakonadi_addressline_unittest(recentaddresswidgettest.cpp)
add_pimcommonakonadi_addressline_unittest(addresseelineeditutiltest.cpp)
add_pimcommonakonadi_addressline_unittest(baloocompletionemailtest.cpp)
add_pimcommonakonadi_addressline_unittest(completionconfiguredialogtest.cpp)
add_pimcommonakonadi_addressline_unittest(completionorderwidgettest.cpp)
add_pimcommonakonadi_addressline_unittest(addresseelineeditbalootest.cpp)
