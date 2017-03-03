set( pimcommon_configureplugins_source_SRCS configurepluginswidgettest.cpp ../configurepluginswidget.cpp ../configurepluginslistwidget.cpp )
add_executable( configurepluginswidgettest ${pimcommon_configureplugins_source_SRCS} )
add_test( configurepluginswidgettest configurepluginswidgettest )
ecm_mark_as_test(kmail-configurepluginswidgettest)
target_link_libraries( configurepluginswidgettest Qt5::Test KF5::I18n Qt5::Widgets
    KF5::ConfigCore KF5::TextWidgets KF5::WidgetsAddons KF5::PimCommonAkonadi)


set( pimcommon_configurepluginslist_source_SRCS configurepluginslistwidgettest.cpp ../configurepluginslistwidget.cpp  )
add_executable( configurepluginslistwidgettest ${pimcommon_configurepluginslist_source_SRCS} )
add_test( configurepluginslistwidgettest configurepluginslistwidgettest )
ecm_mark_as_test(kmail-configurepluginslistwidgettest)
target_link_libraries( configurepluginslistwidgettest Qt5::Test KF5::I18n Qt5::Widgets
    KF5::ConfigCore KF5::TextWidgets KF5::WidgetsAddons KF5::PimCommonAkonadi)
