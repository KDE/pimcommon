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

ecm_qt_declare_logging_category(KPim6PimCommonActivities HEADER pimcommonactivities_debug.h IDENTIFIER PIMCOMMONACTIVITIES_LOG
    CATEGORY_NAME org.kde.pim.pimcommonactivities
    DESCRIPTION "kdepim (pimcommonactivities)"
    EXPORT PIMCOMMON
)

target_sources(KPim6PimCommonActivities PRIVATE
    activitiesbasemanager.cpp
    activitiesbasemanager.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6PimCommonActivities PROPERTIES UNITY_BUILD ON)
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
    REQUIRED_HEADERS PimCommonActivities_base_HEADERS
    PREFIX PimCommonActivities
)

target_link_libraries(KPim6PimCommonActivities
    PUBLIC
    Plasma::Activities
    PRIVATE
    KF6::I18n
)

target_include_directories(KPim6PimCommonActivities INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/>")

target_include_directories(KPim6PimCommonActivities PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KPim6PimCommonActivities PROPERTIES
    VERSION ${PIMCOMMONACTIVITIES_VERSION}
    SOVERSION ${PIMCOMMONACTIVITIES_SOVERSION}
    EXPORT_NAME PimCommonActivities
)

install(TARGETS
    KPim6PimCommonActivities
    EXPORT KPim6PimCommonActivitiesTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(FILES
    ${PimCommonActivities_CamelCasebase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/PimCommonActivities
    COMPONENT Devel
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivities_export.h
    ${PimCommonActivities_base_HEADERS}


    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/pimcommonactivities
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KPim6PimCommonActivities_QCH
        NAME KPim6PimCommonActivities
        BASE_NAME KPim6PimCommonActivities
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommonActivities_base_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMONACTIVITIES_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
)
endif()

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6PimCommonActivities")
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim6PimCommonActivities_QCH
        FILE KPim6PimCommonActivitiesQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6PimCommonActivitiesQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimCommonActivitiesConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KPim6PimCommonActivitiesTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6PimCommonActivitiesTargets.cmake NAMESPACE KPim6::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivities_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivities/ COMPONENT Devel
)

# Widgets

ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMONACTIVITIESWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivitieswidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesWidgetsConfigVersion.cmake"
    SOVERSION 6
)
add_library(KPim6PimCommonActivitiesWidgets)
add_library(KPim6::PimCommonActivitiesWidgets ALIAS KPim6PimCommonActivitiesWidgets)

ecm_qt_declare_logging_category(KPim6PimCommonActivitiesWidgets HEADER pimcommonactivitieswidgets_debug.h IDENTIFIER PIMCOMMONACTIVITIESWIDGETS_LOG
    CATEGORY_NAME org.kde.pim.pimcommonactivitieswidgets
    DESCRIPTION "kdepim (pimcommonactivitieswidgets)"
    EXPORT PIMCOMMON
)

target_sources(KPim6PimCommonActivitiesWidgets PRIVATE
    configureactivitieswidget.cpp
    configureactivitieswidget.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6PimCommonActivitiesWidgets PROPERTIES UNITY_BUILD ON)
endif()
ecm_generate_export_header(KPim6PimCommonActivitiesWidgets
    BASE_NAME pimcommonactivitieswidget
    VERSION ${PIMCOMMONACTIVITIESWIDGETS_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)

ecm_generate_headers(PimCommonActivitiesWidgets_CamelCasebase_HEADERS
    HEADER_NAMES
    ConfigureActivitiesWidget
    REQUIRED_HEADERS PimCommonActivitiesWidgets_base_HEADERS
    PREFIX PimCommonActivitiesWidgets
)

target_link_libraries(KPim6PimCommonActivitiesWidgets
    PUBLIC
    Qt::Widgets
    KPim6::PimCommonActivities
    PRIVATE
    KF6::I18n
)

target_include_directories(KPim6PimCommonActivitiesWidgets INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivitiesWidgets/>")

target_include_directories(KPim6PimCommonActivitiesWidgets PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KPim6PimCommonActivitiesWidgets PROPERTIES
    VERSION ${PIMCOMMONACTIVITIESWIDGETS_VERSION}
    SOVERSION ${PIMCOMMONACTIVITIESWIDGETS_SOVERSION}
    EXPORT_NAME PimCommonActivitiesWidgets
)

install(TARGETS
    KPim6PimCommonActivitiesWidgets
    EXPORT KPim6PimCommonActivitiesWidgetsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(FILES
    ${PimCommonActivitiesWidgets_CamelCasebase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivitiesWidgets/PimCommonActivitiesWidgets
    COMPONENT Devel
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivitieswidget_export.h
    ${PimCommonActivitiesWidgets_base_HEADERS}


    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivitiesWidgets/pimcommonactivitieswidget
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KPim6PimCommonActivitiesWidgets_QCH
        NAME KPim6PimCommonActivitiesWidgets
        BASE_NAME KPim6PimCommonActivitiesWidgets
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommonActivitiesWidgets_base_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMONACTIVITIESWIDGETS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
)
endif()

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6PimCommonActivitiesWidgets")
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim6PimCommonActivitiesWidgets_QCH
        FILE KPim6PimCommonActivitiesWidgetsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6PimCommonActivitiesWidgetsQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimCommonActivitiesWidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesWidgetsConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesWidgetsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonActivitiesWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KPim6PimCommonActivitiesWidgetsTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6PimCommonActivitiesWidgetsTargets.cmake NAMESPACE KPim6::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonactivitieswidgets_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonActivitiesWidgets/ COMPONENT Devel
)
