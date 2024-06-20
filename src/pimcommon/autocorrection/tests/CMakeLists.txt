# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(autocorrection_gui autocorrection_gui.cpp autocorrection_gui.h)
target_link_libraries(autocorrection_gui
  KPim6::PimCommon
  KF6::I18n
)

if(TARGET KF6::TextAutoCorrectionWidgets)
    target_link_libraries(autocorrection_gui
        KF6::TextAutoCorrectionWidgets
)
else()
  target_link_libraries(autocorrection_gui
      KF6::TextAutoCorrection
)
endif()
