# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5PimCommonTextGrammarCheck")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5PimCommonTextGrammarCheckConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarCheckConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammarcheck_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarCheckConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarCheckConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonTextGrammarCheckConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5PimCommonTextGrammarCheckTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5PimCommonTextGrammarCheckTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammarcheck_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammarCheck/ COMPONENT Devel
    )

add_library(KF5PimCommonTextGrammarCheck )
add_library(KF5::PimCommonTextGrammarCheck ALIAS KF5PimCommonTextGrammarCheck)
ecm_qt_declare_logging_category(KF5PimCommonTextGrammarCheck HEADER pimcommontextgrammarcheck_debug.h
    IDENTIFIER PIMCOMMONTEXTGRAMMAR_LOG CATEGORY_NAME org.kde.pim.pimcommontextgrammarcheck
        DESCRIPTION "kdepim (pimcommon Text Grammar Check)"
        EXPORT PIMCOMMON
    )

target_sources(KF5PimCommonTextGrammarCheck PRIVATE
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

    languagetool/languageinfo.cpp
    languagetool/languageinfo.h
    languagetool/languagetoolcombobox.cpp
    languagetool/languagetoolcombobox.h
    languagetool/languagetoolconfigdialog.cpp
    languagetool/languagetoolconfigdialog.h
    languagetool/languagetoolconfigwidget.cpp
    languagetool/languagetoolconfigwidget.h
    languagetool/languagetoolgetlistoflanguagejob.cpp
    languagetool/languagetoolgetlistoflanguagejob.h
    languagetool/languagetoolgrammarerror.cpp
    languagetool/languagetoolgrammarerror.h
    languagetool/languagetoollistoflanguagesparser.cpp
    languagetool/languagetoollistoflanguagesparser.h
    languagetool/languagetoolmanager.cpp
    languagetool/languagetoolmanager.h
    languagetool/languagetoolparser.cpp
    languagetool/languagetoolparser.h
    languagetool/languagetoolresultjob.cpp
    languagetool/languagetoolresultjob.h
    languagetool/languagetoolresultwidget.cpp
    languagetool/languagetoolresultwidget.h
    languagetool/languagetoolupdatecombobox.cpp
    languagetool/languagetoolupdatecombobox.h

    grammalecte/grammalecteconfigdialog.cpp
    grammalecte/grammalecteconfigdialog.h
    grammalecte/grammalecteconfigwidget.cpp
    grammalecte/grammalecteconfigwidget.h
    grammalecte/grammalectegenerateconfigoptionjob.cpp
    grammalecte/grammalectegenerateconfigoptionjob.h
    grammalecte/grammalectegrammarerror.cpp
    grammalecte/grammalectegrammarerror.h
    grammalecte/grammalectemanager.cpp
    grammalecte/grammalectemanager.h
    grammalecte/grammalecteparser.cpp
    grammalecte/grammalecteparser.h
    grammalecte/grammalecteresultjob.cpp
    grammalecte/grammalecteresultjob.h
    grammalecte/grammalecteresultwidget.cpp
    grammalecte/grammalecteresultwidget.h
    grammalecte/grammalecteurlrequesterwidget.h
    grammalecte/grammalecteurlrequesterwidget.cpp
    )
if (BUILD_TESTING)
    add_subdirectory(grammalecte/autotests)
    add_subdirectory(grammalecte/tests)
    add_subdirectory(languagetool/autotests)
    add_subdirectory(languagetool/tests)
endif()

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5PimCommonTextGrammarCheck PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF5PimCommonTextGrammarCheck BASE_NAME pimcommontextgrammarcheck)


target_link_libraries(KF5PimCommonTextGrammarCheck
    PUBLIC
    Qt::Gui
    Qt::Widgets
    PRIVATE
    Qt::Network
    KF5::I18n
    KF5::ConfigWidgets
    )

target_include_directories(KF5PimCommonTextGrammarCheck INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammarCheck/>")

target_include_directories(KF5PimCommonTextGrammarCheck PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KF5PimCommonTextGrammarCheck PROPERTIES
    VERSION ${PIMCOMMON_VERSION}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommonTextGrammarCheck
    )

install(TARGETS
    KF5PimCommonTextGrammarCheck
    EXPORT KF5PimCommonTextGrammarCheckTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_headers(PimCommonTextGrammar_Camelcasecommon_HEADERS
    HEADER_NAMES
    GrammarAction
    GrammarError
    GrammarResultTextEdit
    GrammarResultWidget
    REQUIRED_HEADERS PimCommonTextGrammar_common_HEADERS
    PREFIX PimCommonTextGrammarCheck
    RELATIVE common/
    )

ecm_generate_headers(PimCommonTextGrammar_Camelcasegrammalecte_HEADERS
    HEADER_NAMES
    GrammalecteConfigDialog
    GrammalecteConfigWidget
    GrammalecteManager
    GrammalecteResultWidget
    GrammalecteGenerateConfigOptionJob
    GrammalecteResultJob
    REQUIRED_HEADERS PimCommonTextGrammar_grammalecte_HEADERS
    PREFIX PimCommonTextGrammarCheck
    RELATIVE grammalecte/
    )

ecm_generate_headers(PimCommonTextGrammar_Camelcaselanguagetool_HEADERS
    HEADER_NAMES
    LanguageToolComboBox
    LanguageToolConfigDialog
    LanguageToolConfigWidget
    LanguageToolGetListOfLanguageJob
    LanguageToolManager
    LanguageToolResultWidget
    REQUIRED_HEADERS PimCommonTextGrammar_languagetool_HEADERS
    PREFIX PimCommonTextGrammarCheck
    RELATIVE languagetool/
    )


ecm_generate_pri_file(BASE_NAME PimCommonTextGrammarCheck
    LIB_NAME KF5PimCommonTextGrammarCheck
    DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammarCheck
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammarcheck_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammarCheck/ COMPONENT Devel
    )

install(FILES
    ${PimCommonTextGrammar_common_HEADERS}
    ${PimCommonTextGrammar_Camelcasecommon_HEADERS}

    ${PimCommonTextGrammar_grammalecte_HEADERS}
    ${PimCommonTextGrammar_Camelcasegrammalecte_HEADERS}

    ${PimCommonTextGrammar_languagetool_HEADERS}
    ${PimCommonTextGrammar_Camelcaselanguagetool_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammarCheck/PimCommonTextGrammarCheck
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommontextgrammarcheck_export.h
    ${PimCommonTextGrammar_common_HEADERS}
    ${PimCommonTextGrammar_grammalecte_HEADERS}
    ${PimCommonTextGrammar_languagetool_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonTextGrammarCheck/pimcommontextgrammarcheck
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF5PimCommonTextGrammarCheck_QCH
        NAME KF5PimCommonTextGrammarCheck
        BASE_NAME KF5PimCommonTextGrammarCheck
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommonTextGrammar_common_HEADERS}
        ${PimCommonTextGrammar_grammalecte_HEADERS}
        ${PimCommonTextGrammar_languagetool_HEADERS}
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMONTEXTGRAMMARCHECK_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
    ecm_install_qch_export(
        TARGETS KF5PimCommonTextGrammarCheck_QCH
        FILE KF5PimCommonTextGrammarCheckQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5PimCommonTextGrammarCheckQchTargets.cmake\")")
endif()
