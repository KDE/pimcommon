# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_libkdepim_blacklistbaloocompletion_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addessline-blaclistbaloocompletion-"
        LINK_LIBRARIES Qt::Test KPim6::PimCommonAkonadi KF6::Completion KF6::I18n KF6::ConfigCore KF6::ItemViews KF6::Codecs
)
endmacro()

add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailcompletionwidgettest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemaillisttest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailsearchjobtest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailutiltest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailwarningtest.cpp)
