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


#if !(defined(XC16) || defined(XC32))
#pragma GCC diagnostic ignored "-Wunused-macros"
#endif

#define _DEFAULT_SOURCE
#include <ec/string.h>
#include <ec/time.h>
#include <sys/time.h>
#include <ec/ansi.h>
#include <unistd.h>
#include <ec/benchmark/compare.h>

#define __ec_compare_function_name_max_len 20

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    time_t   start_time;
    time_t   end_time;
    uint64_t elapsed;
} __ec_function_performance_data;

typedef void (*__ec_function_compare_t)(void);

__attribute__ ((visibility("hidden"),noinline))
void
__ec_print_nth_name
    (const uint32_t __nargs, const char * __restrict __arg_names, uint32_t argn)
{
    const char * __restrict Name_Tail = __arg_names;
    const char * __restrict Name_Head;
    if(argn < __nargs)
    {
        do
        {
            Name_Head = strchr(Name_Tail, ',');
            if(argn == 0)
            {
                if(Name_Head == EC_NULL)
                    ec_fputs(Name_Tail, stdout);
                else
                    ec_fwrite_str(Name_Tail, Name_Head - 1, stdout);
                return;
            }
            Name_Tail = Name_Head + 2;
        } while(argn-- > 0);
    }
}

__attribute__ ((visibility("hidden"),noinline))
void
__ec_benchmark_progress_bar
    (int progressBarWidth, char *progressBar, double progress)
{

    ec_generate_progress_bar(progressBar, progress,
                                progressBarWidth, "-", "#");
    ec_io_printf_instant(cursor_home() cursor_move_right_variable()
              " > Iteration Progress: [%s] %5.1f%%",
              __ec_compare_function_name_max_len, progressBar, progress);
}

__attribute__ ((visibility("hidden"),noinline))
void
__ec_benchmark_itterate_function
    (const uint64_t __iterations, __ec_function_compare_t __func,
     __ec_function_performance_data * __restrict __data, int progressBarWidth,
     char *progressBar)
{
    struct timeval timer_start;
    struct timeval timer_end;
    uint64_t       index;

    time(&(__data->start_time));
    gettimeofday(&timer_start, EC_NULL);
    for(index = 0; index < __iterations; index++)
    {
        if(index % (__iterations / 1000) == 0)
        {
            double progress = ((double)index /
                               ((double)__iterations / (double)100));
            __ec_benchmark_progress_bar
                    (progressBarWidth, progressBar, progress);
        }
        __func();
    }
    gettimeofday(&timer_end, EC_NULL);
    time(&(__data->end_time));

    __data->elapsed = (uint64_t)
                       ((timer_end.tv_sec -
                             timer_start.tv_sec) * 1000000 +
                         timer_end.tv_usec -
                             timer_start.tv_usec);
}

