# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

set(bingtranslator_PART_SRCS
)
ecm_qt_declare_logging_category(bingtranslator_PART_SRCS
    HEADER bingtranslator_debug.h
    IDENTIFIER TRANSLATOR_bing
    CATEGORY_NAME org.kde.pim.pimcommontexttranslator.bing
    DESCRIPTION "PimCommon bing translator"
    EXPORT PIMCOMMON
)

add_library(translator_bing MODULE ${bingtranslator_PART_SRCS})
target_link_libraries(translator_bing PRIVATE KF5::PimCommonTextTranslator)

install(TARGETS translator_bing  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)
