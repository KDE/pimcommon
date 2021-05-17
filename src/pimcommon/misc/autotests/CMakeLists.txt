macro(add_pimcommon_misc_unittest _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-misc-"
        LINK_LIBRARIES Qt::Test
        Qt::Widgets
	KF5::PimCommon
    )
endmacro()
add_pimcommon_misc_unittest(emailvalidatortest emailvalidatortest.cpp)
