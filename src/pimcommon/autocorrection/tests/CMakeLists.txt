# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_executable(autocorrection_gui autocorrection_gui.cpp)
target_link_libraries(autocorrection_gui
  KF5::KIOCore
  KF5::PimCommonAutoCorrection
  KF5::PimCommon
  KF5::I18n
)

