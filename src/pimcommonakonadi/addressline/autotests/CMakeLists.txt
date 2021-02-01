macro(add_pimcommonakonadi_addressline_unittest _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addressline-"
        LINK_LIBRARIES Qt5::Test
        KF5::Contacts
        Qt5::Widgets
        KF5::PimCommonAkonadi
        Qt5::DBus
        KF5::Codecs
        KF5::ConfigCore
        KF5::Completion
        KF5::I18n
        KF5::WidgetsAddons
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
