# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim${KF_MAJOR_VERSION}PimCommon")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimCommonConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}PimCommonConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommon_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}PimCommonConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}PimCommonConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}PimCommonConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KPim${KF_MAJOR_VERSION}PimCommonTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KPim${KF_MAJOR_VERSION}PimCommonTargets.cmake NAMESPACE KPim${KF_MAJOR_VERSION}::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommon_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/PimCommon/ COMPONENT Devel
    )




macro(add_resource_iface _kcfgFile _ifaceName _className)
    kcfg_generate_dbus_interface(${CMAKE_CURRENT_SOURCE_DIR}/${_kcfgFile} ${_ifaceName})
    qt_add_dbus_interface(libpimcommon_SRCS
        ${CMAKE_CURRENT_BINARY_DIR}/${_ifaceName}.xml ${_fileName} ${_className}
        )
endmacro()

add_resource_iface(util/imapresource.kcfg org.kde.Akonadi.Imap.Settings imapresourcesettings)

add_library(KPim${KF_MAJOR_VERSION}PimCommon )
add_library(KPim${KF_MAJOR_VERSION}::PimCommon ALIAS KPim${KF_MAJOR_VERSION}PimCommon)
ecm_qt_declare_logging_category(KPim${KF_MAJOR_VERSION}PimCommon HEADER pimcommon_debug.h IDENTIFIER PIMCOMMON_LOG CATEGORY_NAME org.kde.pim.pimcommon
        DESCRIPTION "kdepim (pimcommon)"
        OLD_CATEGORY_NAMES log_pimcommon
        EXPORT PIMCOMMON
    )

target_sources(KPim${KF_MAJOR_VERSION}PimCommon PRIVATE
    ${libpimcommon_SRCS}
    genericplugins/pluginutil.cpp
    genericplugins/genericpluginmanager.cpp
    genericplugins/genericplugin.cpp
    genericplugins/abstractgenericplugin.cpp
    genericplugins/abstractgenericplugininterface.cpp
    configureplugins/configurepluginslistwidget.cpp
    configureplugins/configurepluginswidget.cpp
    configureplugins/configureplugindialog.cpp

    templatewidgets/templatelistwidget.cpp
    templatewidgets/templateeditdialog.cpp
    templatewidgets/templatemanager.cpp
    widgets/renamefiledialog.cpp
    widgets/simplestringlisteditor.cpp
    widgets/customtreeview.cpp
    widgets/configureimmutablewidgetutils.cpp
    widgets/kactionmenuchangecase.cpp
    widgets/spellchecklineedit.cpp
    widgets/lineeditwithcompleterng.cpp
    widgets/customlogwidget.cpp
    customtools/customtoolsplugin.cpp
    customtools/customtoolspluginmanager.cpp
    customtools/customtoolswidgetng.cpp
    customtools/customtoolsviewinterface.cpp
    util/pimutil.cpp
    util/broadcaststatus.cpp

    shareserviceurl/shareserviceurlmanager.cpp
    network/networkmanager.cpp
    misc/emailvalidator.cpp
    widgets/icons.qrc
    misc/emailvalidator.h

    customtools/customtoolswidgetng.h
    customtools/customtoolsplugin.h
    customtools/customtoolspluginmanager.h
    customtools/customtoolsviewinterface.h
    configureplugins/configureplugindialog.h
    configureplugins/configurepluginswidget.h
    configureplugins/configurepluginslistwidget.h
    shareserviceurl/shareserviceurlmanager.h
    pimcommon_private_export.h
    network/networkmanager.h
    widgets/renamefiledialog.h
    widgets/spellchecklineedit.h
    widgets/customtreeview.h
    widgets/lineeditwithcompleterng.h
    widgets/simplestringlisteditor.h
    widgets/customlogwidget.h
    widgets/configureimmutablewidgetutils.h
    widgets/kactionmenuchangecase.h
    templatewidgets/templatemanager.h
    templatewidgets/templatelistwidget.h
    templatewidgets/templateeditdialog.h
    util/broadcaststatus.h
    util/pimutil.h
    genericplugins/genericplugin.h
    genericplugins/genericpluginmanager.h
    genericplugins/pluginutil.h
    genericplugins/abstractgenericplugininterface.h
    genericplugins/abstractgenericplugin.h

    autocorrection/widgets/lineeditwithautocorrection.h
    autocorrection/widgets/lineeditwithautocorrection.cpp
    )

if (QT_MAJOR_VERSION STREQUAL "5")
    target_sources(KPim${KF_MAJOR_VERSION}PimCommon PRIVATE
        migration/migrateapplicationfiles.cpp
        migration/migrateapplicationfiles.h

        migration/migratefileinfo.cpp
        migration/migratefileinfo.h
    )
endif()

target_sources(KPim${KF_MAJOR_VERSION}PimCommon PRIVATE
    widgets/purposemenuwidget.h
    widgets/purposemenuwidget.cpp
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim${KF_MAJOR_VERSION}PimCommon PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KPim${KF_MAJOR_VERSION}PimCommon BASE_NAME pimcommon)


