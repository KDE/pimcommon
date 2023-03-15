# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(imapaclattributetest.cpp
    TEST_NAME imapaclattributetest
    NAME_PREFIX "pimcommon-acl-"
    LINK_LIBRARIES Qt::Test Qt::Gui KPim${KF_MAJOR_VERSION}::AkonadiCore KPim${KF_MAJOR_VERSION}::IMAP KPim${KF_MAJOR_VERSION}::PimCommonAkonadi
    GUI
)

ecm_add_test(collectionaclwidgettest.cpp ../collectionaclwidget.cpp
    TEST_NAME collectionaclwidgettest
    NAME_PREFIX "pimcommon-acl-"
    LINK_LIBRARIES Qt::Test Qt::Gui KPim${KF_MAJOR_VERSION}::AkonadiCore KPim${KF_MAJOR_VERSION}::IMAP KPim${KF_MAJOR_VERSION}::PimCommonAkonadi KF${KF_MAJOR_VERSION}::I18n
)
