# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMONAKONADI
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonAkonadiConfigVersion.cmake"
    SOVERSION 6
)
add_library(KPim6PimCommonAkonadi)
add_library(KPim6::PimCommonAkonadi ALIAS KPim6PimCommonAkonadi)
ecm_qt_declare_logging_category(KPim6PimCommonAkonadi HEADER pimcommonakonadi_debug.h IDENTIFIER PIMCOMMONAKONADI_LOG CATEGORY_NAME org.kde.pim.pimcommonakonadi
        DESCRIPTION "kdepim (pimcommonakonadi)"
        EXPORT PIMCOMMON
)

target_sources(KPim6PimCommonAkonadi PRIVATE
    folderdialog/selectmulticollectionwidget.cpp
    folderdialog/selectmulticollectiondialog.cpp
    folderdialog/checkedcollectionwidget.cpp
    genericplugins/genericplugininterface.cpp
    genericplugins/plugininterface.cpp
    acl/aclentrydialog.cpp
    acl/aclmanager.cpp
    acl/aclutils.cpp
    acl/collectionaclpage.cpp
    acl/imapaclattribute.cpp
    acl/collectionaclwidget.cpp
    acl/acllistview.cpp
    acl/aclmodifyjob.cpp
    manageserversidesubscription/manageserversidesubscriptionjob.cpp
    ldap/ldapsearchdialog.cpp
    util/createresource.cpp
    util/imapresourcecapabilitiesmanager.cpp
    util/mailutil.cpp
   progresswidget/agentprogressmonitor.cpp
   progresswidget/progressmanagerakonadi.cpp
  collectionpage/collectiontypeutil.cpp
  collectionpage/incidencesforwidget.cpp
  collectionpage/contenttypewidget.cpp
    addressline/completionorder/completionorderwidget.cpp
    addressline/addresslineedit/addresseelineedit.cpp
    addressline/addresslineedit/addresseelineedit_p.cpp
    addressline/addresslineedit/addresseelineeditmanager.cpp
    addressline/addresslineedit/addresseelineeditldap.cpp
    addressline/addresslineedit/addresseelineeditakonadi.cpp
    addressline/addresslineedit/addresseelineeditbaloo.cpp
    addressline/addresslineedit/kmailcompletion.cpp
    addressline/addresslineedit/baloocompletionemail.cpp
    addressline/completionconfiguredialog/completionconfiguredialog.cpp
    addressline/addresslineedit/addresseelineeditutil.cpp
    addressline/recentaddress/recentaddresswidget.cpp
    addressline/recentaddress/recentaddresses.cpp
    addressline/plugins/addressesslineeditabstractplugin.cpp
    addressline/plugins/addressesslineeditpluginmanager.cpp
    progresswidget/agentprogressmonitor.h
    progresswidget/progressmanagerakonadi.h
    acl/collectionaclpage.h
    acl/aclutils_p.h
    acl/acllistview.h
    acl/aclentrydialog_p.h
    acl/imapaclattribute.h
    acl/aclmodifyjob.h
    acl/aclmanager.h
    acl/collectionaclwidget.h
    manageserversidesubscription/manageserversidesubscriptionjob.h
    ldap/ldapsearchdialog.h
    addressline/completionorder/completionorderwidget.h
    addressline/recentaddress/recentaddresses.h
    addressline/recentaddress/recentaddresswidget.h
    addressline/completionconfiguredialog/completionconfiguredialog.h
    addressline/plugins/addressesslineeditabstractplugin.h
    addressline/plugins/addressesslineeditpluginmanager.h
    addressline/addresslineedit/addresseelineedit_p.h
    addressline/addresslineedit/addresseelineeditldap.h
    addressline/addresslineedit/addresseelineeditbaloo.h
    addressline/addresslineedit/addresseelineedit.h
    addressline/addresslineedit/addresseelineeditutil.h
    addressline/addresslineedit/baloocompletionemail.h
    addressline/addresslineedit/addresseelineeditakonadi.h
    addressline/addresslineedit/addresseelineeditmanager.h
    addressline/addresslineedit/kmailcompletion.h
    collectionpage/contenttypewidget.h
    collectionpage/collectiontypeutil.h
    collectionpage/incidencesforwidget.h
    folderdialog/checkedcollectionwidget.h
    folderdialog/selectmulticollectiondialog.h
    folderdialog/selectmulticollectionwidget.h
    pimcommonakonadi_private_export.h
    util/mailutil.h
    util/imapresourcecapabilitiesmanager.h
    util/createresource.h
    genericplugins/genericplugininterface.h
    genericplugins/plugininterface.h
)

