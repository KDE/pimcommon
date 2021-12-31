# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5PimCommonAkonadi")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5PimCommonAkonadi_QCH
        FILE KF5PimCommonAkonadiQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5PimCommonAkonadiQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5PimCommonAkonadiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonAkonadiConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX PIMCOMMON
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonAkonadiConfigVersion.cmake"
    SOVERSION 5
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonAkonadiConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5PimCommonAkonadiConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5PimCommonAkonadiTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5PimCommonAkonadiTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF} COMPONENT Devel
    )





set(libpimcommonakonadi_SRCS)


ecm_qt_declare_logging_category(libpimcommonakonadi_SRCS HEADER pimcommonakonadi_debug.h IDENTIFIER PIMCOMMONAKONADI_LOG CATEGORY_NAME org.kde.pim.pimcommonakonadi
        DESCRIPTION "kdepim (pimcommonakonadi)"
        EXPORT PIMCOMMON
    )



add_library(KF5PimCommonAkonadi )
add_library(KF5::PimCommonAkonadi ALIAS KF5PimCommonAkonadi)

target_sources(KF5PimCommonAkonadi PRIVATE
    ${libpimcommonakonadi_SRCS}
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
    widgets/annotationdialog.cpp
    ldap/ldapsearchdialog.cpp
    util/createresource.cpp
    util/imapresourcecapabilitiesmanager.cpp
    util/mailutil.cpp
   progresswidget/agentprogressmonitor.cpp
   progresswidget/progressmanagerakonadi.cpp
  collectionpage/collectiontypeutil.cpp
  collectionpage/attributeregistrar.cpp
  collectionpage/attributes/collectionannotationsattribute.cpp
  collectionpage/incidencesforwidget.cpp
  collectionpage/contenttypewidget.cpp
    addressline/completionorder/completionordereditor.cpp
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
    addressline/completionorder/completionordereditor.h
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
    collectionpage/attributes/collectionannotationsattribute.h
    folderdialog/checkedcollectionwidget.h
    folderdialog/selectmulticollectiondialog.h
    folderdialog/selectmulticollectionwidget.h
    widgets/annotationdialog.h
    pimcommonakonadi_private_export.h
    util/mailutil.h
    util/imapresourcecapabilitiesmanager.h
    util/createresource.h
    genericplugins/genericplugininterface.h
    genericplugins/plugininterface.h
    )

if (NOT FORCE_DISABLE_AKONADI_SEARCH)
target_sources(KF5PimCommonAkonadi PRIVATE
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


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5PimCommonAkonadi PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(KF5PimCommonAkonadi BASE_NAME pimcommonakonadi)

target_link_libraries(KF5PimCommonAkonadi
    PUBLIC
    KF5::PimCommon
    KF5::AkonadiCore
    KF5::AkonadiWidgets
    KF5::Contacts
    KF5::AkonadiContact
    KF5::KIOCore
    KF5::ConfigWidgets
    KF5::IMAP
    KF5::Libkdepim
    PRIVATE
    KF5::I18n
    KF5::Codecs
    KF5::PimTextEdit
    KF5::XmlGui
    KF5::PimTextEdit
    KF5::KIOWidgets
    KF5::KCMUtils
    KF5::Ldap
    KF5::ItemViews
    )

if (NOT FORCE_DISABLE_AKONADI_SEARCH)
    target_link_libraries(KF5PimCommonAkonadi PRIVATE KF5::AkonadiSearchPIM)
endif()


target_include_directories(KF5PimCommonAkonadi INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonAkonadi/;${KDE_INSTALL_INCLUDEDIR_KF}/pimcommonakonadi>")

target_include_directories(KF5PimCommonAkonadi PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")

set_target_properties(KF5PimCommonAkonadi PROPERTIES
    VERSION ${PIMCOMMON_VERSION}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommonAkonadi
    )


install(TARGETS
    KF5PimCommonAkonadi
    EXPORT KF5PimCommonAkonadiTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
    )

if (BUILD_TESTING)
    add_subdirectory(acl/autotests)
    add_subdirectory(folderdialog/tests/)
    add_subdirectory(collectionpage/autotests/)
    add_subdirectory(ldap/tests)
    add_subdirectory(addressline/tests)
    add_subdirectory(addressline/autotests)
    if (NOT FORCE_DISABLE_AKONADI_SEARCH)
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

ecm_generate_headers(PimCommonAkonadi_Camelcasecompletionorder_HEADERS
    HEADER_NAMES
    CompletionOrderEditor
    REQUIRED_HEADERS PimCommonAkonadi_completionorder_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE addressline/completionorder
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

ecm_generate_headers(PimCommonAkonadi_Camelcasecollectionpageattributes_HEADERS
  HEADER_NAMES
  CollectionAnnotationsAttribute
  REQUIRED_HEADERS PimCommonAkonadi_collectionpageattributes_HEADERS
  PREFIX PimCommonAkonadi
  RELATIVE collectionpage/attributes
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

ecm_generate_headers(PimCommonAkonadi_Camelcasewidgets_HEADERS
    HEADER_NAMES
    AnnotationDialog
    REQUIRED_HEADERS PimCommonAkonadi_widgets_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE widgets
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

ecm_generate_pri_file(BASE_NAME PimCommonAkonadi
    LIB_NAME KF5PimCommonAkonadi
    DEPS "AkonadiCore AkonadiWidgets KContacts AkonadiContact network KIOCore KConfigWidgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonAkonadi
    )


install(FILES
    ${PimCommonAkonadi_Camelcasecollectionpage_HEADERS}
    ${PimCommonAkonadi_Camelcasecollectionpageattributes_HEADERS}
    ${PimCommonAkonadi_Camelcaseacl_HEADERS}
    ${PimCommonAkonadi_Camelcaseldap_HEADERS}
    ${PimCommonAkonadi_Camelcasefolderdialog_HEADERS}
    ${PimCommonAkonadi_CamelCasegenericplugins_HEADERS}
    ${PimCommonAkonadi_Camelcasemanagerserversidesubscription_HEADERS}
    ${PimCommonAkonadi_Camelcasewidgets_HEADERS}
    ${PimCommonAkonadi_CamelCaseUtil_HEADERS}
    ${PimCommonAkonadi_Camelcaseprogresswidget_HEADERS}
    ${PimCommonAkonadi_Camelcasecompletionconfiguredialog_HEADERS}
    ${PimCommonAkonadi_Camelcasecompletionorder_HEADERS}
    ${PimCommonAkonadi_Camelcaseaddressline_HEADERS}
    ${PimCommonAkonadi_Camelcaserecentaddress_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PimCommonAkonadi
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_export.h
    ${PimCommonAkonadi_acl_HEADERS}
    ${PimCommonAkonadi_ldap_HEADERS}
    ${PimCommonAkonadi_collectionpage_HEADERS}
    ${PimCommonAkonadi_collectionpageattributes_HEADERS}
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


    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/pimcommonakonadi
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_QCH)
    ecm_add_qch(
        KF5PimCommonAkonadi_QCH
        NAME KF5PimCommonAkonadi
        BASE_NAME KF5PimCommonAkonadi
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${PimCommonAkonadi_acl_HEADERS}
        ${PimCommonAkonadi_ldap_HEADERS}
        ${PimCommonAkonadi_collectionpage_HEADERS}
        ${PimCommonAkonadi_collectionpageattributes_HEADERS}
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
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PIMCOMMONAKONADI_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
