if (USE_NEW_DESIGNERPLUGIN_MACRO)
    include(ECMAddQtDesignerPlugin)
    ecm_qtdesignerplugin_widget(PimCommon::SimpleStringListEditor
        INCLUDE_FILE "pimcommon/simplestringlisteditor.h"
        TOOLTIP "A listbox with add/remove/move up/down button (KDE-PIM)"
        WHATSTHIS "A listbox which lets organize list order."
        GROUP "Input (KDE-PIM)"
        )
    ecm_qtdesignerplugin_widget(PimCommon::TranslatorWidget
        INCLUDE_FILE "pimcommon/translatorwidget.h"
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
else()

    if (KF5DesignerPlugin_FOUND)
        kf5designerplugin_add_plugin(pimcommonwidgets pimcommon.widgets)
        target_link_libraries(pimcommonwidgets
            KF5::PimCommon KF5::PimTextEdit
            )
        if(NOT WIN32)
            # Since there are no libraries provided by this module,
            # there is no point including the build tree in RPath,
            # and then having to edit it at install time.
            set_target_properties(pimcommonwidgets PROPERTIES
                SKIP_BUILD_RPATH TRUE
                BUILD_WITH_INSTALL_RPATH TRUE
                )
        endif()

        install(TARGETS
            pimcommonwidgets
            DESTINATION ${KDE_INSTALL_QTPLUGINDIR}/designer
            )
    endif()
endif()
