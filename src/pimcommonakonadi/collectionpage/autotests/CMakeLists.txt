macro(add_pimcommon_collectionpage_test _name)
    ecm_add_test(${ARGN}
        TEST_NAME ${_name}
        NAME_PREFIX "pimcommon-collectionpage-"
        LINK_LIBRARIES Qt::Test Qt::Gui KF5::AkonadiCore KF5::PimCommonAkonadi
    )
endmacro()

add_pimcommon_collectionpage_test(collectionannotationsattributetest
    collectionannotationsattributetest.cpp
)
add_pimcommon_collectionpage_test(incidencesforwidgettest
    incidencesforwidgettest.cpp
)
add_pimcommon_collectionpage_test(contenttypewidgettest
    contenttypewidgettest.cpp
)
