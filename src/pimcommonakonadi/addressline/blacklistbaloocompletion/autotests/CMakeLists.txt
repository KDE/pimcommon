# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_libkdepim_blacklistbaloocompletion_unittest _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addessline-blaclistbaloocompletion-"
        LINK_LIBRARIES Qt::Test KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::Completion KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::ConfigCore KF${KF_MAJOR_VERSION}::ItemViews KF${KF_MAJOR_VERSION}::Codecs
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
