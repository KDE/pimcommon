/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef PIMCOMMON_TESTS_EXPORT
#define PIMCOMMON_TESTS_EXPORT PIMCOMMON_EXPORT
#endif
#else /* not compiling tests */
#define PIMCOMMON_TESTS_EXPORT
#endif
