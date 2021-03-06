set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5PimCommon")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5PimCommonConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommon_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5PimCommonTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5PimCommonTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommon_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
    )

set(libpimcommon_autocorrection_SRCS
    autocorrection/autocorrection.cpp
    autocorrection/autocorrectionwidget.cpp
    autocorrection/autocorrectionlistwidget.cpp
    autocorrection/autocorrectiontreewidget.cpp
    autocorrection/autocorrectionlanguage.cpp
    autocorrection/import/importlibreofficeautocorrection.cpp
    autocorrection/import/importkmailautocorrection.cpp
    autocorrection/import/importabstractautocorrection.cpp
    autocorrection/widgets/lineeditwithautocorrection.cpp
    autocorrection/widgets/richtexteditwithautocorrection.cpp
    )

set(libpimcommon_generericplugin_SRCS
    genericplugins/pluginutil.cpp
    genericplugins/genericpluginmanager.cpp
    genericplugins/genericplugin.cpp
    genericplugins/abstractgenericplugin.cpp
    genericplugins/abstractgenericplugininterface.cpp
    )


set(libpimcommon_configure_plugins_SRCS
    configureplugins/configurepluginslistwidget.cpp
    configureplugins/configurepluginswidget.cpp
    configureplugins/configureplugindialog.cpp
    )

set(libpimcommon_translator_SRCS
    translator/translatorutil.cpp
    translator/translatorwidget.cpp
    translator/translatordebugdialog.cpp
    translator/googletranslator.cpp
    )

set(libpimcommon_templatewidgets_SRCS
    templatewidgets/templatelistwidget.cpp
    templatewidgets/templateeditdialog.cpp
    templatewidgets/templatemanager.cpp
    )


set(libpimcommon_widgets_SRCS
    widgets/renamefiledialog.cpp
    widgets/simplestringlisteditor.cpp
    widgets/customtreeview.cpp
    widgets/configureimmutablewidgetutils.cpp
    widgets/kactionmenuchangecase.cpp
    widgets/spellchecklineedit.cpp
    widgets/kpimprintpreviewdialog.cpp
    widgets/lineeditwithcompleterng.cpp
    widgets/purposemenuwidget.cpp
    widgets/customlogwidget.cpp
    )

set(libpimcommon_customtools_SRCS
    customtools/customtoolsplugin.cpp
    customtools/customtoolspluginmanager.cpp
    customtools/customtoolswidgetng.cpp
    customtools/customtoolsviewinterface.cpp
    )

set(libpimcommon_util_SRCS
    util/pimutil.cpp
    util/broadcaststatus.cpp
    )

set(libpimcommon_migrate_SRCS
    migration/migrateapplicationfiles.cpp
    migration/migratefileinfo.cpp
    )

set(libpimcommon_shareserviceurl_SRCS
    shareserviceurl/shareserviceurlmanager.cpp
    )

set(libpimcommon_logactivities_SRCS
    logactivities/logactivitiesmanager.cpp
    logactivities/logactivitiesdialog.cpp
    logactivities/logactivitieswidget.cpp
    logactivities/logactivitiespurposemenuwidget.cpp
    )


set(libpimcommon_networkmanager_SRCS
    network/networkmanager.cpp
    )

set(libpimcommon_misc_SRCS
    misc/emailvalidator.cpp
    )


set(libpimcommon_SRCS
    settings/pimcommonsettings.cpp
    ${libpimcommon_misc_SRCS}
    ${libpimcommon_configure_plugins_SRCS}
    ${libpimcommon_networkmanager_SRCS}
    ${libpimcommon_configure_plugins_SRCS}
    ${libpimcommon_shareserviceurl_SRCS}
    ${libpimcommon_migrate_SRCS}
    ${libpimcommon_util_SRCS}
    ${libpimcommon_texteditor_SRCS}
    ${libpimcommon_storageservice_SRCS}
    ${libpimcommon_autocorrection_SRCS}
    ${libpimcommon_translator_SRCS}
    ${libpimcommon_templatewidgets_SRCS}
    ${libpimcommon_widgets_SRCS}
    ${libpimcommon_customtools_SRCS}
    ${libpimcommon_logactivities_SRCS}
    ${libpimcommon_generericplugin_SRCS}
    widgets/icons.qrc
    )
ecm_qt_declare_logging_category(libpimcommon_SRCS HEADER pimcommon_debug.h IDENTIFIER PIMCOMMON_LOG CATEGORY_NAME org.kde.pim.pimcommon
        DESCRIPTION "kdepim (pimcommon)"
        OLD_CATEGORY_NAMES log_pimcommon
        EXPORT PIMCOMMON
    )


ki18n_wrap_ui(libpimcommon_SRCS
    autocorrection/ui/autocorrectionwidget.ui
    )

macro(add_resource_iface _kcfgFile _ifaceName _className _fileName)
    kcfg_generate_dbus_interface(${CMAKE_CURRENT_SOURCE_DIR}/${_kcfgFile} ${_ifaceName})
    qt_add_dbus_interface(libpimcommon_SRCS
        ${CMAKE_CURRENT_BINARY_DIR}/${_ifaceName}.xml ${_fileName} ${_className}
        )
endmacro()

add_resource_iface(util/imapresource.kcfg org.kde.Akonadi.Imap.Settings ImapSettings imapresourcesettings)

kconfig_add_kcfg_files(libpimcommon_SRCS
    settings/pimcommonsetting_base.kcfgc
    )

add_library(KF5PimCommon ${libpimcommon_SRCS})
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5PimCommon PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF5PimCommon BASE_NAME pimcommon)
add_library(KF5::PimCommon ALIAS KF5PimCommon)


target_link_libraries(KF5PimCommon
    PUBLIC
    Qt::Network
    KF5::KIOCore
    KF5::ConfigWidgets
    PRIVATE
    KF5::I18n
    KF5::Libkdepim
    KF5::Archive
    KF5::NewStuff
    KF5::PimTextEdit
    KF5::XmlGui
    KF5::PimTextEdit
    KF5::KIOWidgets
    Qt::PrintSupport
    KF5::Purpose
    KF5::PurposeWidgets
    )


target_include_directories(KF5PimCommon INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommon/;${KDE_INSTALL_INCLUDEDIR_KF5}/pimcommon>")

target_include_directories(KF5PimCommon PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KF5PimCommon PROPERTIES
    VERSION ${PIMCOMMON_VERSION}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommon
    )

install(TARGETS
    KF5PimCommon
    EXPORT KF5PimCommonTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS} 
    )

if (BUILD_TESTING)
    add_subdirectory(translator/autotests)
    add_subdirectory(autocorrection/autotests)
    add_subdirectory(widgets/autotests)
    add_subdirectory(migration/autotests)
    add_subdirectory(shareserviceurl/autotests)
    add_subdirectory(translator/tests)
    add_subdirectory(widgets/tests)
    add_subdirectory(autocorrection/tests)
    add_subdirectory(customtools/autotests)
    add_subdirectory(autotests)
    add_subdirectory(logactivities/autotests)
    add_subdirectory(logactivities/tests)
    add_subdirectory(configureplugins/autotests)
    add_subdirectory(genericplugins/autotests)
    add_subdirectory(misc/autotests)
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

ecm_generate_headers(PimCommon_Camelcasesettings_HEADERS
    HEADER_NAMES
    PimCommonSettings
    REQUIRED_HEADERS PimCommon_settings_HEADERS
    PREFIX PimCommon
    RELATIVE settings
    )

ecm_generate_headers(PimCommon_Camelcaselogactivities_HEADERS
    HEADER_NAMES
    LogActivitiesManager
    REQUIRED_HEADERS PimCommon_logactivities_HEADERS
    PREFIX PimCommon
    RELATIVE logactivities
    )

ecm_generate_headers(PimCommon_Camelcaseshareserviceurl_HEADERS
    HEADER_NAMES
    ShareServiceUrlManager
    REQUIRED_HEADERS PimCommon_shareserviceurl_HEADERS
    PREFIX PimCommon
    RELATIVE shareserviceurl
    )

ecm_generate_headers(PimCommon_Camelcasetranslator_HEADERS
    HEADER_NAMES
    TranslatorWidget
    REQUIRED_HEADERS PimCommon_translator_HEADERS
    PREFIX PimCommon
    RELATIVE translator
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

ecm_generate_headers(PimCommon_Camelcasemigrate_HEADERS
    HEADER_NAMES
    MigrateApplicationFiles
    MigrateFileInfo
    REQUIRED_HEADERS PimCommon_migrate_HEADERS
    PREFIX PimCommon
    RELATIVE migration
    )

ecm_generate_headers(PimCommon_Camelcaseautocorrectionwidgets_HEADERS
    HEADER_NAMES
    RichTexteditWithAutoCorrection
    LineEditWithAutoCorrection
    REQUIRED_HEADERS PimCommon_autocorrectionwidgets_HEADERS
    PREFIX PimCommon
    RELATIVE autocorrection/widgets/
    )

ecm_generate_headers(PimCommon_Camelcaseautocorrection_HEADERS
    HEADER_NAMES
    AutoCorrectionWidget
    AutoCorrectionLanguage
    AutoCorrection
    REQUIRED_HEADERS PimCommon_autocorrection_HEADERS
    PREFIX PimCommon
    RELATIVE autocorrection/
    )

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
    KPimPrintPreviewDialog
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
    DEPS "network KIOCore KConfigWidgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommon
    )


install(FILES
    ${PimCommon_Camelcaseconfigureplugins_HEADERS}
    ${PimCommon_CamelCasegenericplugins_HEADERS}
    ${PimCommon_Camelcaselogactivities_HEADERS}
    ${PimCommon_CamelCasenetworkmanager_HEADERS}
    ${PimCommon_CamelCase_HEADERS}
    ${PimCommon_CamelCasejob_HEADERS}
    ${PimCommon_Camelcaseautocorrection_HEADERS}
    ${PimCommon_Camelcaseautocorrectionwidgets_HEADERS}
    ${PimCommon_Camelcasecustomtools_HEADERS}
    ${PimCommon_Camelcasemanagerserversidesubscription_HEADERS}
    ${PimCommon_Camelcasemigrate_HEADERS}
    ${PimCommon_Camelcaseplaintexteditor_HEADERS}
    ${PimCommon_Camelcaserichtexteditor_HEADERS}
    ${PimCommon_Camelcasescript_HEADERS}
    ${PimCommon_Camelcasesettings_HEADERS}
    ${PimCommon_Camelcaseshareserviceurl_HEADERS}
    ${PimCommon_Camelcasestorageservice_HEADERS}
    ${PimCommon_Camelcasestorageservicedialog_HEADERS}
    ${PimCommon_Camelcasestorageserviceinterface_HEADERS}
    ${PimCommon_Camelcasestorageservicesettings_HEADERS}
    ${PimCommon_Camelcasestorageservicewidgets_HEADERS}
    ${PimCommon_Camelcasetemplatelist_HEADERS}
    ${PimCommon_Camelcasetexteditor_commonwidget_HEADERS}
    ${PimCommon_Camelcasetranslator_HEADERS}
    ${PimCommon_Camelcasewidgets_HEADERS}
    ${PimCommon_CamelCasemisc_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommon
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/imapresourcesettings.h
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommon_export.h
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonsetting_base.h
    ${PimCommon_HEADERS}
    ${PimCommon_genericplugins_HEADERS}
    ${PimCommon_configureplugins_HEADERS}
    ${PimCommon_networkmanager_HEADERS}
    ${PimCommon_autocorrection_HEADERS}
    ${PimCommon_autocorrectionwidgets_HEADERS}
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
    ${PimCommon_logactivities_HEADERS}
    ${PimCommon_misc_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/pimcommon
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

