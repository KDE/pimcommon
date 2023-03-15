# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(customtoolswidgetngtest.cpp customtoolswidgetngtest.h
    TEST_NAME customtoolswidgetngtest
    NAME_PREFIX pimcommon-
    LINK_LIBRARIES Qt::Test Qt::Gui KPim${KF_MAJOR_VERSION}::PimCommon KF${KF_MAJOR_VERSION}::XmlGui
)

