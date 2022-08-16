/* <vprintf_internal.h> -*- C -*- */
/**
 ** @copyright
 ** This file is part of the "eclibc" project.
 ** Copyright (C) 2022 ExoticCandy
 ** @email  admin@ecandy.ir
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

#include <ec/preprocessor.h>
#include <ec/internal/printf_fix_optimizer.h>

#ifndef ECLIBC_INTERNAL_VPRINTF_INTERNAL_H
#define ECLIBC_INTERNAL_VPRINTF_INTERNAL_H 1

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

#define __ec_printf_impl(n, ...) __ec_printf_func__ ## n(__VA_ARGS__)
#define __ec_printf(n, ...) __ec_printf_impl(n, __VA_ARGS__)
#define ec_printf(...) __ec_printf(__EC_VA_NARGS__(__VA_ARGS__), __VA_ARGS__)

#define __ec_fprintf_impl(n, ...) __ec_fprintf_func__ ## n(__VA_ARGS__)
#define __ec_fprintf(n, ...) __ec_fprintf_impl(n, __VA_ARGS__)
#define ec_fprintf(...) __ec_fprintf(__EC_VA_NARGS__(__VA_ARGS__), __VA_ARGS__)

#define ec_vfprintf(__stream, __format, __arg)                                 \
      __ec_vfprintf(__stream, __format, __arg)

#define ec_vprintf(__format, __arg)                                            \
      __ec_vprintf(__format, __arg)

__attribute__((hot,noinline))
void
ec_vfprintf(FILE *__restrict __stream,
                            const char *__restrict __format, va_list __arg);

/*
__attribute__((hot,noinline))
void
ec_fprintf(FILE *__restrict __stream, const char *__restrict __format);
*/

#define __ec_fprintf_func__2(__stream, __format)       fputs(__format, __stream)

__attribute__((hot,noinline))
void
ec_fprintf(FILE *__restrict __stream, const char *__restrict __format, ...);

__attribute__((hot,noinline))
void
ec_vprintf(const char *__restrict __format, va_list __arg);

/*
__attribute__((hot,noinline))
void
ec_printf(const char *__restrict __format);
*/

#define __ec_printf_func__1(__format)                    fputs(__format, stdout)

__attribute__((hot,noinline))
void
ec_printf(const char *__restrict __format, ...);

#ifdef __cplusplus
}
#endif

#endif
