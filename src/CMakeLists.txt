# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_definitions(-DTRANSLATION_DOMAIN=\"libpimcommon6\")

add_subdirectory(pimcommon)
add_subdirectory(pimcommonakonadi)
if(TARGET Plasma::Activities)
    add_subdirectory(pimcommon-activities)
endif()
