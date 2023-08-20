# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommon_regularexpression_unittest _source)
    get_filename_component( _name ${_source} NAME_WE )
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-regularexpression-"
        LINK_LIBRARIES Qt::Test Qt::Gui KPim${KF_MAJOR_VERSION}::PimCommon
    )
endmacro()

add_pimcommon_regularexpression_unittest(regularexpressiontests.cpp)
add_pimcommon_regularexpression_unittest(pimutilstest.cpp)
