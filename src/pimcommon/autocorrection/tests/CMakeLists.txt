# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(autocorrection_gui autocorrection_gui.cpp)
target_link_libraries(autocorrection_gui
  KF5::PimCommon
  KF5::I18n
)

if (USE_KTEXTADDONS_LIB)
    target_link_libraries(autocorrection_gui
        KF5::TextAutoCorrection
    )
else()
    target_link_libraries(autocorrection_gui
        KF5::PimCommonAutoCorrection
    )
endif()
