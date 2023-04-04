# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(imapaclattributetest.cpp
    TEST_NAME imapaclattributetest
    NAME_PREFIX "pimcommon-acl-"
    LINK_LIBRARIES Qt::Test Qt::Gui KPim6::AkonadiCore KPim6::IMAP KPim6::PimCommonAkonadi
    GUI
)

ecm_add_test(collectionaclwidgettest.cpp ../collectionaclwidget.cpp
    TEST_NAME collectionaclwidgettest
    NAME_PREFIX "pimcommon-acl-"
    LINK_LIBRARIES Qt::Test Qt::Gui KPim6::AkonadiCore KPim6::IMAP KPim6::PimCommonAkonadi KF6::I18n
)
