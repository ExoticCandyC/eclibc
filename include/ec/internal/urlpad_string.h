/* <urlpad_string.h> -*- C -*- */
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

#ifndef ECLIBC_INTERNAL_URLPAD_STRING_H
#define ECLIBC_INTERNAL_URLPAD_STRING_H 1


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
url_encode_chr(char source, char *destination)
{
    uint8_t ptr = (uint8_t)source;
    const char *temp = "0123456789ABCDEF";
    destination = destination + strlen(destination);
    if((ptr >= 'a' && ptr <= 'z') ||
       (ptr >= 'A' && ptr <= 'Z') ||
       (ptr >= '0' && ptr <= '9'))
    {
        *destination++ = (char)ptr;
    }
    else
    {
        *destination++ = '%';
        *destination++ = temp[ptr / 0x10];
        *destination++ = temp[ptr % 0x10];
    }
    *destination = '\0';
}

static inline void
__attribute__ ((unused, always_inline))
url_encode(const char *__restrict source, char *destination)
{
    const uint8_t *ptr = (const uint8_t *)source;
    const char *temp = "0123456789ABCDEF";
    destination = destination + strlen(destination);
    while(*ptr != '\0')
    {
        if((*ptr >= 'a' && *ptr <= 'z') ||
           (*ptr >= 'A' && *ptr <= 'Z') ||
           (*ptr >= '0' && *ptr <= '9'))
        {
            *destination++ = (char)*ptr++;
        }
        else
        {
            *destination++ = '%';
            *destination++ = temp[*ptr   / 0x10];
            *destination++ = temp[*ptr++ % 0x10];
        }
    }
    *destination = '\0';
}

#define ec_urlfpad_string(__s, str)   url_encode(str, __s)
#define ec_urlpad_len_str(__s, str)   url_encode(str, __s)
#define ec_urlpad_character(__s, chr) url_encode_chr(chr, __s)

#if !(defined(XC16) || defined(XC32))
#pragma GCC diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif
