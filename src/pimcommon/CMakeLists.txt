# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommon_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommon/ COMPONENT Devel
)

ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommon_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonConfigVersion.cmake"
    SOVERSION 6
)


macro(add_resource_iface _kcfgFile _ifaceName _className)
    kcfg_generate_dbus_interface(${CMAKE_CURRENT_SOURCE_DIR}/${_kcfgFile} ${_ifaceName})
    qt_add_dbus_interface(libpimcommon_SRCS
        ${CMAKE_CURRENT_BINARY_DIR}/${_ifaceName}.xml ${_fileName} ${_className}
)
endmacro()

add_resource_iface(util/imapresource.kcfg org.kde.Akonadi.Imap.Settings imapresourcesettings)

add_library(KPim6PimCommon)
add_library(KPim6::PimCommon ALIAS KPim6PimCommon)
ecm_qt_declare_logging_category(KPim6PimCommon HEADER pimcommon_debug.h IDENTIFIER PIMCOMMON_LOG CATEGORY_NAME org.kde.pim.pimcommon
        DESCRIPTION "kdepim (pimcommon)"
        OLD_CATEGORY_NAMES log_pimcommon
        EXPORT PIMCOMMON
)

target_sources(KPim6PimCommon PRIVATE
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
    widgets/icons.qrc

    customtools/customtoolswidgetng.h
    customtools/customtoolsplugin.h
    customtools/customtoolspluginmanager.h
    customtools/customtoolsviewinterface.h
    configureplugins/configureplugindialog.h
    configureplugins/configurepluginswidget.h
    configureplugins/configurepluginslistwidget.h

    configureplugins/configurepluginstreewidgetdelegate.h
    configureplugins/configurepluginstreewidgetdelegate.cpp

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

    widgets/purposemenumessagewidget.h
    widgets/purposemenumessagewidget.cpp


    needupdateversion/needupdateversionwidget.h
    needupdateversion/needupdateversionwidget.cpp

    needupdateversion/needupdateversionutils.h
    needupdateversion/needupdateversionutils.cpp

    widgets/purposemenuwidget.h
    widgets/purposemenuwidget.cpp

    whatsnew/whatsnewdialog.h
    whatsnew/whatsnewdialog.cpp
    whatsnew/whatsnewwidget.h
    whatsnew/whatsnewwidget.cpp

    whatsnew/whatsnewmessagewidget.h
    whatsnew/whatsnewmessagewidget.cpp

    whatsnew/whatsnewcomboboxwidget.h
    whatsnew/whatsnewcomboboxwidget.cpp

    whatsnew/whatsnewtranslationsbase.h
    whatsnew/whatsnewtranslationsbase.cpp
    whatsnew/whatsnewinfo.h
    whatsnew/whatsnewinfo.cpp
    
    verifynewversion/verifynewversionutils.cpp
    verifynewversion/verifynewversionutils.h
    verifynewversion/verifynewversionwidget.cpp
    verifynewversion/verifynewversionwidget.h
)

if(ENABLE_WARN_OUTDATED)
    target_compile_definitions(KPim6PimCommon PRIVATE ENABLE_WARN_OUTDATED=1)
else()
    target_compile_definitions(KPim6PimCommon PRIVATE ENABLE_WARN_OUTDATED=0)
