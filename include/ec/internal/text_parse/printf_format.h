/* <printf_format.h> -*- C -*- */
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

#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef ECLIBC_INTERNAL_PRINTF_FORMAT_H
#define ECLIBC_INTERNAL_PRINTF_FORMAT_H 1

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

typedef struct
{
    int      NumberLeft;
    int      NumberRight;
    char     format_chr;
    uint8_t  NumSeen          :  2; /* 1 : Left     2: Right*/
    uint8_t  Star             :  2; /* 1 : Left     2: Right*/
    uint8_t  NumNegative      :  2; /* 1 : Left     2: Right*/
    uint8_t  show_sign        :  2; /* 1 : Left     2: Right*/
    uint8_t  side             :  1; /* 0 : Left     1: Right*/
    uint8_t  alternateForm    :  1;
    uint8_t  is_ec_format     :  1;
    uint8_t  Size             :  2; /* 0 : half      - 8 bit
                                     * 1 : normal    - 16 bit
                                     * 2 : long      - 32 bit
                                     * 3 : long long - 64 bit
                                     */
} __ec_printf_args;

static inline const char *
__attribute__ ((hot,unused,always_inline))
__ec_printf_extract_format (const char *__restrict start,
                     __ec_printf_args  *__restrict args, va_list __arg)
{
    memset(args, 0, sizeof(__ec_printf_args));
    args->side = 0;
    start++;
    switch(*start)
    {
        case '%':
        {
            args->format_chr = '%';
            return ++start;
        }
        case '!':
        {
            args->is_ec_format = 1;
            start++;
            if(*start == '^')
            {
                args->alternateForm = 1;
                start++;
            }
        }
    }
    __ec_printf_extract_jump_label:
    #define ____ec_signs_temp_switch()                                         \
    switch(*start)                                                             \
    {                                                                          \
        case '+':                                                              \
            args->show_sign = (unsigned)(args->show_sign |                     \
                                                       (1 << args->side)) & 3; \
            start++;                                                           \
            break;                                                             \
        case '-':                                                              \
            args->NumNegative = (unsigned)(args->NumNegative |                 \
                                                       (1 << args->side)) & 3; \
            start++;                                                           \
            break;                                                             \
        case '*':                                                              \
            args->Star = (unsigned)(args->Star |                               \
                                                       (1 << args->side)) & 3; \
            start++;                                                           \
            break;                                                             \
    }
    ____ec_signs_temp_switch();
    ____ec_signs_temp_switch();
    #undef ____ec_signs_temp_switch
    if(args->side == 0)
        args->NumberLeft = atoi(start) * ((args->NumNegative & 1) ? -1 : 1);
    else
        args->NumberRight = atoi(start) * ((args->NumNegative & 2) ? -1 : 1);
    if(isdigit((unsigned char)(*start)))
        args->NumSeen = (unsigned)(args->NumSeen | (1 << args->side)) & 3;
    start += strspn(start, "0123456789");
    if(args->side == 0 && *start == '.')
    {
        args->side = 1;
        start++;
        goto __ec_printf_extract_jump_label;
    }
    switch(*start)
    {
        case 'L':
        case 'q':
        {
            args->Size = 3;
            start++;
            break;
        }
        case 'h':
        {
            args->Size = 0;
            start++;
            break;
        }
        case 'l':
        {
            args->Size = 2;
            start++;
            if(*start == 'l')
            {
                args->Size = 3;
                start++;
            }
            break;
        }
        default:
        {
            args->Size = 1;
            break;
        }
    }
    if(args->Star & 1)
        args->NumberLeft = va_arg(__arg, int);
    if(args->Star & 2)
        args->NumberLeft = va_arg(__arg, int);
    args->format_chr = *start++;
    return start;
}

#ifdef __cplusplus
}
#endif

#endif
