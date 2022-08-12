/* <itoa.h> -*- C -*- */
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

/**
 * @file itoa.h
 * @brief       since itoa doesn't exist on some compilars, and in general
 *              itoa is reliant on the architecture of the processors and
 *              doesn't produce a unified result over all the platforms,
 *              different types of itoa is implemented here to ensure we have
 *              the same tools on every platform and every compiler.
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef ECLIBC_ITOA_H
#define ECLIBC_ITOA_H 1

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
 * @brief ec_itoa       Converts an unsigned long int to a string. It is not
 *                      recomended to use this function, since integer's size
 *                      is platform dependent, and hence it will render your
 *                      code unportable between different platforms.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
static inline char *
__attribute__ ((unused, always_inline))
ec_itoa (unsigned long int value, char *__restrict buflim,
          unsigned int base, bool upper_case)
{
    extern const char __ec_upper_digits[];
    extern const char __ec_lower_digits[];
    const char *digits = ((upper_case == true)
                          ? __ec_upper_digits : __ec_lower_digits);
    do
        *--buflim = digits[value % base];
    while ((value /= base) != 0);
    return buflim;
}

#define __ec_itoa(type)                                                        \
    static inline char *                                                       \
    __attribute__ ((unused, always_inline))                                    \
    ec_itoa_##type (type value, char *__restrict buflim,                       \
                      type base, bool upper_case)                              \
    {                                                                          \
        extern const char __ec_upper_digits[];                                 \
        extern const char __ec_lower_digits[];                                 \
        const char *digits = ((upper_case == true)                             \
                              ? __ec_upper_digits :                            \
                                __ec_lower_digits);                            \
        uint8_t sign = 0;                                                      \
                                                                               \
        if(value < 0 && base == 10)                                            \
        {                                                                      \
            value = (type)(value * -1);                                        \
            sign = 1;                                                          \
        }                                                                      \
                                                                               \
        do                                                                     \
        {                                                                      \
            *--buflim = digits[(uint8_t)(value % base)];                       \
            value = (type)(value /base);                                       \
        } while (value != 0);                                                  \
                                                                               \
        if(sign == 1)                                                          \
            *--buflim = '-';                                                   \
                                                                               \
        return buflim;                                                         \
    }

#define __ec_uitoa(type)                                                       \
    static inline char *                                                       \
    __attribute__ ((unused, always_inline))                                    \
    ec_itoa_##type (type value, char *__restrict buflim,                       \
                      type base, bool upper_case)                              \
    {                                                                          \
        extern const char __ec_upper_digits[];                                 \
        extern const char __ec_lower_digits[];                                 \
        const char *digits = ((upper_case == true)                             \
                              ? __ec_upper_digits :                            \
                                __ec_lower_digits);                            \
                                                                               \
        do                                                                     \
            *--buflim = digits[value % base];                                  \
        while ((value /= base) != 0);                                          \
                                                                               \
        return buflim;                                                         \
    }

/**
 * @brief ec_itoa_int   Converts an integer to a string. It is not recomended
 *                      to use this function, since integer's size is platform
 *                      dependent, and hence it will render your code unportable
 *                      between different platforms.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_itoa(int)

/**
 * @brief ec_itoa_int8_t    Converts an 8 bit signed integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_itoa(int8_t)

/**
 * @brief ec_itoa_int16_t   Converts a 16 bit signed integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_itoa(int16_t)

/**
 * @brief ec_itoa_int32_t   Converts a 32 bit signed integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_itoa(int32_t)

/**
 * @brief ec_itoa_int64_t   Converts a 64 bit signed integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_itoa(int64_t)

/**
 * @brief ec_itoa_uint8_t   Converts an 8 bit unsigned integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_uitoa(uint8_t)

/**
 * @brief ec_itoa_uint16_t  Converts a 16 bit unsigned integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_uitoa(uint16_t)

/**
 * @brief ec_itoa_uint32_t  Converts a 32 bit unsigned integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_uitoa(uint32_t)

/**
 * @brief ec_itoa_uint64_t  Converts a 64 bit unsigned integer to a string.
 * @param [in]value     The value to be converted to string.
 * @param [in]buflim    The pointer to the END of the string to be used for the
 *                      conversion.
 * @param [in]base      The base of the number to be used for the conversion.
 * @param [in]upper_case    if true, uppercase letters will be used.
 * @return              The pointer to the start of the generated string.
 */
__ec_uitoa(uint64_t)

#undef __ec_itoa
#undef __ec_uitoa

#ifdef __cplusplus
}
#endif

#endif
