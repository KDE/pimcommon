# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMONACTIVITIES
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivities_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesConfigVersion.cmake"
    SOVERSION 6
)
add_library(KPim6PimCommonActivities)
add_library(KPim6::PimCommonActivities ALIAS KPim6PimCommonActivities)

# precompiled headers support
if(ENABLE_PCH)
    target_precompile_headers(
        KPim6PimCommonActivities
        PRIVATE
            <QObject>
            <QString>
            <QStringList>
    )
endif()

ecm_qt_declare_logging_category(KPim6PimCommonActivities HEADER pimcommonactivities_debug.h IDENTIFIER PIMCOMMONACTIVITIES_LOG
    CATEGORY_NAME org.kde.pim.pimcommonactivities
    DESCRIPTION "kdepim (pimcommonactivities)"
    EXPORT PIMCOMMON
)

target_sources(
    KPim6PimCommonActivities
    PRIVATE
        activitiesbasemanager.cpp
        activitiesbasemanager.h
        configureactivitieswidget.cpp
        configureactivitieswidget.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KPim6PimCommonActivities
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
ecm_generate_export_header(KPim6PimCommonActivities
    BASE_NAME pimcommonactivities
    VERSION ${PIMCOMMONACTIVITIES_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)

ecm_generate_headers(PimCommonActivities_CamelCasebase_HEADERS
    HEADER_NAMES
    ActivitiesBaseManager
    ConfigureActivitiesWidget
    REQUIRED_HEADERS PimCommonActivities_base_HEADERS
    PREFIX PimCommonActivities
)

target_link_libraries(
    KPim6PimCommonActivities
    PUBLIC
        Qt::Widgets
        Plasma::Activities
    PRIVATE
        KF6::I18n
)

target_include_directories(
    KPim6PimCommonActivities
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/>"
)

target_include_directories(
    KPim6PimCommonActivities
    PUBLIC
        "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>"
)

set_target_properties(
    KPim6PimCommonActivities
    PROPERTIES
        VERSION
            ${PIMCOMMONACTIVITIES_VERSION}
        SOVERSION
            ${PIMCOMMONACTIVITIES_SOVERSION}
        EXPORT_NAME
            PimCommonActivities
)

install(TARGETS KPim6PimCommonActivities EXPORT KPim6PimCommonActivitiesTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
    FILES
        ${PimCommonActivities_CamelCasebase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/PimCommonActivities
    COMPONENT Devel
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivities_export.h
        ${PimCommonActivities_base_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/pimcommonactivities
    COMPONENT Devel
)

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6PimCommonActivities")
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimCommonActivitiesConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KPim6PimCommonActivitiesTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6PimCommonActivitiesTargets.cmake
    NAMESPACE KPim6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivities_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/
    COMPONENT Devel
)
ecm_generate_qdoc(KPim6PimCommonActivities pimcommon-activities.qdocconf)
