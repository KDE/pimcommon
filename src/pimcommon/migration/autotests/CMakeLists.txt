# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_definitions(-DMIGRATION_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

macro(add_pimcommon_migration_unittest _source)
    ecm_add_test(${_source}
        NAME_PREFIX "pimcommon-migration-"
        LINK_LIBRARIES Qt::Test KF5::CoreAddons KF5::ConfigCore KF5::PimCommon
    )
endmacro()

add_pimcommon_migration_unittest(migrateapplicationfilestest.cpp)
add_pimcommon_migration_unittest(migratefileinfotest.cpp)
