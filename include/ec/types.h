/* <types.h> -*- C -*- */
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

#include <ec/arch.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef ECLIBC_TYPES_H
#define ECLIBC_TYPES_H 1

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

#ifndef DISABLED
#define DISABLED 0
#endif

#ifndef ENABLED
#define ENABLED 1
#endif

typedef enum
{
    log_none        = 0,
    log_error       = 1,
    log_warning     = 2,
    log_info        = 3,
    log_debug       = 4,
    log_internal    = 5,
    log_all         = 6,
    log_MAX         = 7
} log_level;

#if (EC_ARCH > 8)
typedef uint64_t ec_timetick_t; /**< time tick is a unit of a hundreadth seconds */
#endif
typedef uint32_t ec_time_seconds_t; /**< time of day, turned into seconds        */
typedef uint32_t ec_utf8_t;

#if (EC_ARCH > 8)
typedef uint64_t ec_phonenumber_t;
#else
typedef struct
{
    uint32_t part1;
    uint32_t part2;
} ec_phonenumber_t;
#endif

#define ec_make_IPv4(_IPobj, _byte1, _byte2, _byte3, _byte4)                   \
    {                                                                          \
        _IPobj.display_string.byte1 = _byte1;                                  \
        _IPobj.display_string.byte2 = _byte2;                                  \
        _IPobj.display_string.byte3 = _byte3;                                  \
        _IPobj.display_string.byte4 = _byte4;                                  \
    }

#define ec_make_IPv6(_IPobj, _byte1, _byte2, _byte3, _byte4,                   \
                             _byte5, _byte6, _byte7, _byte8)                   \
    {                                                                          \
        _IPobj.display_string.byte1 = _byte1;                                  \
        _IPobj.display_string.byte2 = _byte2;                                  \
        _IPobj.display_string.byte3 = _byte3;                                  \
        _IPobj.display_string.byte4 = _byte4;                                  \
        _IPobj.display_string.byte5 = _byte5;                                  \
        _IPobj.display_string.byte6 = _byte6;                                  \
        _IPobj.display_string.byte7 = _byte7;                                  \
        _IPobj.display_string.byte8 = _byte8;                                  \
    }

#define ec_make_MAC(_MACobj, _byte1, _byte2, _byte3, _byte4, _byte5, _byte6)   \
    {                                                                          \
        _MACobj.display_string.byte1 = _byte1;                                 \
        _MACobj.display_string.byte2 = _byte2;                                 \
        _MACobj.display_string.byte3 = _byte3;                                 \
        _MACobj.display_string.byte4 = _byte4;                                 \
        _MACobj.display_string.byte5 = _byte5;                                 \
        _MACobj.display_string.byte6 = _byte6;                                 \
    }

#define ec_make_cisco_MAC(_MACobj, _byte1, _byte2, _byte3)                     \
    {                                                                          \
        _MACobj.cisco_string.byte1 = _byte1;                                   \
        _MACobj.cisco_string.byte2 = _byte2;                                   \
        _MACobj.cisco_string.byte3 = _byte3;                                   \
    }

typedef union
{
    /* IPv4: 241.32.156.85 */
    struct
    {
        unsigned int byte4 : 8;
        unsigned int byte3 : 8;
        unsigned int byte2 : 8;
        unsigned int byte1 : 8;
    } display_string;
    uint32_t IP;
} ec_ipv4_t;

typedef union
{
    /* IPv6: 2001:0db8:85a3:0000:0000:8a2e:0370:7334 */
    struct
    {
        unsigned int byte8 : 16;
        unsigned int byte7 : 16;
        unsigned int byte6 : 16;
        unsigned int byte5 : 16;
        unsigned int byte4 : 16;
        unsigned int byte3 : 16;
        unsigned int byte2 : 16;
        unsigned int byte1 : 16;
    } display_string;
#   if (EC_ARCH > 8)
    struct
    {
        uint64_t part1;
        uint64_t part2;
    } _64bit;
#   endif
    struct
    {
        uint32_t part1;
        uint32_t part2;
        uint32_t part3;
        uint32_t part4;
    } _32bit;
} ec_ipv6_t;

typedef union
{
    struct
    {
        unsigned int byte6 : 8;
        unsigned int byte5 : 8;
        unsigned int byte4 : 8;
        unsigned int byte3 : 8;
        unsigned int byte2 : 8;
        unsigned int byte1 : 8;
        unsigned int       : 16;
    } display_string;
    struct
    {
        unsigned int byte3 : 16;
        unsigned int byte2 : 16;
        unsigned int byte1 : 16;
        unsigned int       : 16;
    } cisco_string;
#   if (EC_ARCH > 8)
    uint64_t MAC;
#   else
    struct
    {
        uint32_t part1;
        uint16_t part2;
        unsigned int : 16;
    } MAC;
#   endif
} ec_mac_t;

#ifdef __cplusplus
}
#endif

#endif
