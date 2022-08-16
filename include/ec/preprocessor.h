/* <preprocessor.h> -*- C -*- */
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

#include <ec/macro/earg_helper.h>

#ifndef ECLIBC_PRE_PROCESSOR_H
#define ECLIBC_PRE_PROCESSOR_H 1

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

/**
 * @def __EC_VA_NARGS__(...)
 * @brief   Counts the number of variadic arguments passed to a variadic macro.
 *          The limit on this function is 110 right now, can be increased.
 * @return  The number of variadic arguments passed to a macro
 * @example
 *
 * #define sample_variadic_macro(...) __EC_VA_NARGS__(__VA_ARGS__)
 *
 * This macro returns the number of variadic arguments passed onto it.
 *
 */
#define __EC_VA_NARGS__(...) \
__EC_COMPILER_OPTIMIZER_COUNT(__VA_ARGS__,__EC_COMPILER_OPTIMIZER_RSEQ_N())



#ifdef __cplusplus
}
#endif

#endif
