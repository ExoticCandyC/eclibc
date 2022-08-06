/* <compare.c> -*- C -*- */
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

#if (defined(__linux__) || defined(_WIN32))

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ec/benchmark/compare.h>
#include <ec/io.h>
#include <ec/printf.h>

#ifdef __cplusplus
extern "C"
{
#endif


/* This module is designed ONLY for PC targets */

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
                            long long int innerItterations)
{
    long long int index;

    struct timeval function1_start;
    time_t         function1_start_time;
    struct timeval function2_start;
    time_t         function2_start_time;
    struct timeval function1_end;
    time_t         function1_end_time;
    struct timeval function2_end;
    time_t         function2_end_time;

    time_t         function1_elapsed;
    time_t         function2_elapsed;

    double         relative_1_2;
    double         relative_2_1;

    #ifdef __linux__
    int            terminalColumns = ec_io_get_terminal_columns_count();
    #else
    int            terminalColumns = 80;
    #endif
    int            progressBarWidth = (int)(terminalColumns -
                       (int)sizeof("Function 1 iteration progress: [] 100.0%"));
    char           *progressBar;

    if(progressBarWidth < 0)
        progressBarWidth = 0;
    progressBar = malloc((size_t)(progressBarWidth + 1));

    printf("\r\neclibc: ec/benchmark/compare.h:\n\n\r");

    if(iteration < 1000)
    {
        iteration = 1000;
        printf("Minimum number of iterations is 1000. Changing iterations "
               "count to 1000.\n\n\n\r");
    }

    printf("\tStarting the function comparison algorithm:\n\n\n\r");

    time(&function1_start_time);
    gettimeofday(&function1_start, EC_NULL);
    for(index = 0; index < iteration; index++)
    {
        if(index % (iteration / 1000) == 0)
        {
            double progress = ((double)index /
                               ((double)iteration / (double)100));
            ec_generate_progress_bar(progressBar, progress,
                                        progressBarWidth, "-", "#");
            ec_io_printf_instant("\rFunction 1 iteration progress: "
                                    "[%s] %5.1f%%", progressBar, progress);
        }
        function1();
    }
    gettimeofday(&function1_end, EC_NULL);
    time(&function1_end_time);
    ec_generate_progress_bar(progressBar, 100, progressBarWidth, "-", "#");
    ec_io_printf_instant("\rFunction 1 iteration progress: "
                                "[%s] 100.0%%", progressBar);
    printf("\r\nFunction 1 finished iterating.\r\n\n");

    time(&function2_start_time);
    gettimeofday(&function2_start, EC_NULL);
    for(index = 0; index < iteration; index++)
    {
        if(index % (iteration / 1000) == 0)
        {
            double progress = ((double)index /
                               ((double)iteration / (double)100));
            ec_generate_progress_bar(progressBar, progress,
                                        progressBarWidth, "-", "#");
            ec_io_printf_instant("\rFunction 2 iteration progress: "
                                    "[%s] %5.1f%%", progressBar, progress);
        }
        function2();
    }
    gettimeofday(&function2_end, EC_NULL);
    time(&function2_end_time);
    ec_generate_progress_bar(progressBar, 100, progressBarWidth, "-", "#");
    ec_io_printf_instant("\rFunction 2 iteration progress: "
                                "[%s] 100.0%%", progressBar);
    printf("\r\nFunction 2 finished iterating.\r\n\n");

    free(progressBar);

    function1_elapsed = (function1_end.tv_sec -
                             function1_start.tv_sec) * 1000000 +
                         function1_end.tv_usec -
                             function1_start.tv_usec;

    function2_elapsed = (function2_end.tv_sec -
                             function2_start.tv_sec) * 1000000 +
                         function2_end.tv_usec -
                             function2_start.tv_usec;

    printf("\r\neclibc: ec/benchmark/compare.h:\n\n\r");
    printf("Comparison test results:\r\n");

    #if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||        \
           defined(__TI_COMPILER_VERSION__)) && defined(__STRICT_ANSI__) &&    \
           (defined(_WIN32) || defined(__linux__))
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wformat"
    #endif
    printf("\tIterations: %lld\n\r", (iteration * innerItterations));
    #if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||        \
           defined(__TI_COMPILER_VERSION__)) && defined(__STRICT_ANSI__) &&    \
           (defined(_WIN32) || defined(__linux__))
    #pragma GCC diagnostic pop
    #endif

    printf("\r\n\tFunction 1:\r\n");
    printf("\t\tStart:\t%s\r" , ctime(&function1_start_time));
    printf("\t\tFinish:\t%s\r", ctime(&function1_end_time));
    printf("\t\tElapsed time: %lu[us]\r\n",
                                          (long unsigned int)function1_elapsed);

    printf("\r\n\tFunction 2:\r\n");
    printf("\t\tStart:\t%s\r" , ctime(&function2_start_time));
    printf("\t\tFinish:\t%s\r", ctime(&function2_end_time));
    printf("\t\tElapsed time: %lu[us]\r\n",
                                          (long unsigned int)function2_elapsed);
    printf("\r\n");

    relative_1_2 =
            ((((double)(function1_elapsed)) / ((double)(function2_elapsed))) *
             ((double)100));
    relative_2_1 =
            ((((double)(function2_elapsed)) / ((double)(function1_elapsed))) *
             ((double)100));


    printf("\tFunction %u is %.10f%% faster than Function %u.\r\n\n\n",
                          ((relative_1_2 < 100) ? 1 : 2),
                          ((relative_1_2 < 100) ? relative_2_1 : relative_1_2),
                          ((relative_1_2 < 100) ? 2 : 1));

    #ifdef __linux__
    printf("Press any key to continue.\r\n");
    system("read -r -n 1 -s");
    #endif
}



#ifdef __cplusplus
}
#endif

#else
typedef int DUMMY_TYPEDEF_TO_AVOID_ANSI_WARNING_RISING;
#endif
