# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(genericpluginmanagertest.cpp genericpluginmanagertest.h
    TEST_NAME genericpluginmanagertest
    LINK_LIBRARIES Qt::Test KPim6::PimCommon
)

ecm_add_test(actiontypetest.cpp actiontypetest.h
    TEST_NAME actiontypetest
    LINK_LIBRARIES Qt::Test KPim6::PimCommon
)

ecm_add_test(pluginutiltest.cpp pluginutiltest.h
    TEST_NAME pluginutiltest
    LINK_LIBRARIES Qt::Test KPim6::PimCommon
)