if(NOT FORCE_DISABLE_AKONADI_SEARCH)
target_sources(KPim6PimCommonAkonadi PRIVATE
    addressline/blacklistbaloocompletion/blacklistbalooemaillist.cpp
    addressline/blacklistbaloocompletion/blacklistbalooemailutil.cpp
    addressline/blacklistbaloocompletion/blacklistbalooemailcompletionwidget.cpp
    addressline/blacklistbaloocompletion/blacklistbalooemailwarning.cpp
    addressline/blacklistbaloocompletion/blacklistbalooemailsearchjob.cpp
    addressline/blacklistbaloocompletion/blacklistbalooemailcompletionwidget.h
    addressline/blacklistbaloocompletion/blacklistbalooemailwarning.h
    addressline/blacklistbaloocompletion/blacklistbalooemailutil.h
    addressline/blacklistbaloocompletion/blacklistbalooemailsearchjob.h
    addressline/blacklistbaloocompletion/blacklistbalooemaillist.h
)
endif()


if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6PimCommonAkonadi PROPERTIES UNITY_BUILD ON)
endif()
ecm_generate_export_header(KPim6PimCommonAkonadi
    BASE_NAME pimcommonakonadi
    VERSION ${PIMCOMMONAKONADI_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)


target_link_libraries(KPim6PimCommonAkonadi
    PUBLIC
    KPim6::PimCommon
    KPim6::AkonadiCore
    KPim6::AkonadiWidgets
    KF6::Contacts
    KPim6::AkonadiContactWidgets
    KF6::KIOCore
    KPim6::IMAP
    KPim6::Libkdepim
    PRIVATE
    KPim6::AkonadiContactCore
    KF6::I18n
    KF6::Codecs
    KF6::XmlGui
    KF6::KIOWidgets
    KF6::KCMUtils
    KPim6::LdapWidgets
    KF6::ItemViews
)

if(NOT FORCE_DISABLE_AKONADI_SEARCH)
    target_link_libraries(KPim6PimCommonAkonadi PRIVATE KPim6::AkonadiSearchPIM)
endif()


target_include_directories(KPim6PimCommonAkonadi INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonAkonadi/>")

target_include_directories(KPim6PimCommonAkonadi PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KPim6PimCommonAkonadi PROPERTIES
    VERSION ${PIMCOMMONAKONADI_VERSION}
    SOVERSION ${PIMCOMMONAKONADI_SOVERSION}
    EXPORT_NAME PimCommonAkonadi
)


install(TARGETS
    KPim6PimCommonAkonadi
    EXPORT KPim6PimCommonAkonadiTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

if(BUILD_TESTING)
    add_subdirectory(acl/autotests)
    add_subdirectory(folderdialog/tests/)
    add_subdirectory(collectionpage/autotests/)
    add_subdirectory(ldap/tests)
    add_subdirectory(addressline/tests)
    add_subdirectory(addressline/autotests)
    if(NOT FORCE_DISABLE_AKONADI_SEARCH)
       add_subdirectory(addressline/blacklistbaloocompletion/autotests)
    endif()       
endif()



if(BUILD_DESIGNERPLUGIN)
        add_subdirectory(designer)
endif()

ecm_generate_headers(PimCommonAkonadi_Camelcaseaddressline_HEADERS
    HEADER_NAMES
    AddresseeLineEdit
    REQUIRED_HEADERS PimCommonAkonadi_addressline_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE addressline/addresslineedit/
)

ecm_generate_headers(PimCommonAkonadi_Camelcaserecentaddress_HEADERS
    HEADER_NAMES
    RecentAddresses
    REQUIRED_HEADERS PimCommonAkonadi_recentaddress_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE addressline/recentaddress/
)

ecm_generate_headers(PimCommonAkonadi_Camelcasecompletionconfiguredialog_HEADERS
    HEADER_NAMES
    CompletionConfigureDialog
    REQUIRED_HEADERS PimCommonAkonadi_completionconfiguredialog_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE addressline/completionconfiguredialog/
)



ecm_generate_headers(PimCommonAkonadi_Camelcasecollectionpage_HEADERS
  HEADER_NAMES
  IncidencesForWidget
  CollectionTypeUtil
  ContentTypeWidget
  REQUIRED_HEADERS PimCommonAkonadi_collectionpage_HEADERS
  PREFIX PimCommonAkonadi
  RELATIVE collectionpage
)

ecm_generate_headers(PimCommonAkonadi_CamelCaseUtil_HEADERS
    HEADER_NAMES
    CreateResource
    ImapResourceCapabilitiesManager
    MailUtil
    REQUIRED_HEADERS PimCommonAkonadi_Util_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE util
)

ecm_generate_headers(PimCommonAkonadi_Camelcaseprogresswidget_HEADERS
    HEADER_NAMES
    ProgressManagerAkonadi
    REQUIRED_HEADERS PimCommonAkonadi_progresswidget_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE progresswidget
)

ecm_generate_headers(PimCommonAkonadi_Camelcaseldap_HEADERS
    HEADER_NAMES
    LdapSearchDialog
    REQUIRED_HEADERS PimCommonAkonadi_ldap_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE ldap
)

ecm_generate_headers(PimCommonAkonadi_Camelcasemanagerserversidesubscription_HEADERS
    HEADER_NAMES
    ManageServerSideSubscriptionJob
    REQUIRED_HEADERS PimCommonAkonadi_managerserversidesubscription_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE manageserversidesubscription
)

ecm_generate_headers(PimCommonAkonadi_Camelcaseacl_HEADERS
    HEADER_NAMES
    CollectionAclPage
    ImapAclAttribute
    REQUIRED_HEADERS PimCommonAkonadi_acl_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE acl
)

ecm_generate_headers(PimCommonAkonadi_Camelcasefolderdialog_HEADERS
    HEADER_NAMES
    CheckedCollectionWidget
    SelectMultiCollectionDialog
    REQUIRED_HEADERS PimCommonAkonadi_folderdialog_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE folderdialog
)

ecm_generate_headers(PimCommonAkonadi_CamelCasegenericplugins_HEADERS
    HEADER_NAMES
    PluginInterface
    GenericPluginInterface
    REQUIRED_HEADERS PimCommonAkonadi_genericplugins_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE genericplugins
)

install(FILES
    ${PimCommonAkonadi_Camelcasecollectionpage_HEADERS}
    ${PimCommonAkonadi_Camelcaseacl_HEADERS}
    ${PimCommonAkonadi_Camelcaseldap_HEADERS}
    ${PimCommonAkonadi_Camelcasefolderdialog_HEADERS}
    ${PimCommonAkonadi_CamelCasegenericplugins_HEADERS}
    ${PimCommonAkonadi_Camelcasemanagerserversidesubscription_HEADERS}
    ${PimCommonAkonadi_Camelcasewidgets_HEADERS}
    ${PimCommonAkonadi_CamelCaseUtil_HEADERS}
    ${PimCommonAkonadi_Camelcaseprogresswidget_HEADERS}
    ${PimCommonAkonadi_Camelcasecompletionconfiguredialog_HEADERS}
    ${PimCommonAkonadi_Camelcaseaddressline_HEADERS}
    ${PimCommonAkonadi_Camelcaserecentaddress_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonAkonadi/PimCommonAkonadi
    COMPONENT Devel
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_export.h
    ${PimCommonAkonadi_acl_HEADERS}
    ${PimCommonAkonadi_ldap_HEADERS}
    ${PimCommonAkonadi_collectionpage_HEADERS}
    ${PimCommonAkonadi_folderdialog_HEADERS}
    ${PimCommonAkonadi_genericplugins_HEADERS}
    ${PimCommonAkonadi_casewidgets_HEADERS}
    ${PimCommonAkonadi_widgets_HEADERS}
    ${PimCommonAkonadi_managerserversidesubscription_HEADERS}
    ${PimCommonAkonadi_Util_HEADERS}
    ${PimCommonAkonadi_progresswidget_HEADERS}
    ${PimCommonAkonadi_completionconfiguredialog_HEADERS}
    ${PimCommonAkonadi_addressline_HEADERS}
    ${PimCommonAkonadi_recentaddress_HEADERS}


    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonAkonadi/pimcommonakonadi
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KPim6PimCommonAkonadi_QCH
        NAME KPim6PimCommonAkonadi
        BASE_NAME KPim6PimCommonAkonadi
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommonAkonadi_acl_HEADERS}
        ${PimCommonAkonadi_ldap_HEADERS}
        ${PimCommonAkonadi_collectionpage_HEADERS}
        ${PimCommonAkonadi_folderdialog_HEADERS}
        ${PimCommonAkonadi_genericplugins_HEADERS}
        ${PimCommonAkonadi_casewidgets_HEADERS}
        ${PimCommonAkonadi_widgets_HEADERS}
        ${PimCommonAkonadi_managerserversidesubscription_HEADERS}
        ${PimCommonAkonadi_Util_HEADERS}
        ${PimCommonAkonadi_progresswidget_HEADERS}
        ${PimCommonAkonadi_completionconfiguredialog_HEADERS}
        ${PimCommonAkonadi_completionorder_HEADERS}
        ${PimCommonAkonadi_addressline_HEADERS}
        ${PimCommonAkonadi_recentaddress_HEADERS}
        #MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMONAKONADI_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
)

endif()
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6PimCommonAkonadi")
if(BUILD_QCH)
ecm_install_qch_export(
    TARGETS KPim6PimCommonAkonadi_QCH
    FILE KPim6PimCommonAkonadiQchTargets.cmake
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6PimCommonAkonadiQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimCommonAkonadiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonAkonadiConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)




install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonAkonadiConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KPim6PimCommonAkonadiConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KPim6PimCommonAkonadiTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6PimCommonAkonadiTargets.cmake NAMESPACE KPim6::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/PimCommonAkonadi/ COMPONENT Devel
)

