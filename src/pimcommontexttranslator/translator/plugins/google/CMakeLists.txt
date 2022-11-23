# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

set(googletranslator_PART_SRCS
)
ecm_qt_declare_logging_category(googletranslator_PART_SRCS
    HEADER googletranslator_debug.h
    IDENTIFIER TRANSLATOR_GOOGLE
    CATEGORY_NAME org.kde.pim.pimcommontexttranslator.google
    DESCRIPTION "PimCommon google translator"
    EXPORT PIMCOMMON
)

add_library(translator_google MODULE ${googletranslator_PART_SRCS})
target_link_libraries(translator_google PRIVATE KF5::PimCommonTextTranslator)

install(TARGETS translator_google  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)
