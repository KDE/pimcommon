#! /bin/sh
# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

$XGETTEXT `find . -name '*.h' -o -name '*.cpp' | grep -v '/tests/' | grep -v '/autotests/'` -o $podir/libpimcommon6.pot
