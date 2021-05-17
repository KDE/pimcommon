ecm_add_test(genericpluginmanagertest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt::Test KF5::PimCommonAkonadi
)


ecm_add_test(actiontypetest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt::Test KF5::PimCommonAkonadi
)

ecm_add_test(pluginutiltest.cpp
    NAME_PREFIX "pimcommon-genericplugins-"
    LINK_LIBRARIES Qt::Test KF5::PimCommonAkonadi
)

