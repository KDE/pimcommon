# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommonakonadi_addressline_unittest _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addressline-"
        LINK_LIBRARIES Qt::Test
        KF5::Contacts
        Qt::Widgets
        KF5::PimCommonAkonadi
        Qt::DBus
        KF5::Codecs
        KF5::ConfigCore
        KF5::Completion
        KF5::I18n
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
