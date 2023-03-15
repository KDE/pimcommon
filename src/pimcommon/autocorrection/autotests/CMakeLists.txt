# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
macro(add_pimcommon_autocorrect_unittest _source)
  set(_test ${_source})
  get_filename_component(_name ${_source} NAME_WE)
  add_executable( ${_name} ${_test} ${_name}.h)
  add_test(NAME ${_name} COMMAND ${_name} )
  ecm_mark_as_test(pimcommon-autocorrection-${_name})
  target_link_libraries(${_name}  Qt::Test KPim${KF_MAJOR_VERSION}::PimCommon KF${KF_MAJOR_VERSION}::TextAutoCorrection)
endmacro()

add_pimcommon_autocorrect_unittest(lineeditwithautocorrectiontest.cpp)
