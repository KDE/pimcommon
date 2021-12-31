# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_libkdepim_blacklistbaloocompletion_unittest _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addessline-blaclistbaloocompletion-"
        LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::PimCommonAkonadi KF5::WidgetsAddons KF5::Completion KF5::I18n KF5::ConfigCore KF5::ItemViews KF5::Codecs
    )
endmacro()

add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailcompletionwidgettest
    blacklistbalooemailcompletionwidgettest.cpp
)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemaillisttest
    blacklistbalooemaillisttest.cpp
)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailsearchjobtest
    blacklistbalooemailsearchjobtest.cpp
)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailutiltest
    blacklistbalooemailutiltest.cpp
)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailwarningtest
    blacklistbalooemailwarningtest.cpp
)
