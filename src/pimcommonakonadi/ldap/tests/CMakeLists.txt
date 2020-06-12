########### next target ###############
set(testldapsearchdialog_SRCS ldapsearchdialog_gui.cpp)

add_executable(ldapsearchdialog_gui ${testldapsearchdialog_SRCS})
target_link_libraries(ldapsearchdialog_gui KF5::PimCommonAkonadi KF5::I18n KF5::CoreAddons Qt5::Widgets KF5::Contacts)

