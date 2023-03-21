# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_libkdepim_blacklistbaloocompletion_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-addessline-blaclistbaloocompletion-"
        LINK_LIBRARIES Qt::Test KPim${KF_MAJOR_VERSION}::PimCommonAkonadi KF${KF_MAJOR_VERSION}::Completion KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::ConfigCore KF${KF_MAJOR_VERSION}::ItemViews KF${KF_MAJOR_VERSION}::Codecs
    )
endmacro()

add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailcompletionwidgettest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemaillisttest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailsearchjobtest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailutiltest.cpp)
add_libkdepim_blacklistbaloocompletion_unittest(blacklistbalooemailwarningtest.cpp)
