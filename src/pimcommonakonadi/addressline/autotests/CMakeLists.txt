# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommonakonadi_addressline_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addressline-"
        LINK_LIBRARIES Qt::Test
        KF6::Contacts
        Qt::Widgets
        KPim6::PimCommonAkonadi
        Qt::DBus
        KF6::Codecs
        KF6::ConfigCore
        KF6::Completion
        KF6::I18n
    )
endmacro()

add_pimcommonakonadi_addressline_unittest(recentaddresswidgettest.cpp)
add_pimcommonakonadi_addressline_unittest(addresseelineeditutiltest.cpp)
add_pimcommonakonadi_addressline_unittest(baloocompletionemailtest.cpp)
add_pimcommonakonadi_addressline_unittest(completionconfiguredialogtest.cpp)
add_pimcommonakonadi_addressline_unittest(completionorderwidgettest.cpp)
add_pimcommonakonadi_addressline_unittest(addresseelineeditbalootest.cpp)
