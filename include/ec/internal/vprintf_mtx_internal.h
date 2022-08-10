/* <vprintf_mtx_internal.h> -*- C -*- */
/**
 ** @copyright
 ** This file is part of the "eclibc" project.
 ** Copyright (C) 2022 ExoticCandy
 ** @email  ExoticCandyC.dev@gmail.com
 **
 ** Project's home page:
 ** https://github.com/ExoticCandyC/eclibc
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <stdarg.h>
#include <stdio.h>

#ifndef ECLIBC_INTERNAL_VPRINTF_MTX_INTERNAL_H
#define ECLIBC_INTERNAL_VPRINTF_MTX_INTERNAL_H 1

#ifdef __cplusplus
extern "C"
{
#endif

/* Since different compilers and different platforms implement NULL in a
 * different manner, EC_NULL is a helping macro to unify the NULL pointer over
 * all platforms.
 * E.g. some platforms have __builtin_null (like XC16) and some define it the
 *      same exact way.
 */
#ifndef EC_NULL
#define EC_NULL ((void *)0)
#endif

/* All CPP compilers on the other hand, use the same exact NULL pointer on all
 * platforms. So, there is no need to change the course of standard C++ library.
 */
#ifdef __cplusplus
#undef EC_NULL
#define EC_NULL NULL
#endif

__attribute__((hot,noinline))
void
ec_vfprintf_mtx(FILE *__restrict __stream,
                            const char *__restrict __format, va_list __arg);

__attribute__((hot,noinline))
void
ec_fprintf_mtx(FILE *__restrict __stream, const char *__restrict __format, ...);

__attribute__((hot,noinline))
void
ec_vprintf_mtx(const char *__restrict __format, va_list __arg);

__attribute__((hot,noinline))
void
ec_printf_mtx(const char *__restrict __format, ...);

void __ec_printf_mtx_init_mutex();
#ifndef ECLIBC_INTERNAL_COMPILE
__attribute__((constructor))
static void
__ec_printf_mtx_init_mutex_constructor()
{
    __ec_printf_mtx_init_mutex();
}
#endif

#ifdef __cplusplus
}
#endif

#endif
