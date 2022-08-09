/* <map.c> -*- C -*- */
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

#include <ec/map.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Lower-case digits.  */
const char __ec_itoa_lower_digits[36]
        = "0123456789abcdefghijklmnopqrstuvwxyz";
/* Upper-case digits.  */
const char __ec_itoa_upper_digits[36]
        = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static inline char *
__attribute__ ((unused, always_inline))
_ec_itoa (unsigned long int value, char *buflim,
          unsigned int base, int upper_case)
{
    extern const char __ec_itoa_upper_digits[];
    extern const char __ec_itoa_lower_digits[];
    const char *digits = (upper_case
                          ? __ec_itoa_upper_digits : __ec_itoa_lower_digits);
    char *bp = buflim;
    switch (base)
    {
#define SPECIAL(Base)                                                          \
        case Base:                                                             \
            do                                                                 \
                *--bp = digits[value % Base];                                  \
            while ((value /= Base) != 0);                                      \
            break
        SPECIAL (10);
        SPECIAL (16);
        SPECIAL (8);
        SPECIAL (2);
#undef SPECIAL
        default:
            do
                *--bp = digits[value % base];
            while ((value /= base) != 0);
    }
    return bp;
}

typedef int DUMMY_TYPEDEF_TO_AVOID_PEDANTIC_ERROR;

#ifdef __cplusplus
}
#endif

