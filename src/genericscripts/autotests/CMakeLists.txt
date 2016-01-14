
ecm_add_test(genericscriptsmanagertest.cpp
    NAME_PREFIX "pimcommon-genericscripts-"
    LINK_LIBRARIES Qt5::Test KF5::PimCommon
)

ecm_add_test(genericscripttest.cpp
    NAME_PREFIX "pimcommon-genericscripts-"
    LINK_LIBRARIES Qt5::Test KF5::PimCommon
)

ecm_add_test(genericscriptactiontest.cpp
    NAME_PREFIX "pimcommon-genericscripts-"
    LINK_LIBRARIES Qt5::Test KF5::PimCommon
)
