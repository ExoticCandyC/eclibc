/* <compare.h> -*- C -*- */
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

#if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||           \
       defined(__TI_COMPILER_VERSION__)) && defined(__STRICT_ANSI__) &&       \
       (defined(_WIN32) || defined(__linux__))
#pragma GCC diagnostic ignored "-Wlong-long"
#endif

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
 * @brief ec_performance_compare    This function takes two functions, and runs
 *                                  them multiple times. After the iterations
 *                                  are done, it will compare the results of
 *                                  both functions and gives the user a full
 *                                  statistics on the performance of each
 *                                  function, and their performance relative to
 *                                  each other.
 *                                  Please note that the functions should NOT
 *                                  take any arguments and should return no
 *                                  values as well. So, you should make wrapper
 *                                  functions for the functions that dont meet
 *                                  this criteria and then pass the wrapper
 *                                  functions to this function.
 * @param [in]function1             The first function to be used during the
 *                                  test.
 * @param [in]function2             The second function to be used during the
 *                                  test.
 * @param [in]iteration             Number of times each function is executed.
 * @param [in]innerItterations      Number of times each function is being
 *                                  executed by the wrapper. The default value
 *                                  is 0.
 */
void ec_performance_compare(void (*function1)(void),
                            void (*function2)(void),
                            long long int iteration,
                            long long int innerItterations);

#endif

#ifdef __cplusplus
}
#endif

#endif
