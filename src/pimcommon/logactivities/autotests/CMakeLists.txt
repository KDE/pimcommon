# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(logactivitiesmanagertest.cpp
    NAME_PREFIX "pimcommon-logactivities-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::PimCommon KF5::PimTextEdit
)

ecm_add_test(logactivitieswidgettest.cpp
    NAME_PREFIX "pimcommon-logactivities-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::PimCommon KF5::PimTextEdit
)

ecm_add_test(logactivitiesdialogtest.cpp
    NAME_PREFIX "pimcommon-logactivities-"
    LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::PimCommon KF5::PimTextEdit
)
