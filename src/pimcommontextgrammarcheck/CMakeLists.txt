# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5PimCommonTextGrammar")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5PimCommonTextGrammar_QCH
        FILE KF5PimCommonTextGrammarQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5PimCommonTextGrammarQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5PimCommonTextGrammarConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammar_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5PimCommonTextGrammarTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5PimCommonTextGrammarTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammar_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammar/ COMPONENT Devel
    )

add_library(KF5PimCommonTextGrammar )
add_library(KF5::PimCommonTextGrammar ALIAS KF5PimCommonTextGrammar)
ecm_qt_declare_logging_category(KF5PimCommonTextGrammar HEADER pimcommontextgrammar_debug.h
    IDENTIFIER PIMCOMMONTEXTGRAMMAR_LOG CATEGORY_NAME org.kde.pim.pimcommontextgrammar
        DESCRIPTION "kdepim (pimcommon Grammar)"
        EXPORT PIMCOMMON
    )

target_sources(KF5PimCommonTextGrammar PRIVATE
    common/grammarerror.cpp
    common/grammarerror.h
    common/grammaraction.h
    common/grammaraction.cpp
    common/grammarresultwidget.cpp
    common/grammarresultwidget.h
    common/grammarresulttextedit.cpp
    common/grammarresulttextedit.h
    common/grammarresultutil.h
    common/grammarresultutil.cpp
    )
#if (BUILD_TESTING)
#endif()

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5PimCommonTextGrammar PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF5PimCommonTextGrammar BASE_NAME pimcommontextgrammar)


target_link_libraries(KF5PimCommonTextGrammar
    PUBLIC
    Qt::Gui
    Qt::Widgets
    PRIVATE
    KF5::I18n
    KF5::WidgetsAddons
    KF5::ConfigWidgets
    )

target_include_directories(KF5PimCommonTextGrammar INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammar/>")

target_include_directories(KF5PimCommonTextGrammar PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KF5PimCommonTextGrammar PROPERTIES
    VERSION ${PIMCOMMON_VERSION}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommonTextGrammar
    )

install(TARGETS
    KF5PimCommonTextGrammar
    EXPORT KF5PimCommonTextGrammarTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_headers(PimCommonTextGrammar_Camelcasetranslator_HEADERS
    HEADER_NAMES
    GrammarAction
    GrammarError
    GrammarResultTextEdit
    GrammarResultWidget
    REQUIRED_HEADERS PimCommonTextGrammar_translator_HEADERS
    PREFIX PimCommonTextGrammar
    RELATIVE common/
    )

ecm_generate_pri_file(BASE_NAME PimCommonTextGrammar
    LIB_NAME KF5PimCommonTextGrammar
    DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammar
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammar_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammar/ COMPONENT Devel
    )

install(FILES
    ${PimCommonTextGrammar_translator_HEADERS}
    ${PimCommonTextGrammar_Camelcasetranslator_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammar/PimCommonTextGrammar
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammar_export.h
    ${PimCommonTextGrammar_translator_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammar/pimcommontextgrammar
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF5PimCommonTextGrammar_QCH
        NAME KF5PimCommonTextGrammar
        BASE_NAME KF5PimCommonTextGrammar
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommonTextGrammar_translator_HEADERS}
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
