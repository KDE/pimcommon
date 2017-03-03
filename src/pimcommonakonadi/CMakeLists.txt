
add_definitions( -DQT_NO_CAST_FROM_ASCII )
add_definitions( -DQT_NO_CAST_TO_ASCII )

set(libpimcommonakonadi_folderdialog_SRCS
    folderdialog/selectmulticollectionwidget.cpp
    folderdialog/selectmulticollectiondialog.cpp
    folderdialog/checkedcollectionwidget.cpp
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

set(libpimcommonakonadi_SRCS
    ${libpimcommonakonadi_acl_SRCS}
    ${libpimcommonakonadi_folderdialog_SRCS}
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
    Qt5::Network
    KF5::KIOCore
    KF5::ConfigWidgets
    PRIVATE
    KF5::I18n
    KF5::IMAP
    KF5::Libkdepim
    KF5::Archive
    KF5::Codecs
    KF5::NewStuff
    KF5::PimTextEdit
    KF5::Wallet
    KF5::DBusAddons
    KF5::XmlGui
    KF5::PimTextEdit
    KF5::IconThemes
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
endif()


ecm_generate_headers(PimCommon_Camelcaseacl_HEADERS
    HEADER_NAMES
    CollectionAclPage
    ImapAclAttribute
    REQUIRED_HEADERS PimCommon_acl_HEADERS
    PREFIX PimCommon
    RELATIVE acl
    )

ecm_generate_headers(PimCommon_Camelcasefolderdialog_HEADERS
    HEADER_NAMES
    CheckedCollectionWidget
    SelectMultiCollectionDialog
    REQUIRED_HEADERS PimCommon_folderdialog_HEADERS
    PREFIX PimCommon
    RELATIVE folderdialog
    )

ecm_generate_pri_file(BASE_NAME PimCommonAkonadi
    LIB_NAME KF5PimCommonAkonadi
    DEPS "AkonadiCore AkonadiWidgets Contacts AkonadiContact Network KIOCore ConfigWidgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommonAkonadi
    )


install(FILES
    ${PimCommon_Camelcaseacl_HEADERS}
    ${PimCommon_Camelcasefolderdialog_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/PimCommonAkonadi
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_debug.h
    ${CMAKE_CURRENT_BINARY_DIR}/pimcommonakonadi_export.h
    ${PimCommon_acl_HEADERS}
    ${PimCommon_folderdialog_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/pimcommonAkonadi
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
