# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(genericpluginmanagertest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::PimCommonAkonadi
)


ecm_add_test(actiontypetest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::PimCommonAkonadi
)

ecm_add_test(pluginutiltest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::PimCommonAkonadi
)

