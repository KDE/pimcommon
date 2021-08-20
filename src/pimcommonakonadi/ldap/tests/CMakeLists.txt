########### next target ###############
add_executable(ldapsearchdialog_gui ldapsearchdialog_gui.cpp)
target_link_libraries(ldapsearchdialog_gui KF5::PimCommonAkonadi KF5::I18n KF5::CoreAddons Qt::Widgets KF5::Contacts)

