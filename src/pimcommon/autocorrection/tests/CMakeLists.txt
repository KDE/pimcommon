# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(autocorrection_gui autocorrection_gui.cpp autocorrection_gui.h)
target_link_libraries(autocorrection_gui
  KPim${KF_MAJOR_VERSION}::PimCommon
  KF${KF_MAJOR_VERSION}::I18n
)

if (TARGET KF${KF_MAJOR_VERSION}::TextAutoCorrectionWidgets)
    target_link_libraries(autocorrection_gui
        KF${KF_MAJOR_VERSION}::TextAutoCorrectionWidgets
    )
else()
  target_link_libraries(autocorrection_gui
      KF${KF_MAJOR_VERSION}::TextAutoCorrection
  )
endif()
