# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommonakonadi_addressline_unittest _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addressline-"
        LINK_LIBRARIES Qt::Test
        KF${KF_MAJOR_VERSION}::Contacts
        Qt::Widgets
        KF5::PimCommonAkonadi
        Qt::DBus
        KF${KF_MAJOR_VERSION}::Codecs
        KF${KF_MAJOR_VERSION}::ConfigCore
        KF${KF_MAJOR_VERSION}::Completion
        KF${KF_MAJOR_VERSION}::I18n
    )
endmacro()

add_pimcommonakonadi_addressline_unittest(recentaddresswidgettest
    recentaddresswidgettest.cpp
)
add_pimcommonakonadi_addressline_unittest(addresseelineeditutiltest
    addresseelineeditutiltest.cpp
)

add_pimcommonakonadi_addressline_unittest(baloocompletionemailtest
    baloocompletionemailtest.cpp
)
add_pimcommonakonadi_addressline_unittest(completionconfiguredialogtest
    completionconfiguredialogtest.cpp
)
add_pimcommonakonadi_addressline_unittest(completionorderwidgettest
    completionorderwidgettest.cpp
)