target_link_libraries(KPim${KF_MAJOR_VERSION}PimCommon
    PUBLIC
    Qt::Gui
    Qt::Widgets
    Qt::DBus
    KF${KF_MAJOR_VERSION}::KIOCore
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    KPim${KF_MAJOR_VERSION}::PimTextEdit
    KF${KF_MAJOR_VERSION}::TextAutoCorrection
    PRIVATE
    Qt::Network
    KF${KF_MAJOR_VERSION}::I18n
    KPim${KF_MAJOR_VERSION}::Libkdepim
    KF${KF_MAJOR_VERSION}::XmlGui
    KF${KF_MAJOR_VERSION}::KIOWidgets
    KF${KF_MAJOR_VERSION}::ItemViews
    KF${KF_MAJOR_VERSION}::NewStuffCore
    KF${KF_MAJOR_VERSION}::NewStuffWidgets
    KF${KF_MAJOR_VERSION}::Purpose
    KF${KF_MAJOR_VERSION}::PurposeWidgets
    KF${KF_MAJOR_VERSION}::Codecs
)

target_include_directories(KPim${KF_MAJOR_VERSION}PimCommon INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/PimCommon/>")

target_include_directories(KPim${KF_MAJOR_VERSION}PimCommon PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KPim${KF_MAJOR_VERSION}PimCommon PROPERTIES
    VERSION ${PIMCOMMON_VERSION}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommon
    )

install(TARGETS
    KPim${KF_MAJOR_VERSION}PimCommon
    EXPORT KPim${KF_MAJOR_VERSION}PimCommonTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )

if (BUILD_TESTING)
    add_subdirectory(widgets/autotests)
    if (QT_MAJOR_VERSION STREQUAL "5")
        add_subdirectory(migration/autotests)
    endif()
    add_subdirectory(shareserviceurl/autotests)
    add_subdirectory(widgets/tests)
    add_subdirectory(customtools/autotests)
    add_subdirectory(autotests)
    add_subdirectory(configureplugins/autotests)
    add_subdirectory(genericplugins/autotests)
    add_subdirectory(misc/autotests)
    add_subdirectory(autocorrection/autotests)
    add_subdirectory(autocorrection/tests)
endif()

ecm_generate_headers(PimCommon_CamelCasegenericplugins_HEADERS
    HEADER_NAMES
    PluginUtil
    GenericPluginManager
    GenericPlugin
    AbstractGenericPlugin
    AbstractGenericPluginInterface
    REQUIRED_HEADERS PimCommon_genericplugins_HEADERS
    PREFIX PimCommon
    RELATIVE genericplugins
    )

ecm_generate_headers(PimCommon_Camelcaseautocorrectionwidgets_HEADERS
    HEADER_NAMES
    LineEditWithAutoCorrection
    REQUIRED_HEADERS PimCommon_autocorrectionwidgets_HEADERS
    PREFIX PimCommon
    RELATIVE autocorrection/widgets/
    )


ecm_generate_headers(PimCommon_CamelCasenetworkmanager_HEADERS
    HEADER_NAMES
    NetworkManager
    REQUIRED_HEADERS PimCommon_networkmanager_HEADERS
    PREFIX PimCommon
    RELATIVE network
    )

ecm_generate_headers(PimCommon_CamelCasemisc_HEADERS
    HEADER_NAMES
    EmailValidator
    REQUIRED_HEADERS PimCommon_misc_HEADERS
    PREFIX PimCommon
    RELATIVE misc
    )

ecm_generate_headers(PimCommon_CamelCase_HEADERS
    HEADER_NAMES
    PimUtil
    BroadcastStatus
    REQUIRED_HEADERS PimCommon_HEADERS
    PREFIX PimCommon
    RELATIVE util
    )

ecm_generate_headers(PimCommon_Camelcaseshareserviceurl_HEADERS
    HEADER_NAMES
    ShareServiceUrlManager
    REQUIRED_HEADERS PimCommon_shareserviceurl_HEADERS
    PREFIX PimCommon
    RELATIVE shareserviceurl
    )

ecm_generate_headers(PimCommon_Camelcasecustomtools_HEADERS
    HEADER_NAMES
    CustomToolsWidgetng
    CustomToolsPlugin
    CustomToolsViewInterface
    CustomToolsPluginManager
    REQUIRED_HEADERS PimCommon_customtools_HEADERS
    PREFIX PimCommon
    RELATIVE customtools
    )

if (QT_MAJOR_VERSION STREQUAL "5")
    ecm_generate_headers(PimCommon_Camelcasemigrate_HEADERS
        HEADER_NAMES
        MigrateApplicationFiles
        MigrateFileInfo
        REQUIRED_HEADERS PimCommon_migrate_HEADERS
        PREFIX PimCommon
        RELATIVE migration
    )
endif()

ecm_generate_headers(PimCommon_Camelcasetemplatelist_HEADERS
    HEADER_NAMES
    TemplateListWidget
    TemplateManager
    REQUIRED_HEADERS PimCommon_templatelist_HEADERS
    PREFIX PimCommon
    RELATIVE templatewidgets
    )


ecm_generate_headers(PimCommon_Camelcasewidgets_HEADERS
    HEADER_NAMES
    CustomTreeView
    SpellCheckLineEdit
    ConfigureImmutableWidgetUtils
    RenameFileDialog
    SimpleStringListEditor
    KActionMenuChangeCase
    LineEditWithCompleterNg
    CustomLogWidget
    PurposeMenuWidget
    REQUIRED_HEADERS PimCommon_widgets_HEADERS
    PREFIX PimCommon
    RELATIVE widgets
    )

ecm_generate_headers(PimCommon_Camelcaseconfigureplugins_HEADERS
    HEADER_NAMES
    ConfigurePluginsListWidget
    ConfigurePluginsWidget
    ConfigurePluginDialog
    REQUIRED_HEADERS PimCommon_configureplugins_HEADERS
    PREFIX PimCommon
    RELATIVE configureplugins
    )
ecm_generate_pri_file(BASE_NAME PimCommon
    LIB_NAME KF5PimCommon
    DEPS "network KIOCore KConfigWidgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/PimCommon
    )


install(FILES
    ${PimCommon_Camelcaseconfigureplugins_HEADERS}
    ${PimCommon_CamelCasegenericplugins_HEADERS}
    ${PimCommon_Camelcaseautocorrectionwidgets_HEADERS}
    ${PimCommon_CamelCasenetworkmanager_HEADERS}
    ${PimCommon_CamelCase_HEADERS}
    ${PimCommon_CamelCasejob_HEADERS}
    ${PimCommon_Camelcasecustomtools_HEADERS}
    ${PimCommon_Camelcasemanagerserversidesubscription_HEADERS}
    ${PimCommon_Camelcasemigrate_HEADERS}
    ${PimCommon_Camelcaseplaintexteditor_HEADERS}
    ${PimCommon_Camelcaserichtexteditor_HEADERS}
    ${PimCommon_Camelcasescript_HEADERS}
    ${PimCommon_Camelcaseshareserviceurl_HEADERS}
    ${PimCommon_Camelcasetemplatelist_HEADERS}
    ${PimCommon_Camelcasetexteditor_commonwidget_HEADERS}
    ${PimCommon_Camelcasewidgets_HEADERS}
    ${PimCommon_CamelCasemisc_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/PimCommon/PimCommon
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/imapresourcesettings.h
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommon_export.h
    ${PimCommon_HEADERS}
    ${PimCommon_autocorrectionwidgets_HEADERS}
    ${PimCommon_genericplugins_HEADERS}
    ${PimCommon_configureplugins_HEADERS}
    ${PimCommon_networkmanager_HEADERS}
    ${PimCommon_customtools_HEADERS}
    ${PimCommon_job_HEADERS}
    ${PimCommon_managerserversidesubscription_HEADERS}
    ${PimCommon_migrate_HEADERS}
    ${PimCommon_plaintexteditor_HEADERS}
    ${PimCommon_richtexteditor_HEADERS}
    ${PimCommon_shareserviceurl_HEADERS}
    ${PimCommon_templatelist_HEADERS}
    ${PimCommon_texteditor_commonwidget_HEADERS}
    ${PimCommon_widgets_HEADERS}
    ${PimCommon_misc_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/PimCommon/pimcommon
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

if (BUILD_QCH)
    ecm_add_qch(
        KPim${KF_MAJOR_VERSION}PimCommon_QCH
        NAME KPim${KF_MAJOR_VERSION}PimCommon
        BASE_NAME KPim${KF_MAJOR_VERSION}PimCommon
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommon_HEADERS}
        ${PimCommon_genericplugins_HEADERS}
        ${PimCommon_configureplugins_HEADERS}
        ${PimCommon_networkmanager_HEADERS}
        ${PimCommon_customtools_HEADERS}
        ${PimCommon_job_HEADERS}
        ${PimCommon_managerserversidesubscription_HEADERS}
        ${PimCommon_migrate_HEADERS}
        ${PimCommon_plaintexteditor_HEADERS}
        ${PimCommon_richtexteditor_HEADERS}
        ${PimCommon_settings_HEADERS}
        ${PimCommon_shareserviceurl_HEADERS}
        ${PimCommon_storageservice_HEADERS}
        ${PimCommon_storageservicedialog_HEADERS}
        ${PimCommon_storageserviceinterface_HEADERS}
        ${PimCommon_storageservicesettings_HEADERS}
        ${PimCommon_storageservicewidgets_HEADERS}
        ${PimCommon_templatelist_HEADERS}
        ${PimCommon_texteditor_commonwidget_HEADERS}
        ${PimCommon_translator_HEADERS}
        ${PimCommon_widgets_HEADERS}
        ${PimCommon_misc_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMON_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
    ecm_install_qch_export(
        TARGETS KPim${KF_MAJOR_VERSION}PimCommon_QCH
        FILE KPim${KF_MAJOR_VERSION}PimCommonQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim${KF_MAJOR_VERSION}PimCommonQchTargets.cmake\")")
endif()

