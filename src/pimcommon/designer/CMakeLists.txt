# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
include(ECMAddQtDesignerPlugin)
ecm_qtdesignerplugin_widget(PimCommon::SimpleStringListEditor
    INCLUDE_FILE "PimCommon/SimpleStringListEditor"
    TOOLTIP "A listbox with add/remove/move up/down button (KDE-PIM)"
    WHATSTHIS "A listbox which lets organize list order."
    GROUP "Input (KDE-PIM)"
)
ecm_add_qtdesignerplugin(pimcommonwidgets
    NAME PimCommonWidgets
    OUTPUT_NAME pimcommon6widgets
    WIDGETS
    PimCommon::SimpleStringListEditor
    LINK_LIBRARIES
    KPim6::PimCommon
    INSTALL_DESTINATION "${KDE_INSTALL_QTPLUGINDIR}/designer"
    COMPONENT Devel
)
