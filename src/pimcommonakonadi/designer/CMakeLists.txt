include(ECMAddQtDesignerPlugin)
ecm_qtdesignerplugin_widget(PimCommon::AddresseeLineEdit
    INCLUDE_FILE "PimCommonAkonadi/AddresseeLineEdit"
    TOOLTIP "Addressee Line Edit (KDE-PIM)"
    WHATSTHIS "A line edit which lets you select addressees from the addressbook"
    GROUP "Input (KDE-PIM)"
    )

ecm_add_qtdesignerplugin(pimcommonakonadiwidgets
    NAME PimCommonAkonadiWidgets
    OUTPUT_NAME pimcommonakonadiwidgets
    WIDGETS
    PimCommon::AddresseeLineEdit
    LINK_LIBRARIES
    KF5::PimCommonAkonadi
    KF5::Completion
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
    )
