# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)
add_library(translator_lingva MODULE)

ecm_qt_declare_logging_category(translator_lingva_debug_SRCS
    HEADER lingvatranslator_debug.h
    IDENTIFIER TRANSLATOR_LINGVA_LOG
    CATEGORY_NAME org.kde.pim.pimcommontexttranslator.lingva
    DESCRIPTION "PimCommon lingva translator"
    EXPORT PIMCOMMON
)

target_sources(translator_lingva PRIVATE
    ${translator_lingva_debug_SRCS}
    lingvaengineclient.cpp
    lingvaengineclient.h
    lingvaengineplugin.cpp
    lingvaengineplugin.h
    lingvaenginedialog.h
    lingvaenginedialog.cpp
    lingvaenginewidget.h
    lingvaenginewidget.cpp
    lingvaengineutil.h
    lingvaengineutil.cpp
)

target_link_libraries(translator_lingva PRIVATE KF5::PimCommonTextTranslator KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::ConfigCore)

install(TARGETS translator_lingva  DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/translator/)
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
