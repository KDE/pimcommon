# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(genericpluginmanagertest.cpp genericpluginmanagertest.h
    TEST_NAME genericpluginmanagertest
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt::Test KPim${KF_MAJOR_VERSION}::PimCommon
)


ecm_add_test(actiontypetest.cpp actiontypetest.h
    TEST_NAME actiontypetest
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt::Test KPim${KF_MAJOR_VERSION}::PimCommon
)

ecm_add_test(pluginutiltest.cpp pluginutiltest.h
    TEST_NAME pluginutiltest
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt::Test KPim${KF_MAJOR_VERSION}::PimCommon
)

