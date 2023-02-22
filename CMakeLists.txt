# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.22.50")

project(pimcommon VERSION ${PIM_VERSION})

set(KF_MIN_VERSION "5.103.0")

find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
include(ECMAddTests)
include(ECMInstallIcons)
include(ECMAddQtDesignerPlugin)
include(ECMAddQch)


option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

set(PIMCOMMON_LIB_VERSION ${PIM_VERSION})
set(LIBKDEPIM_LIB_VERSION "5.22.40")
set(QT_REQUIRED_VERSION "5.15.2")
if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_REQUIRED_VERSION "6.4.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
    set(KTEXTADDONS_MIN_VERSION "1.0.42")
else()
    set(KF_MAJOR_VERSION "5")
    set(KTEXTADDONS_MIN_VERSION "1.0.0")
endif()
set(KIMAP_LIB_VERSION "5.22.40")
set(KPIMTEXTEDIT_LIB_VERSION "5.22.40")
set(KLDAP_LIB_VERSION "5.22.40")

set(AKONADICONTACT_LIB_VERSION "5.22.40")
set(AKONADI_VERSION "5.22.40")

find_package(Qt${QT_MAJOR_VERSION} ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets DBus Network Test Xml)

find_package(KF${KF_MAJOR_VERSION}Archive ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Codecs ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Config ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}ConfigWidgets ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}CoreAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}I18n ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}ItemModels ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}JobWidgets ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}KIO ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}NewStuff ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Service ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}WidgetsAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}XmlGui ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}KCMUtils ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Contacts ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimTextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}Ldap ${KLDAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim${KF_MAJOR_VERSION}Libkdepim ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)

find_package(KF${KF_MAJOR_VERSION}Purpose ${KF_MIN_VERSION} CONFIG REQUIRED)
option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

option(BUILD_DESIGNERPLUGIN "Build plugin for Qt Designer" ON)
add_feature_info(DESIGNERPLUGIN ${BUILD_DESIGNERPLUGIN} "Build plugin for Qt Designer")


option(FORCE_DISABLE_AKONADI_SEARCH "Disable features and API that require akonadi-search, e.g. because xapian isn't available" OFF)
if (UNIX)
    if (NOT FORCE_DISABLE_AKONADI_SEARCH)
        find_package(KF5AkonadiSearch ${AKONADI_SEARCH_VERSION} CONFIG REQUIRED)
        set_package_properties(KF5AkonadiSearch PROPERTIES DESCRIPTION "The Akonadi Search libraries" URL "https://invent.kde.org/pim/akonadi-search" TYPE REQUIRED PURPOSE "Provides search capabilities in KMail and Akonadi")
    endif()
else()
    if (NOT FORCE_DISABLE_AKONADI_SEARCH)
        find_package(KF5AkonadiSearch ${AKONADI_SEARCH_VERSION} CONFIG)
        set_package_properties(KF5AkonadiSearch PROPERTIES DESCRIPTION "The Akonadi Search libraries" URL "https://invent.kde.org/pim/akonadi-search" TYPE OPTIONAL PURPOSE "Provides search capabilities in KMail and Akonadi")
    endif()
endif()

if (NOT KF5AkonadiSearch_FOUND)
    set(FORCE_DISABLE_AKONADI_SEARCH TRUE)
endif()

set(DISABLE_AKONADI_SEARCH ${FORCE_DISABLE_AKONADI_SEARCH})
configure_file(config-akonadi-search.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/config-akonadi-search.h)


if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

########### Targets ###########

ecm_set_disabled_deprecation_versions(QT 5.15.2  KF 5.103.0)

find_package(KF${KF_MAJOR_VERSION}TextAutoCorrection ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)

add_subdirectory(src)
ecm_qt_install_logging_categories(
        EXPORT PIMCOMMON
        FILE pimcommon.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
