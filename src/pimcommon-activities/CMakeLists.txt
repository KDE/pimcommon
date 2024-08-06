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
    configureactivitieswidget.cpp
    configureactivitieswidget.h
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
    ConfigureActivitiesWidget
    REQUIRED_HEADERS PimCommonActivities_base_HEADERS
    PREFIX PimCommonActivities
)

target_link_libraries(KPim6PimCommonActivities
    PUBLIC
    Qt::Widgets
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

# if(BUILD_QCH)
#     ecm_add_qch(
#         KPim6PimCommonActivities_QCH
#         NAME KPim6PimCommonActivities
#         BASE_NAME KPim6PimCommonActivities
#         VERSION ${PIM_VERSION}
#         ORG_DOMAIN org.kde
#         SOURCES # using only public headers, to cover only public API
#         ${PimCommonActivities_acl_HEADERS}
#         ${PimCommonActivities_ldap_HEADERS}
#         ${PimCommonActivities_collectionpage_HEADERS}
#         ${PimCommonActivities_folderdialog_HEADERS}
#         ${PimCommonActivities_genericplugins_HEADERS}
#         ${PimCommonActivities_casewidgets_HEADERS}
#         ${PimCommonActivities_widgets_HEADERS}
#         ${PimCommonActivities_managerserversidesubscription_HEADERS}
#         ${PimCommonActivities_Util_HEADERS}
#         ${PimCommonActivities_progresswidget_HEADERS}
#         ${PimCommonActivities_completionconfiguredialog_HEADERS}
#         ${PimCommonActivities_completionorder_HEADERS}
#         ${PimCommonActivities_addressline_HEADERS}
#         ${PimCommonActivities_recentaddress_HEADERS}
#         #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
#         #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
#         LINK_QCHS
#             Qt6Core_QCH
#             Qt6Gui_QCH
#             Qt6Widgets_QCH
#         INCLUDE_DIRS
#             ${CMAKE_CURRENT_BINARY_DIR}
#         BLANK_MACROS
#             PIMCOMMONACTIVITIES_EXPORT
#         TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
#         QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
#         COMPONENT Devel
# )

# endif()
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

