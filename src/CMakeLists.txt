# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_definitions(-DTRANSLATION_DOMAIN=\"libpimcommon6\")

add_subdirectory(pimcommon)
add_subdirectory(pimcommonakonadi)
if(OPTION_USE_PLASMA_ACTIVITIES)
   add_subdirectory(pimcommon-activities)
endif()
