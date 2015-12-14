ecm_add_test(genericpluginmanagertest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt5::Test KF5::PimCommon
)


ecm_add_test(actiontypetest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt5::Test KF5::PimCommon
)
