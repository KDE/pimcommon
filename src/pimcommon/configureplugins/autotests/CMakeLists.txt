set( pimcommon_configureplugins_source_SRCS configurepluginswidgettest.cpp )
add_executable( configurepluginswidgettest ${pimcommon_configureplugins_source_SRCS} )
add_test(NAME configurepluginswidgettest COMMAND configurepluginswidgettest )
ecm_mark_as_test(kmail-configurepluginswidgettest)
target_link_libraries( configurepluginswidgettest Qt5::Test KF5::I18n Qt5::Widgets
    KF5::ConfigCore KF5::TextWidgets KF5::WidgetsAddons KF5::PimCommon)


set( pimcommon_configurepluginslist_source_SRCS configurepluginslistwidgettest.cpp)
add_executable( configurepluginslistwidgettest ${pimcommon_configurepluginslist_source_SRCS} )
add_test(NAME configurepluginslistwidgettest COMMAND configurepluginslistwidgettest )
ecm_mark_as_test(kmail-configurepluginslistwidgettest)
target_link_libraries( configurepluginslistwidgettest Qt5::Test KF5::I18n Qt5::Widgets
    KF5::ConfigCore KF5::TextWidgets KF5::WidgetsAddons KF5::PimCommon)