endif()

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6PimCommon PROPERTIES UNITY_BUILD ON)
endif()
ecm_generate_export_header(KPim6PimCommon
    BASE_NAME pimcommon
    VERSION ${PIMCOMMON_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)


target_link_libraries(KPim6PimCommon
    PUBLIC
    Qt::Gui
    Qt::Widgets
    Qt::DBus
    KF6::KIOCore
    KF6::WidgetsAddons
    KF6::TextCustomEditor
    PRIVATE
    Qt::Network
    KF6::I18n
    KF6::XmlGui
    KF6::KIOWidgets
    KF6::ItemViews
    KF6::NewStuffCore
    KF6::NewStuffWidgets
    KF6::Purpose
    KF6::PurposeWidgets
    KF6::Codecs
)
if(TARGET KF6::TextAutoCorrectionWidgets)
    target_link_libraries(KPim6PimCommon
        PUBLIC
        KF6::TextAutoCorrectionWidgets
)
else()
    target_link_libraries(KPim6PimCommon
        PUBLIC
        KF6::TextAutoCorrection
)
endif()

target_include_directories(KPim6PimCommon INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommon/>")

target_include_directories(KPim6PimCommon PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KPim6PimCommon PROPERTIES
    VERSION ${PIMCOMMON_VERSION}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommon
)

install(TARGETS
    KPim6PimCommon
    EXPORT KPim6PimCommonTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

if(BUILD_TESTING)
    add_subdirectory(widgets/autotests)
    add_subdirectory(shareserviceurl/autotests)
    add_subdirectory(widgets/tests)
    add_subdirectory(customtools/autotests)
    add_subdirectory(autotests)
    add_subdirectory(configureplugins/autotests)
    add_subdirectory(genericplugins/autotests)
    add_subdirectory(autocorrection/autotests)
    add_subdirectory(autocorrection/tests)
    add_subdirectory(needupdateversion/tests)
    add_subdirectory(needupdateversion/autotests)
    add_subdirectory(whatsnew/autotests)
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

ecm_generate_headers(PimCommon_Camelcaseneedupdateversionwidgets_HEADERS
    HEADER_NAMES
    NeedUpdateVersionUtils
    NeedUpdateVersionWidget
    REQUIRED_HEADERS PimCommon_needupdateversionwidgets_HEADERS
    PREFIX PimCommon
    RELATIVE needupdateversion
)

ecm_generate_headers(PimCommon_Camelverifynewversion_HEADERS
    HEADER_NAMES
    VerifyNewVersionWidget
    REQUIRED_HEADERS PimCommon_verifynewversion_HEADERS
    PREFIX PimCommon
    RELATIVE verifynewversion
)

ecm_generate_headers(PimCommon_CamelCasenetworkmanager_HEADERS
    HEADER_NAMES
    NetworkManager
    REQUIRED_HEADERS PimCommon_networkmanager_HEADERS
    PREFIX PimCommon
    RELATIVE network
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
    PurposeMenuMessageWidget
    REQUIRED_HEADERS PimCommon_widgets_HEADERS
    PREFIX PimCommon
    RELATIVE widgets
)

ecm_generate_headers(PimCommon_Camelcaseconfigureplugins_HEADERS
    HEADER_NAMES
    ConfigurePluginsListWidget
    ConfigurePluginsWidget
    ConfigurePluginDialog
    ConfigurePluginsTreeWidgetDelegate
    REQUIRED_HEADERS PimCommon_configureplugins_HEADERS
    PREFIX PimCommon
    RELATIVE configureplugins
)


ecm_generate_headers(PimCommon_Camelcasewhatsnew_HEADERS
    HEADER_NAMES
    WhatsNewComboBoxWidget
    WhatsNewDialog
    WhatsNewInfo
    WhatsNewTranslationsBase
    WhatsNewMessageWidget
    REQUIRED_HEADERS PimCommon_whatsnew_HEADERS
    PREFIX PimCommon
    RELATIVE whatsnew
)

install(FILES
    ${PimCommon_Camelcaseconfigureplugins_HEADERS}
    ${PimCommon_CamelCasegenericplugins_HEADERS}
    ${PimCommon_Camelcaseautocorrectionwidgets_HEADERS}
    ${PimCommon_CamelCasenetworkmanager_HEADERS}
    ${PimCommon_Camelcaseneedupdateversionwidgets_HEADERS}
    ${PimCommon_Camelverifynewversion_HEADERS}
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
    ${PimCommon_Camelcasewhatsnew_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommon/PimCommon
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
    ${PimCommon_needupdateversionwidgets_HEADERS}
    ${PimCommon_customtools_HEADERS}
    ${PimCommon_job_HEADERS}
    ${PimCommon_managerserversidesubscription_HEADERS}
    ${PimCommon_plaintexteditor_HEADERS}
    ${PimCommon_richtexteditor_HEADERS}
    ${PimCommon_shareserviceurl_HEADERS}
    ${PimCommon_templatelist_HEADERS}
    ${PimCommon_texteditor_commonwidget_HEADERS}
    ${PimCommon_widgets_HEADERS}
    ${PimCommon_whatsnew_HEADERS}
    ${PimCommon_verifynewversion_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommon/pimcommon
    COMPONENT Devel
)

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

if(BUILD_QCH)
    ecm_add_qch(
        KPim6PimCommon_QCH
        NAME KPim6PimCommon
        BASE_NAME KPim6PimCommon
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommon_HEADERS}
        ${PimCommon_genericplugins_HEADERS}
        ${PimCommon_configureplugins_HEADERS}
        ${PimCommon_networkmanager_HEADERS}
        ${PimCommon_needupdateversionwidgets_HEADERS}
        ${PimCommon_customtools_HEADERS}
        ${PimCommon_job_HEADERS}
        ${PimCommon_managerserversidesubscription_HEADERS}
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
        ${PimCommon_whatsnew_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMON_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
)
endif()

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6PimCommon")
if(BUILD_QCH)
ecm_install_qch_export(
    TARGETS KPim6PimCommon_QCH
    FILE KPim6PimCommonQchTargets.cmake
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6PimCommonQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimCommonConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KPim6PimCommonTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KPim6PimCommonTargets.cmake NAMESPACE KPim6::)
