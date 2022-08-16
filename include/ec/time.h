/* <time.h> -*- C -*- */
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

#include <time.h>

#ifndef ECLIBC_TIME_H
#define ECLIBC_TIME_H 1

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

typedef enum
{
    ec_January,
    ec_February,
    ec_March,
    ec_April,
    ec_May,
    ec_June,
    ec_July,
    ec_August,
    ec_September,
    ec_October,
    ec_November,
    ec_December
} ec_months;

extern const char *ec_month_name_str[];

#ifdef __cplusplus
}
#endif

#ifndef ECLIBC_INTERNAL_COMPILE

#if defined(__XTENSA__)

#elif defined(XC16)

#ifndef FCY
#    ifndef EC_XC16_PERIPHRAL_FREQUENCY
#        error "To use <ec/time.h> to add delay functions, you need to define \
the periphral clock frequency in compile flags, e.q. \
-DEC_XC16_PERIPHRAL_FREQUENCY=4000000"
#    endif
#    define FCY EC_XC16_PERIPHRAL_FREQUENCY
#endif
#include <libpic30.h>
#include <stdint.h>
#include <xc.h>

#ifndef __delay_ns
#define __delay_ns(_ns)  __asm__("nop")
#endif
#define __delay_s(time) ____ec_delay_s((uint32_t)time)

static inline void
__attribute__ ((unused, always_inline))
____ec_delay_s(uint32_t time)
{
    while(time > 0)
    {
        time--;
        __delay_ms(1000);
        ClrWdt();
    }
}


#elif defined(XC32)

#elif defined(__cplusplus)

#include <chrono>
#include <thread>
#define __delay_ns(_ns) \
    std::this_thread::sleep_for(std::chrono::nanoseconds(_ns))
#define __delay_us(_us) \
    std::this_thread::sleep_for(std::chrono::microseconds(_us))
#define __delay_ms(_ms) \
    std::this_thread::sleep_for(std::chrono::milliseconds(_ms))
#define __delay_s(_s)   \
    std::this_thread::sleep_for(std::chrono::milliseconds(_s * 1000))

#else

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <time.h>
#include <unistd.h>

#define __delay_ns(_ns) __asm__("nop")
#define __delay_us(_us) usleep((__useconds_t)_us)
#define __delay_ms(_ms) __delay_us((_ms * 1000))
#define __delay_s(_s)   __delay_ms((_s * 1000))

#endif

#endif

#endif