__attribute__((noinline))
void
__ec_performance_compare
    (uint64_t __iterations, const uint64_t __multiplyer,
     const uint32_t __nargs, const char * __restrict __arg_names, ...)
{
    __ec_function_compare_t          __func;
    __ec_function_performance_data * __restrict performance_data;
    va_list         argptr;
    int             terminalColumns;
    int             progressBarWidth;
    char           *progressBar;
    uint32_t        index;
    uint32_t        min_elapsed_index = 0;
    uint64_t        min_elapsed_value = 0xFFFFFFFFFFFFFFFF;
    ec_printf("\r\neclibc: ec/benchmark/compare.h:\r\n");
    if(__nargs == 1)
    {
        ec_printf("Atleast two functions are needed for benchmark "
                                                              "comparing.\r\n");
        return;
    }

    if(__iterations < 1000)
    {
        __iterations = 1000;
        ec_printf("Minimum number of iterations is 1000. Changing iterations "
                                                      "count to 1000.\r\n");
    }

    ec_printf("\r\nStarting the function comparison algorithm:\r\n");

    ec_io_printf_instant(cursor_invisible());

    #ifdef __linux__
    terminal_echo_off();
    #endif

    #ifdef __linux__
    /* Making sure the terminal has been initiated and stablized */
    usleep(50000);
    terminalColumns = ec_io_get_terminal_columns_count() -
                      __ec_compare_function_name_max_len + 1;
    #else
    terminalColumns = 80 - __ec_compare_function_name_max_len;
    #endif

    progressBarWidth = (int)(terminalColumns -
                       (int)sizeof(" : Iteration Progress: [] 100.0%"));

    if(progressBarWidth < 0)
        progressBarWidth = 0;
    progressBar = malloc((size_t)(progressBarWidth + 20));
    performance_data = malloc(sizeof(__ec_function_performance_data) * __nargs);

    va_start(argptr, __arg_names);

    for(index = 0; index < __nargs; index++)
    {
        __ec_print_nth_name(__nargs, __arg_names, index);
        __func = va_arg(argptr, __ec_function_compare_t);
        __ec_benchmark_itterate_function(__iterations, __func,
                                         (performance_data + index),
                                         progressBarWidth, progressBar);

        ec_printf(cursor_home() color_text_green());
        __ec_print_nth_name(__nargs, __arg_names, index);
        __ec_benchmark_progress_bar(progressBarWidth, progressBar, 100.F);
        ec_printf(color_reset() end_line());
    }

    va_end(argptr);

    ec_printf("\r\neclibc: ec/benchmark/compare.h:\n\n\r");
    ec_printf("Comparison test results:\r\n");

    ec_printf("%4sIterations: %llu\n\r", "", (__iterations * __multiplyer));

    for(index = 0; index < __nargs; index++)
    {
        ec_printf("%8s\"", "");
        __ec_print_nth_name(__nargs, __arg_names, index);
        ec_printf("\" statistics:\r\n");
        ec_printf("%12s%-11s%s\r" , "", "Start:",
                        ctime(&(performance_data[index].start_time)));
        ec_printf("%12s%-11s%s\r", "", "Finish:",
                        ctime(&(performance_data[index].end_time)));
        ec_printf("%12s%-11s%llu[us]\r\n", "", "Elapsed:",
                                              performance_data[index].elapsed);
        if(performance_data[index].elapsed < min_elapsed_value)
        {
            min_elapsed_value = performance_data[index].elapsed;
            min_elapsed_index = index;
        }
    }

    ec_printf(end_line() "Benchmark graph:" end_line());
    ec_printf("%4sSpeed percentile - " color_text_green() "higher"
                                   color_reset() " is better:" end_line(), "");

    progressBarWidth = (int)(terminalColumns -
                       (int)sizeof("         > %100.00% []"));
    if(progressBarWidth < 0)
        progressBarWidth = 0;

    for(index = 0; index < __nargs; index++)
    {
        double percentile = (((double)performance_data[min_elapsed_index].elapsed) /
                             ((double)performance_data[index].elapsed)) * 100.F;

        if(percentile > 95.F)
            ec_printf(color_text_green());
        else if(percentile > 70.F)
            ec_printf(color_text_cyan());
        else if(percentile > 50.F)
            ec_printf(color_text_yellow());
        else
            ec_printf(color_text_red());

        ec_generate_progress_bar(progressBar, percentile,
                                    progressBarWidth, " ", "#");
        ec_printf("%8s", "");
        __ec_print_nth_name(__nargs, __arg_names, index);
        ec_printf(cursor_home() cursor_move_right_variable() " > %6.2f%% [%s]",
                    (8 + __ec_compare_function_name_max_len),
                    percentile, progressBar);
        ec_printf(color_reset() end_line());
    }


    free(progressBar);
    free(performance_data);

    #ifdef __linux__
    terminal_echo_on();
    #endif

    ec_io_printf_instant(cursor_visible());
}

#ifdef __cplusplus
}
#endif

#else
typedef int DUMMY_TYPEDEF_TO_AVOID_ANSI_WARNING_RISING;
#endif
