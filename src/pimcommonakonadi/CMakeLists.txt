include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5PimCommonAkonadi")

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
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
    )


set(libpimcommonakonadi_folderdialog_SRCS
    folderdialog/selectmulticollectionwidget.cpp
    folderdialog/selectmulticollectiondialog.cpp
    folderdialog/checkedcollectionwidget.cpp
    )


set(libpimcommonakonadi_generericplugin_SRCS
    genericplugins/genericplugininterface.cpp
    genericplugins/plugininterface.cpp
    )

set(libpimcommonakonadi_acl_SRCS
    acl/aclentrydialog.cpp
    acl/aclmanager.cpp
    acl/aclutils.cpp
    acl/collectionaclpage.cpp
    acl/imapaclattribute.cpp
    acl/collectionaclwidget.cpp
    acl/acllistview.cpp
    acl/aclmodifyjob.cpp
    )

set(libpimcommonakonadi_manageserversidesubscription_SRCS
    manageserversidesubscription/manageserversidesubscriptionjob.cpp
    )

set(libpimcommonakonadi_widgets_SRCS
    widgets/annotationdialog.cpp
    )

set(libpimcommon_job_SRCS
    job/fetchrecursivecollectionsjob.cpp
    )

set(libpimcommonakonadi_util_SRCS
    util/createresource.cpp
    util/imapresourcecapabilitiesmanager.cpp
    util/mailutil.cpp
    )

set(libpimcommonakonadi_collection_SRCS
  collectionpage/collectiontypeutil.cpp
  collectionpage/attributeregistrar.cpp
  collectionpage/attributes/collectionannotationsattribute.cpp
  collectionpage/incidencesforwidget.cpp
  collectionpage/contenttypewidget.cpp
)


set(libpimcommonakonadi_SRCS
    ${libpimcommonakonadi_collection_SRCS}
    ${libpimcommonakonadi_acl_SRCS}
    ${libpimcommonakonadi_folderdialog_SRCS}
    ${libpimcommonakonadi_generericplugin_SRCS}
    ${libpimcommonakonadi_configure_plugins_SRCS}
    ${libpimcommonakonadi_manageserversidesubscription_SRCS}
    ${libpimcommonakonadi_widgets_SRCS}
    ${libpimcommonakonadi_util_SRCS}
    ${libpimcommon_job_SRCS}
    )


ecm_qt_declare_logging_category(libpimcommonakonadi_SRCS HEADER pimcommonakonadi_debug.h IDENTIFIER PIMCOMMONAKONADI_LOG CATEGORY_NAME org.kde.pim.pimcommonakonadi)


add_library(KF5PimCommonAkonadi ${libpimcommonakonadi_SRCS})
generate_export_header(KF5PimCommonAkonadi BASE_NAME pimcommonakonadi)
add_library(KF5::PimCommonAkonadi ALIAS KF5PimCommonAkonadi)

target_link_libraries(KF5PimCommonAkonadi
    PUBLIC
    KF5::PimCommon
    KF5::AkonadiCore
    KF5::AkonadiWidgets
    KF5::Contacts
    KF5::AkonadiContact
    KF5::KIOCore
    KF5::ConfigWidgets
    PRIVATE
    KF5::I18n
    KF5::IMAP
    KF5::LibkdepimAkonadi
    KF5::Codecs
    KF5::PimTextEdit
    KF5::DBusAddons
    KF5::XmlGui
    KF5::PimTextEdit
    KF5::Completion
    KF5::KIOWidgets
    )

