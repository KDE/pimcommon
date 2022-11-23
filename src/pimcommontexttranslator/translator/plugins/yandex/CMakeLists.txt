# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

set(yandextranslator_PART_SRCS
)
ecm_qt_declare_logging_category(yandextranslator_PART_SRCS
    HEADER yandextranslator_debug.h
    IDENTIFIER TRANSLATOR_yandex
    CATEGORY_NAME org.kde.pim.pimcommontexttranslator.yandex
    DESCRIPTION "PimCommon yandex translator"
    EXPORT PIMCOMMON
)

add_library(translator_yandex MODULE ${yandextranslator_PART_SRCS})
target_link_libraries(translator_yandex PRIVATE KF5::PimCommonTextTranslator)

install(TARGETS translator_yandex  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)
