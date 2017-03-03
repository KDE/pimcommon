ecm_add_test(imapaclattributetest.cpp ../imapaclattribute.cpp
    TEST_NAME imapaclattributetest
    NAME_PREFIX "pimcommon-acl-"
    LINK_LIBRARIES Qt5::Test Qt5::Gui KF5::AkonadiCore KF5::IMAP KF5::PimCommonAkonadi
    GUI
)

ecm_add_test(collectionaclwidgettest.cpp ../collectionaclwidget.cpp
    TEST_NAME collectionaclwidgettest
    NAME_PREFIX "pimcommon-acl-"
    LINK_LIBRARIES Qt5::Test Qt5::Gui KF5::AkonadiCore KF5::IMAP KF5::PimCommonAkonadi KF5::I18n
)
