# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommon_regularexpression_unittest _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-regularexpression-"
        LINK_LIBRARIES Qt::Test Qt::Gui KF5::PimCommon
    )
endmacro()

add_pimcommon_regularexpression_unittest(regularexpressiontests regularexpressiontests.cpp)
