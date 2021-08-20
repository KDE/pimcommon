add_executable(logactivities_gui main.cpp logactivitiesmainwidget.cpp)
target_link_libraries(logactivities_gui
  KF5::PimCommon
  KF5::I18n
)

