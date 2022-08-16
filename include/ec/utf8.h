/* <utf8.h> -*- C -*- */
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

#include <ec/types.h>

#ifndef ECLIBC_UTF8_H
#define ECLIBC_UTF8_H 1

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
 * @def printf_utf8()
 * @brief               a unified way for the library to print utf8 characters.
 * @warning             this method, combined with "expand_utf(__value)" macro
 *                      dont take out the null bytes and they can leak into the
 *                      final stream if you are using fprintf and all stream
 *                      related functions. (they simply have to let you write
 *                      the null byte ('\0') into files. So, using this method
 *                      for stream printing is not advisable.
 *                      on the other hand, printf can handle it and print
 *                      complex UTF8 emojis without any problems.
 *                      In general, it is advisable to refrain from using this
 *                      method, and pass a large enough string to the
 *                      "ea_utf8_decode" function to print the emoji in the
 *                      string for you. Then you can use use the resulting
 *                      string like any other string.
 */
#define printf_utf8()       "%c%c%c%c"

/**
 * @def expand_utf(_utf8_value_)
 * @brief                   Expands a UTF8 value to be passed to printf
 *                          function.
 * @param [in]_utf8_value_  The UTF8 value to be expanded.
 */
#define expand_utf8(_utf8_value_) ea_utf8_get_byte(_utf8_value_, 1), \
                                  ea_utf8_get_byte(_utf8_value_, 2), \
                                  ea_utf8_get_byte(_utf8_value_, 3), \
                                  ea_utf8_get_byte(_utf8_value_, 4)

/**
 * @brief ea_utf_get_byte   Gets the Nth byte used to print a UTF8 character
 * @param value             The UTF8 value to be decoded
 * @param index             The number of the byte that is being requested.
 * @return                  0 if the value doesn't expand to the given index,
 *                          and the appropriate character if it exists.
 */
char ea_utf8_get_byte(ec_utf8_t value, uint8_t index);

/**
 * @brief ea_utf8_decode    Prints the given UTF8 character into the string
 *                          pointer passed to this function. This is the
 *                          recommended way of using UTF8 characters, compared
 *                          to "printf_utf8"
 * @param [in]value         The UTF8 value to be decoded
 * @param [out]pointer      The pointer to the target string to hold the
 *                          decoded string.
 */
void ea_utf8_decode  (ec_utf8_t value, char *pointer);

#ifdef __cplusplus
}
#endif

#endif
