cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.14.80")

project(pimcommon VERSION ${PIM_VERSION})

set(KF5_MIN_VERSION "5.71.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(LIBRARY_NAMELINK)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(FeatureSummary)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)
include(ECMInstallIcons)
include(ECMAddQtDesignerPlugin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PIMCOMMON_LIB_VERSION ${PIM_VERSION})
set(AKONADICONTACT_LIB_VERSION "5.14.40")
set(LIBKDEPIM_LIB_VERSION "5.14.41")
set(QT_REQUIRED_VERSION "5.13.0")
set(KMIME_LIB_VERSION "5.14.40")
set(KIMAP_LIB_VERSION "5.14.40")
set(KPIMTEXTEDIT_LIB_VERSION "5.14.40")
set(AKONADI_VERSION "5.14.40")
set(KLDAP_LIB_VERSION "5.14.41")


find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets DBus Network Test Xml PrintSupport)

find_package(KF5Archive ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Codecs ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5ConfigWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5ItemModels ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5JobWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5NewStuff ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Service ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5WidgetsAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KCMUtils ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Contacts ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimTextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Ldap ${KLDAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)

find_package(KF5Purpose ${KF5_MIN_VERSION} CONFIG REQUIRED)


option(BUILD_DESIGNERPLUGIN "Build plugin for Qt Designer" ON)
add_feature_info(DESIGNERPLUGIN ${BUILD_DESIGNERPLUGIN} "Build plugin for Qt Designer")

option(FORCE_DISABLE_AKONADI_SEARCH "Disable features and API that require akonadi-search, e.g. because xapian isn't available" OFF)
if (NOT FORCE_DISABLE_AKONADI_SEARCH)
   find_package(KF5AkonadiSearch ${AKONADISEARCH_LIB_VERSION} CONFIG REQUIRED)
   set_package_properties(KF5AkonadiSearch PROPERTIES DESCRIPTION "The Akonadi Search libraries" URL "https://www.kde.org" TYPE REQUIRED PURPOSE "Provides search capabilities in KMail and Akonadi")
endif()

set(DISABLE_AKONADI_SEARCH ${FORCE_DISABLE_AKONADI_SEARCH})
configure_file(config-akonadi-search.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/config-akonadi-search.h)


find_package(Xsltproc)
set_package_properties(Xsltproc PROPERTIES DESCRIPTION "XSLT processor from libxslt" TYPE REQUIRED PURPOSE "Required to generate D-Bus interfaces for all Akonadi resources.")

if(BUILD_TESTING)
   find_package(KF5Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

########### Targets ###########

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050f00)
add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x054800) 

add_definitions(-DQT_NO_FOREACH)
add_definitions(-DQT_NO_KEYWORDS)

add_subdirectory(src)
ecm_qt_install_logging_categories(
        EXPORT PIMCOMMON
        FILE pimcommon.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
