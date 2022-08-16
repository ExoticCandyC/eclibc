/* <pad_string.h> -*- C -*- */
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
#include <ec/io.h>
#include <ec/arch.h>

#ifndef ECLIBC_INTERNAL_SPAD_STRING_H
#define ECLIBC_INTERNAL_SPAD_STRING_H 1


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

#if !(defined(XC16) || defined(XC32))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <stdint.h>
static inline void
__attribute__ ((unused, always_inline))
ec_sfpad_string(char *__restrict __s, int padSize, char padChar,
                char *__restrict start, char *__restrict end)
{
    int rpad = padSize - (int)(start - end);
    char *__restrict lpad = end - padSize;
    while(lpad++ < start)
        strncat(__s, &padChar, 1);
    strncat(__s, start, (size_t)(end - start));
    while(rpad++ < 0)
        strncat(__s, &padChar, 1);
}

static inline void
__attribute__ ((unused, always_inline))
ec_spad_len_str(char *__restrict __s, int padSize, char padChar,
                const char * __restrict str, size_t len)
{
    char *__restrict __start;
    if(padSize > (int)len)
    {
        __start = __s + strlen(__s);
        memset(__start, padChar, (size_t)(padSize - (int)len));
        __start[(padSize - (int)len)] = '\0';
    }
    strcat(__s, str);
    while(padSize++ < (int)((((int)len) * -1) - 1))
        strncat(__s, &padChar, 1);
}

static inline void
__attribute__ ((unused, always_inline))
ec_spad_character(char *__restrict __s, int padSize, char padChar,
                                                                char character)
{
    char *__restrict __start = __s + strlen(__s);
    if(padSize > 1)
    {
        memset(__start, padChar, (size_t)(padSize - 1));
        __start[(padSize - 1)] = '\0';
    }
    strncat(__s, &character, 1);
    __start++;
    if(padSize < -2)
    {
        memset(__start, padChar, (size_t)((padSize + 2) * -1));
        __start[((padSize + 2) * -1)] = '\0';
    }
}

#if !(defined(XC16) || defined(XC32))
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif
