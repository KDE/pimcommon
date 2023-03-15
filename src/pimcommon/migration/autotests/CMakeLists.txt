# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
if (QT_MAJOR_VERSION STREQUAL "5")
    add_definitions(-DMIGRATION_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

    macro(add_pimcommon_migration_unittest _source)
        get_filename_component(_name ${_source} NAME_WE)
        ecm_add_test(${_source} ${_name}.h
            TEST_NAME ${_name}
            NAME_PREFIX "pimcommon-migration-"
            LINK_LIBRARIES Qt::Test KF${KF_MAJOR_VERSION}::CoreAddons KF${KF_MAJOR_VERSION}::ConfigCore KPim${KF_MAJOR_VERSION}::PimCommon
        )
endmacro()

add_pimcommon_migration_unittest(migrateapplicationfilestest.cpp)
add_pimcommon_migration_unittest(migratefileinfotest.cpp)
else()
    MESSAGE(STATUS "Need to remove migrate tests in qt6")
endif()
