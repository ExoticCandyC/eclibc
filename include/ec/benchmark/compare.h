/* <compare.h> -*- C -*- */
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

#include <ec/io.h>
#include <ec/preprocessor.h>
#include <stdlib.h>

#ifndef ECLIBC_BENCHMARK_COMPARE_H
#define ECLIBC_BENCHMARK_COMPARE_H 1

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

/* This module is designed ONLY for PC targets */
#if (defined(__linux__) || defined(_WIN32))


/**
 * @def ec_performance_compare(__iterations, __multiplyer, ...)
 *
 * @brief       This function accepts a variable number of functions and runs
 *              them multiple times and gives out detailed statistics about the
 *              performance of each function.
 *              Please note that the functions should NOT take any arguments
 *              and should return no values as well. So, you should make
 *              wrapper functions for the functions that dont meet this
 *              criteria and then pass the wrapper functions to this function.
 *
 * @warning     If the user doesn't provide at least one function to this macro,
 *              it will cause a compile time error.
 *
 * @param [in]__iterations      Number of times each function is executed.
 * @param [in]__multiplyer      Number of times each function is being executed
 *                              by the wrapper.
 */
#define ec_performance_compare(__iterations, __multiplyer, ...)                \
      __ec_performance_compare(__iterations, __multiplyer,                     \
                     (__EC_VA_NARGS__(__VA_ARGS__)), #__VA_ARGS__, __VA_ARGS__)

__attribute__((noinline))
void
__ec_performance_compare
    (const uint64_t __iterations, const uint64_t __multiplyer,
     const uint32_t __nargs, const char * __restrict __arg_names, ...);


#endif

#ifdef __cplusplus
}
#endif

#endif
