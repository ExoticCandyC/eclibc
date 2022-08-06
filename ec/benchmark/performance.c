/* <performance.c> -*- C -*- */
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

/*
 * Including this header will enable the performance test. Uncomment this
 * include directive to enable performance test on ALL your programs using this
 * library.
 */

#if (defined(__linux__) || defined(_WIN32))

#define ________DO_NOT_ENABLE_PERFORMANCE_TEST________
#include <ec/benchmark/performance.h>
#undef  ________DO_NOT_ENABLE_PERFORMANCE_TEST________

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

#ifdef __cplusplus
extern "C"
{
#endif

struct timeval __ec_api_performance_test_start;
time_t __ec_api_performance_test_start_time;

void ____ec_api_performance_constructor()
{
    time(&__ec_api_performance_test_start_time);
    gettimeofday(&__ec_api_performance_test_start, EC_NULL);
}

void ____ec_api_performance_destructor()
{
    int index;
    time_t duration;
    double accuracy;
    double fracture;
    struct timeval __ec_api_performance_test_end;
    time_t now;
    gettimeofday(&__ec_api_performance_test_end, EC_NULL);
    time(&now);
    duration = (__ec_api_performance_test_end.tv_sec -
                    __ec_api_performance_test_start.tv_sec) * 1000000 +
                __ec_api_performance_test_end.tv_usec -
                    __ec_api_performance_test_start.tv_usec;
    fracture = (double)150000 / (double)(duration - 100000);
    if(duration <= 100000 || fracture > 1)
        accuracy = 0;
    else
        accuracy = ((double)1 - fracture) * 100;
    for(index = 0; index < 3; index++)
        printf("\r\n");
    printf("eclibc: ec/benchmark/performance.h:\n\n\r");
    printf("          Program finished running.     \r\n");
    #ifdef __linux__
    printf("    Press any key to see the statistics.\r\n");
    system("read -r -n 1 -s");
    #endif
    for(index = 0; index < 5; index++)
        printf("\r\n");
    if(accuracy < 0.01)
        printf("Warning!! Extremely inacurate data are being presented here."
               "\r\nAccuracy of the calculated time difference is less than "
               "0.01%%\r\n");
    else if(accuracy < 30)
        printf("Warning!! The calculated data is not to be trusted in only a "
               "few iterations, run at least 1000 iterations to get a more "
               "accurate result.\r\n"
               "Accuracy of the calculated time difference: %.2f%%\r\n",
               accuracy);
    else
        printf("Accuracy of the calculated time difference: %.2f%%\r\n",
               accuracy);
    printf("\r\n");
    printf("Execution started at:\r\n\t\t%s\r\n",
                                ctime(&__ec_api_performance_test_start_time));
    printf("Execution finished at:\r\n\t\t%s\r\n",
                                ctime(&now));
    printf("Execution of the program took:\r\n\t\t%lu[us]\r\n\n\n",
                                                   (long unsigned int)duration);
    #ifdef __linux__
    printf("Press any key to exit.\r\n");
    system("read -r -n 1 -s");
    #endif
}

#ifdef __cplusplus
}
#endif

#else
typedef int DUMMY_TYPEDEF_TO_AVOID_ANSI_WARNING_RISING;
#endif
