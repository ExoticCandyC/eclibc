/* <performance.h> -*- C -*- */
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

/**
 * @file    ec/benchmark/performance.h
 * @brief   This file includes the performance test module. To use this module
 *          all you have to do is including this header.
 *          When this file is included in a project, this module will
 *          automatically pick up the time when the program runs, and after
 *          the program ends, it will calculate how long the program took to
 *          run.
 *          An example output is like this:
 ******************************************************************************
 *  eclibc: ec/benchmark/performance.h:                                       *
 *                                                                            *
 *            Program finished running.                                       *
 *      Press any key to see the statistics.                                  *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 *  Accuracy of the calculated time difference: 91.54%                        *
 *                                                                            *
 *  Execution started at:                                                     *
 *  		Fri Aug  5 17:58:30 2022                                          *
 *                                                                            *
 *  Execution finished at:                                                    *
 *  		Fri Aug  5 17:58:32 2022                                          *
 *                                                                            *
 *  Execution of the program took:                                            *
 *  		1873855[us]                                                       *
 *                                                                            *
 *                                                                            *
 *  Press any key to exit.                                                    *
 ******************************************************************************
 */

#ifndef ECLIBC_BENCHMARK_PERFORMANCE_H
#define ECLIBC_BENCHMARK_PERFORMANCE_H 1

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

void ____ec_api_performance_constructor();
void ____ec_api_performance_destructor();

/* If the file was directly included inside a project */
#ifndef ________DO_NOT_ENABLE_PERFORMANCE_TEST________

/* Define the module's constructor and destructor as program constructor and
 * destructor. Weak attribute is used to avoid errors rising if the file  is
 * included inside a project, more than once.
 * Note: weak attribute is generally not needed, but it is better to be safe
 *       than sorry.
 */

__attribute__((weak,constructor)) void __ec_api_performance_constructor()
{
    ____ec_api_performance_constructor();
}

__attribute__((weak,destructor))  void __ec_api_performance_destructor()
{
    ____ec_api_performance_destructor();
}
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
