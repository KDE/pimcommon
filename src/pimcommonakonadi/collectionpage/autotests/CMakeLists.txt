macro(add_mailcommon_collectionpage_test _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-collectionpage-"
        LINK_LIBRARIES Qt5::Test Qt5::Gui KF5::AkonadiCore KF5::PimCommonAkonadi KF5::Completion
    )
endmacro()

add_mailcommon_collectionpage_test(collectionannotationsattributetest
    collectionannotationsattributetest.cpp
    ../attributes/collectionannotationsattribute.cpp
)
add_mailcommon_collectionpage_test(incidencesforwidgettest
    incidencesforwidgettest.cpp
)
add_mailcommon_collectionpage_test(contenttypewidgettest
    contenttypewidgettest.cpp
)
