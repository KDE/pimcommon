# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(customtoolswidgetngtest.cpp
    TEST_NAME customtoolswidgetngtest
    NAME_PREFIX pimcommon-
    LINK_LIBRARIES Qt::Test Qt::Gui KF5::PimCommon KF5::XmlGui
)

