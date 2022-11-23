# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

set(libretranslatetranslator_PART_SRCS
)
ecm_qt_declare_logging_category(libretranslatetranslator_PART_SRCS
    HEADER libretranslatetranslator_debug.h
    IDENTIFIER TRANSLATOR_libretranslate
    CATEGORY_NAME org.kde.pim.pimcommontexttranslator.libretranslate
    DESCRIPTION "PimCommon libretranslate translator"
    EXPORT PIMCOMMON
)

add_library(translator_libretranslate MODULE ${libretranslatetranslator_PART_SRCS})
target_link_libraries(translator_libretranslate PRIVATE KF5::PimCommonTextTranslator)

install(TARGETS translator_libretranslate  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)
