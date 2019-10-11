cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.12.3")

project(pimcommon VERSION ${PIM_VERSION})

set(KF5_MIN_VERSION "5.60.0")

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

include(ECMSetupVersion)
include(FeatureSummary)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)
include(ECMInstallIcons)




set(PIMCOMMON_LIB_VERSION ${PIM_VERSION})
set(AKONADICONTACT_LIB_VERSION "5.12.2")
set(LIBKDEPIM_LIB_VERSION "5.12.2")
set(QT_REQUIRED_VERSION "5.11.0")
set(KMIME_LIB_VERSION "5.12.2")
set(KIMAP_LIB_VERSION "5.12.2")
set(KCONTACTS_LIB_VERSION "5.12.2")
set(KPIMTEXTEDIT_LIB_VERSION "5.12.2")
set(AKONADI_VERSION "5.12.2")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets DBus Network Test Xml PrintSupport)

find_package(KF5Archive ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Codecs ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Completion ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5ConfigWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5DBusAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5ItemModels ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5JobWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5NewStuff ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Service ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5WidgetsAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Contacts ${KCONTACTS_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5LibkdepimAkonadi ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimTextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)

find_package(KF5Purpose ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5DesignerPlugin ${KF5_MIN_VERSION} CONFIG)
set_package_properties(KF5DesignerPlugin PROPERTIES DESCRIPTION "KF5 designer plugin" TYPE OPTIONAL)

find_package(Xsltproc)
set_package_properties(Xsltproc PROPERTIES DESCRIPTION "XSLT processor from libxslt" TYPE REQUIRED PURPOSE "Required to generate D-Bus interfaces for all Akonadi resources.")

if(BUILD_TESTING)
   find_package(KF5Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

########### Targets ###########

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
add_definitions(-DQT_NO_FOREACH)

add_subdirectory(src)
install(FILES pimcommon.renamecategories pimcommon.categories  DESTINATION  ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
