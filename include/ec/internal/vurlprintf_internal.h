/* <vurlprintf_internal.h> -*- C -*- */
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

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ec/preprocessor.h>
#include <ec/internal/sprintf_fix_optimizer.h>

#ifndef ECLIBC_INTERNAL_URLSPRINTF_INTERNAL_H
#define ECLIBC_INTERNAL_URLSPRINTF_INTERNAL_H 1

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

#define __ec_urlprintf_impl(n, ...) __ec_urlprintf_func__ ## n(__VA_ARGS__)
#define __ec_urlprintf(n, ...) __ec_urlprintf_impl(n, __VA_ARGS__)
#define ec_urlprintf(...)                                                      \
      __ec_urlprintf(__EC_VA_NARGS__(__VA_ARGS__), __VA_ARGS__)

#define ec_vurlprintf(__s, __format, __arg)                                    \
      __ec_vurlprintf(__s, __format, __arg)

#define __ec_urlprintf_func__2(__dst, __src)                                   \
            (int)strlen(strcpy(__dst, __src))


__attribute__((hot,noinline))
int
ec_vurlprintf(char *__restrict __dst, const char *__restrict __src,
                                                                 va_list __arg);

__attribute__((hot,noinline))
int
ec_urlprintf(char *__restrict __dst, const char *__restrict __src, ...);

#ifdef __cplusplus
}
#endif

#endif
