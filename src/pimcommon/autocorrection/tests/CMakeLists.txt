# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(autocorrection_gui autocorrection_gui.cpp autocorrection_gui.h)
target_link_libraries(autocorrection_gui
  KF5::PimCommon
  KF${KF_MAJOR_VERSION}::I18n
)

if (USE_KTEXTADDONS_LIB)
    target_link_libraries(autocorrection_gui
        KF${KF_MAJOR_VERSION}::TextAutoCorrection
    )
else()
    target_link_libraries(autocorrection_gui
        KF5::PimCommonAutoCorrection
    )
endif()
