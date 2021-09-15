include(ECMAddQtDesignerPlugin)
ecm_qtdesignerplugin_widget(PimCommon::SimpleStringListEditor
    INCLUDE_FILE "PimCommon/SimpleStringListEditor"
    TOOLTIP "A listbox with add/remove/move up/down button (KDE-PIM)"
    WHATSTHIS "A listbox which lets organize list order."
    GROUP "Input (KDE-PIM)"
    )
ecm_qtdesignerplugin_widget(PimCommon::TranslatorWidget
    INCLUDE_FILE "PimCommon/TranslatorWidget"
    TOOLTIP "A widget to make translate string (KDE-PIM)"
    WHATSTHIS "A widget to make translate string."
    GROUP "Input (KDE-PIM)"
    )

ecm_add_qtdesignerplugin(pimcommonwidgets
    NAME PimCommonWidgets
    OUTPUT_NAME pimcommonwidgets
    WIDGETS
    PimCommon::SimpleStringListEditor
    PimCommon::TranslatorWidget
    LINK_LIBRARIES
    KF5::PimCommon KF5::PimTextEdit
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
    )
