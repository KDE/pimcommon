# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_definitions(-DTRANSLATION_DOMAIN=\"libpimcommon\")

add_subdirectory(pimcommon)
if (TARGET KF5::AkonadiCore)
    add_subdirectory(pimcommonakonadi)
endif()
