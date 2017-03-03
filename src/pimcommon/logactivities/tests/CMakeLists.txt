set(logactivities_gui_SRCS main.cpp logactivitiesmainwidget.cpp)
add_executable(logactivities_gui ${logactivities_gui_SRCS})
target_link_libraries(logactivities_gui
  KF5::PimCommon
  KF5::I18n
)

