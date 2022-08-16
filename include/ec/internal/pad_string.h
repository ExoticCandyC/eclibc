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

#include <stdio.h>
#include <ec/io.h>
#include <ec/arch.h>

#ifndef ECLIBC_INTERNAL_PAD_STRING_H
#define ECLIBC_INTERNAL_PAD_STRING_H 1


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

static inline void
__attribute__ ((unused, always_inline))
ec_fpad_string(FILE * stream, int padSize, char padChar,
                char *__restrict start, char *__restrict end)
{
    int rpad = padSize - (int)(start - end);
    char *__restrict lpad = end - padSize;
#if !(defined(XC16) || defined(XC32))
    while(lpad++ < start)
        ec_fputc(padChar, stream);
    /*while(start < end)
        ec_fputc(*start++, stream);*/
    ec_fwrite_str(start, end, stream);
    while(rpad++ < 0)
        ec_fputc(padChar, stream);
#else
    while(lpad++ < start)
        ec_fputc((unsigned char)padChar, stream);
    /*while(start < end)
        ec_fputc((unsigned char)*start++, stream);*/
    ec_fputs(start, stream);
    while(rpad++ < 0)
        ec_fputc((unsigned char)padChar, stream);
#endif
}

static inline void
__attribute__ ((unused, always_inline))
ec_fpad_len_str(FILE * stream, int padSize, char padChar,
                const char * __restrict str, size_t len)
{
#if !(defined(XC16) || defined(XC32))
    while(padSize-- > (int)len)
        ec_fputc(padChar, stream);
    ec_fputs(str, stream);
    while(padSize++ < (int)((((int)len) * -1) - 1))
        ec_fputc(padChar, stream);
#else
    while(padSize-- > (int)len)
        ec_fputc((unsigned char)padChar, stream);
    ec_fputs(str, stream);
    while(padSize++ < (int)((((int)len) * -1) - 1))
        ec_fputc((unsigned char)padChar, stream);
#endif
}

static inline void
__attribute__ ((unused, always_inline))
ec_fpad_character(FILE * stream, int padSize, char padChar, char character)
{
#if !(defined(XC16) || defined(XC32))
    while(padSize-- > 1)
        ec_fputc(padChar, stream);
    ec_fputc(character, stream);
    while(padSize++ < -2)
        ec_fputc(padChar, stream);
#else
    while(padSize-- > 1)
        ec_fputc((unsigned char)padChar, stream);
    ec_fputc((unsigned char)character, stream);
    while(padSize++ < -1)
        ec_fputc((unsigned char)padChar, stream);
#endif
}

#if !(defined(XC16) || defined(XC32))
#pragma GCC diagnostic pop
#endif

static inline char *
__attribute__ ((unused, always_inline))
ec_pad_num_string(int padSize, char *__restrict start, char *__restrict end)
{
    char *__restrict lpad = end - padSize;
    if(padSize <= 0)
        return start;
    while(lpad < start)
        *--start = '0';
    return lpad;
}

#ifdef __cplusplus
}
#endif

#endif
