/* <fota.h> -*- C -*- */
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

#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <ec/itoa.h>

#ifndef ECLIBC_FTOA_H
#define ECLIBC_FTOA_H 1

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

/**
 * @brief ec_ecvt_break     breaks a double value into it's sub-parts.
 * @param [in]value         the double value to be separated.
 * @param [out]intpart      the integer part of the double value.
 * @param [in/out]decpart   [in]the number of decimal digits requested.
 *                          [out]the decimal part of the double value.
 */
static inline void
__attribute__ ((unused, always_inline))
ec_break_double(double value, int64_t *intpart, uint64_t *decpart)
{
    *intpart = (int64_t)value;
    *decpart = (uint64_t)(((value - (double)*intpart) *
                                                    pow(10, (double)*decpart)));
}

/**
 * @brief ec_ftoa       Converts a double value to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]dec       Number of decimal places to be generated.
 * @return              The pointer to the start of the generated string.
 */
static inline char *
__attribute__ ((unused, always_inline))
ec_ftoa(double value, char *__restrict buflim, int dec)
{
    int64_t intpart;
    uint64_t decpart = (uint64_t)dec;
    ec_break_double(value, &intpart, &decpart);
    buflim = ec_itoa_uint64_t(decpart, buflim, 10, 1);
    *--buflim = '.';
    return ec_itoa_int64_t(intpart, buflim, 10, 1);
}


#ifdef __cplusplus
}
#endif

#endif
