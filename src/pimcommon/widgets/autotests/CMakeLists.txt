# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(kactionmenuchangecasetest.cpp
    TEST_NAME kactionmenuchangecasetest
    NAME_PREFIX pimcommon-widget
    LINK_LIBRARIES Qt::Test Qt::Gui KF5::WidgetsAddons KF5::I18n KF5::XmlGui KF5::PimCommon
)

ecm_add_test(lineeditwithcompleterngtest.cpp
    TEST_NAME lineeditwithcompleterngtest
    NAME_PREFIX pimcommon-widget
    LINK_LIBRARIES Qt::Test Qt::Gui KF5::WidgetsAddons KF5::I18n KF5::PimCommon
)

ecm_add_test(purposemenuwidgettest.cpp
    TEST_NAME purposemenuwidgettest
    NAME_PREFIX pimcommon-widget
    LINK_LIBRARIES Qt::Test Qt::Gui KF5::WidgetsAddons KF5::I18n KF5::PimCommon KF5::Purpose KF5::PurposeWidgets
    )
