# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
ecm_add_test(translatortest.cpp
    NAME_PREFIX "pimcommon-translator-"
    LINK_LIBRARIES KF5::PimCommon Qt${QT_MAJOR_VERSION}::Test KF5::XmlGui KF5::PimTextEdit
)