target_include_directories(KF5PimCommonAkonadi INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommonAkonadi/;${KDE_INSTALL_INCLUDEDIR_KF5}/pimcommonakonadi>")

target_include_directories(KF5PimCommonAkonadi PUBLIC "$<BUILD_INTERFACE:${pimcommon_SOURCE_DIR}/src;${pimcommon_BINARY_DIR}/src>")
target_include_directories(KF5PimCommonAkonadi PUBLIC $<TARGET_PROPERTY:KF5::IMAP,INTERFACE_INCLUDE_DIRECTORIES>)

set_target_properties(KF5PimCommonAkonadi PROPERTIES
    VERSION ${PIMCOMMON_VERSION_STRING}
    SOVERSION ${PIMCOMMON_SOVERSION}
    EXPORT_NAME PimCommonAkonadi
    )


install(TARGETS
    KF5PimCommonAkonadi
    EXPORT KF5PimCommonAkonadiTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}  ${LIBRARY_NAMELINK}
    )

if (BUILD_TESTING)
    add_subdirectory(acl/autotests)
    add_subdirectory(folderdialog/tests/)
    add_subdirectory(collectionpage/autotests/)
endif()

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


ecm_generate_headers(PimCommonAkonadiUtil_CamelCase_HEADERS
    HEADER_NAMES
    CreateResource
    ImapResourceCapabilitiesManager
    MailUtil
    REQUIRED_HEADERS PimCommonAkonadiUtil_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE util
    )

ecm_generate_headers(PimCommon_CamelCasejob_HEADERS
    HEADER_NAMES
    FetchRecursiveCollectionsJob
    REQUIRED_HEADERS PimCommon_job_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE job
    )


ecm_generate_headers(PimCommonAkonadi_Camelcasewidgets_HEADERS
    HEADER_NAMES
    AnnotationDialog
    REQUIRED_HEADERS PimCommonAkonadi_widgets_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE widgets
    )

ecm_generate_headers(PimCommon_Camelcasemanagerserversidesubscription_HEADERS
    HEADER_NAMES
    ManageServerSideSubscriptionJob
    REQUIRED_HEADERS PimCommon_managerserversidesubscription_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE manageserversidesubscription
    )

ecm_generate_headers(PimCommon_Camelcaseacl_HEADERS
    HEADER_NAMES
    CollectionAclPage
    ImapAclAttribute
    REQUIRED_HEADERS PimCommon_acl_HEADERS
    PREFIX PimCommonAkonadi
    RELATIVE acl
    )

ecm_generate_headers(PimCommon_Camelcasefolderdialog_HEADERS
    HEADER_NAMES
    CheckedCollectionWidget
    SelectMultiCollectionDialog
    REQUIRED_HEADERS PimCommon_folderdialog_HEADERS
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
    DEPS "AkonadiCore AkonadiWidgets Contacts AkonadiContact Network KIOCore ConfigWidgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommonAkonadi
    )


install(FILES
    ${PimCommonAkonadi_Camelcasecollectionpage_HEADERS}
    ${PimCommonAkonadi_Camelcasecollectionpageattributes_HEADERS}
    ${PimCommon_CamelCasejob_HEADERS}
    ${PimCommon_Camelcaseacl_HEADERS}
    ${PimCommon_Camelcasefolderdialog_HEADERS}
    ${PimCommonAkonadi_CamelCasegenericplugins_HEADERS}
    ${PimCommon_Camelcasemanagerserversidesubscription_HEADERS}
    ${PimCommonAkonadi_Camelcasewidgets_HEADERS}
    ${PimCommonAkonadiUtil_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommonAkonadi
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_debug.h
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_export.h
    ${PimCommon_acl_HEADERS}
    ${PimCommonAkonadi_collectionpage_HEADERS}
    ${PimCommonAkonadi_collectionpageattributes_HEADERS}
    ${PimCommon_folderdialog_HEADERS}
    ${PimCommonAkonadi_genericplugins_HEADERS}
    ${PimCommon_serversidesubscription_HEADERS}
    ${PimCommonAkonadi_casewidgets_HEADERS}
    ${PimCommonAkonadi_widgets_HEADERS}
    ${PimCommon_managerserversidesubscription_HEADERS}
    ${PimCommon_job_HEADERS}
    ${PimCommonAkonadiUtil_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/pimcommonakonadi
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
