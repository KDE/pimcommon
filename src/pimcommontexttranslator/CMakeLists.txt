# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5PimCommonTextTranslator")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5PimCommonTextTranslator_QCH
        FILE KF5PimCommonTextTranslatorQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5PimCommonTextTranslatorQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5PimCommonTextTranslatorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextTranslatorConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommontexttranslator_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextTranslatorConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextTranslatorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextTranslatorConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5PimCommonTextTranslatorTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5PimCommonTextTranslatorTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontexttranslator_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextTranslator/ COMPONENT Devel
    )

add_library(KF5PimCommonTextTranslator )
add_library(KF5::PimCommonTextTranslator ALIAS KF5PimCommonTextTranslator)
ecm_qt_declare_logging_category(KF5PimCommonTextTranslator HEADER pimcommontexttranslator_debug.h
    IDENTIFIER PIMCOMMONTEXTTRANSLATOR_LOG CATEGORY_NAME org.kde.pim.pimcommontexttranslator
        DESCRIPTION "kdepim (pimcommon TextTranslator)"
        EXPORT PIMCOMMON
    )

target_sources(KF5PimCommonTextTranslator PRIVATE
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5PimCommonTextTranslator PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF5PimCommonTextTranslator BASE_NAME pimcommontexttranslator)


target_link_libraries(KF5PimCommonTextTranslator
    PUBLIC
    Qt::Gui
    Qt::Widgets
    PRIVATE
    KF5::I18n
    )

target_include_directories(KF5PimCommonTextTranslator INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextTranslator/>")

target_include_directories(KF5PimCommonTextTranslator PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KF5PimCommonTextTranslator PROPERTIES
    VERSION ${PIMCOMMON_VERSION}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommonTextTranslator
    )

install(TARGETS
    KF5PimCommonTextTranslator
    EXPORT KF5PimCommonTextTranslatorTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
    )

#if (BUILD_TESTING)
#    add_subdirectory(autocorrection/autotests)
#    add_subdirectory(autocorrection/tests)
#endif()


#ecm_generate_headers(PimCommon_Camelcasesettings_HEADERS
#    HEADER_NAMES
#    PimCommonAutoCorrectionSettings
#    REQUIRED_HEADERS PimCommon_settings_HEADERS
#    PREFIX PimCommonAutoCorrection
#    RELATIVE settings
#    )

ecm_generate_pri_file(BASE_NAME PimCommonTextTranslator
    LIB_NAME KF5PimCommonTextTranslator
    DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextTranslator
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonatexttranslator_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextTranslator/ COMPONENT Devel
    )

#install(FILES
#    ${PimCommon_Camelcaseautocorrection_HEADERS}
#    ${PimCommon_Camelcaseautocorrectionwidgets_HEADERS}
#    ${PimCommon_Camelcasesettings_HEADERS}
#    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonAutoCorrection/PimCommonAutoCorrection
#    COMPONENT Devel
#    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontexttranslator_export.h
#    ${PimCommon_HEADERS}
#    ${PimCommon_autocorrection_HEADERS}
#    ${PimCommon_autocorrectionwidgets_HEADERS}
#    ${PimCommon_settings_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextTranslator/pimcommontexttranslator
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF5PimCommonTextTranslator_QCH
        NAME KF5PimCommonTextTranslator
        BASE_NAME KF5PimCommonTextTranslator
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        #${PimCommon_autocorrection_HEADERS}
        #${PimCommon_autocorrectionwidgets_HEADERS}
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMON_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
