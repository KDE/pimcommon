# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_definitions(-DTRANSLATION_DOMAIN=\"libpimcommon\")

add_subdirectory(pimcommon)
add_subdirectory(pimcommonakonadi)
if (NOT USE_KTEXTADDONS_LIB)
    add_subdirectory(pimcommonautocorrection)
    add_subdirectory(pimcommontexttranslator)
    add_subdirectory(pimcommontextgrammarcheck)
endif()
