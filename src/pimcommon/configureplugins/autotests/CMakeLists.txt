add_executable( configurepluginswidgettest configurepluginswidgettest.cpp )
add_test(NAME configurepluginswidgettest COMMAND configurepluginswidgettest )
ecm_mark_as_test(kmail-configurepluginswidgettest)
target_link_libraries( configurepluginswidgettest Qt::Test KF5::I18n Qt::Widgets
    KF5::ConfigCore KF5::TextWidgets KF5::WidgetsAddons KF5::PimCommon)


add_executable( configurepluginslistwidgettest configurepluginslistwidgettest.cpp)
add_test(NAME configurepluginslistwidgettest COMMAND configurepluginslistwidgettest )
ecm_mark_as_test(kmail-configurepluginslistwidgettest)
target_link_libraries( configurepluginslistwidgettest Qt::Test KF5::I18n Qt::Widgets
    KF5::ConfigCore KF5::TextWidgets KF5::WidgetsAddons KF5::PimCommon KF5::ItemViews)
