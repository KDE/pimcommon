# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

set(deepltranslator_PART_SRCS
    deeplengineclient.cpp
    deeplengineclient.h
    deeplengineplugin.cpp
    deeplengineplugin.h
)
ecm_qt_declare_logging_category(deepltranslator_PART_SRCS
    HEADER deepltranslator_debug.h
    IDENTIFIER TRANSLATOR_deepl
    CATEGORY_NAME org.kde.pim.pimcommontexttranslator.deepl
    DESCRIPTION "PimCommon deepl translator"
    EXPORT PIMCOMMON
)

add_library(translator_deepl MODULE ${deepltranslator_PART_SRCS})
target_link_libraries(translator_deepl PRIVATE KF5::PimCommonTextTranslator KF5::I18n)

install(TARGETS translator_deepl  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)
