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

#ifdef __cplusplus
#include <cstdint>
#include <cstddef>
#else
#include <stdint.h>
#include <stddef.h>
#endif

#include <stdint.h>

#include <ec/arch.h>

#ifndef ECLIBC_PRINTF_H
#define ECLIBC_PRINTF_H 1

/**
 * @file    printf.h
 * @brief   Different compilers and different CPU architectures have different
 *          understanding of different data types. To avoid misprints and
 *          annoying compiler warnings about using the wrong format in printf,
 *          this file unifies all the data types using macros.
 *
 * @example
 *          // it will print 123 in the output regardless of the compiler and
 *          // architecture
 *          printf(printf_uint8(1,1), 123);
 *
 *          // this one will print the following string:
 *          // "This is a testing string: __the testing string to be printed__
 *          //  followed by a testing integer: -456"
 *          printf("This is a testing string: " printf_string()
 *                 " followed by a testing integer: " printf_int(1,1),
 *                 "__the testing string to be printed__", -456);
 */

#if (EC_ARCH == 8)
#    define printf_uint8(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint16(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint32(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "lu"
#    define printf_uint64(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "llu"
#    define printf_int8(SPACE_PAD, ZERO_PAD)                                   \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int16(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int32(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "li"
#    define printf_int64(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "lli"
#    define printf_int(SPACE_PAD, ZERO_PAD)                                    \
                    "%" #SPACE_PAD "." #ZERO_PAD       "d"
#    define printf_double(SPACE_PAD, FLOATING_COUNT)                           \
                    "%" #SPACE_PAD "." #FLOATING_COUNT "f"
#elif (EC_ARCH == 16)
#    define printf_uint8(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint16(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint32(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "lu"
#    define printf_uint64(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "llu"
#    define printf_int8(SPACE_PAD, ZERO_PAD)                                   \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int16(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int32(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "li"
#    define printf_int64(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "lli"
#    define printf_int(SPACE_PAD, ZERO_PAD)                                    \
                    "%" #SPACE_PAD "." #ZERO_PAD       "d"
#    define printf_double(SPACE_PAD, FLOATING_COUNT)                           \
                    "%" #SPACE_PAD "." #FLOATING_COUNT "f"
#elif (EC_ARCH == 32)
#    define printf_uint8(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint16(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint32(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "lu"
#    define printf_uint64(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "llu"
#    define printf_int8(SPACE_PAD, ZERO_PAD)                                   \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int16(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int32(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "li"
#    define printf_int64(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "lli"
#    define printf_int(SPACE_PAD, ZERO_PAD)                                    \
                    "%" #SPACE_PAD "." #ZERO_PAD       "d"
#    define printf_double(SPACE_PAD, FLOATING_COUNT)                           \
                    "%" #SPACE_PAD "." #FLOATING_COUNT "f"
#else
#    define printf_uint8(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint16(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint32(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "u"
#    define printf_uint64(SPACE_PAD, ZERO_PAD)                                 \
                    "%" #SPACE_PAD "." #ZERO_PAD       "lu"
#    define printf_int8(SPACE_PAD, ZERO_PAD)                                   \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int16(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int32(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "i"
#    define printf_int64(SPACE_PAD, ZERO_PAD)                                  \
                    "%" #SPACE_PAD "." #ZERO_PAD       "li"
#    define printf_int(SPACE_PAD, ZERO_PAD)                                    \
                    "%" #SPACE_PAD "." #ZERO_PAD       "d"
#    define printf_double(SPACE_PAD, FLOATING_COUNT)                           \
                    "%" #SPACE_PAD "." #FLOATING_COUNT "f"
#endif

/**
 * @def printf_percent()
 * @brief       Passes the correct sequence to the printf to print % character.
 */
#define printf_percent()         "%%"

/**
 * @def printf_string(LENGTH)
 * @brief               Passes the correct format to the printf to print a
 *                      string.
 * @param [in]LENGTH    The desired length of the string. Printf will pad the
 *                      string using space character to make sure the printed
 *                      string has the required length.
 */
#define printf_string(LENGTH)    "%" #LENGTH "s"

/**
 * @def printf_IP()
 * @brief               Passes the correct format to the printf to print an IP
 *                      address.
 */
#define printf_IP()                                                            \
                printf_uint8(1,1) "." printf_uint8(1,1) "."                    \
                printf_uint8(1,1) "." printf_uint8(1,1)

/**
 * @def printf_hex8()
 * @brief               Passes the correct format to the printf to print an 8
 *                      bit long number in it's hex form.
 */
#define printf_hex8()            "%2.2X"

/**
 * @def printf_hex16()
 * @brief               Passes the correct format to the printf to print a 16
 *                      bit long number in it's hex form.
 */
#define printf_hex16()           printf_hex8()  printf_hex8()

/**
 * @def printf_hex24()
 * @brief               Passes the correct format to the printf to print a 24
 *                      bit long number in it's hex form.
 */
#define printf_hex24()           printf_hex16() printf_hex8()

/**
 * @def printf_hex32()
 * @brief               Passes the correct format to the printf to print a 32
 *                      bit long number in it's hex form.
 */
#define printf_hex32()           printf_hex24() printf_hex8()

/**
 * @def printf_hex48()
 * @brief               Passes the correct format to the printf to print a 48
 *                      bit long number in it's hex form.
 */
#define printf_hex48()           printf_hex32() printf_hex16()

/**
 * @def printf_hex64()
 * @brief               Passes the correct format to the printf to print a 64
 *                      bit long number in it's hex form.
 */
#define printf_hex64()           printf_hex48() printf_hex16()

/**
 * @def printf_MAC()
 * @brief               Passes the correct format to the printf to print a MAC
 *                      address.
 */
#define printf_MAC()                                                           \
                printf_hex8() ":" printf_hex8() ":" printf_hex8() ":"          \
                printf_hex8() ":" printf_hex8() ":" printf_hex8() ":"

/**
 * @def printf_timezone()
 * @brief               Passes the correct format to the printf to print a
 *                      time zone value. (+HH:MM / -HH:MM)
 */
#define printf_timezone()        "%c" printf_uint8(2,2) ":" printf_uint8(2,2)

/**
 * @def printf_phonenumber()
 * @brief               Passes the correct format to the printf to print a 12
 *                      digit phone number. (+XXYYYZZZZZZZ)
 */
#define printf_phonenumber()     "+"  printf_uint64(12,12)

/**
 * @def printf_date()
 * @brief               Passes the correct format to the printf to print a
 *                      given date.
 */
#define printf_date()                                                          \
                printf_uint16(4,4) "/" printf_uint8(2,2) "/" printf_uint8(2,2)

/**
 * @def printf_date()
 * @brief               Passes the correct format to the printf to print a
 *                      given time.
 */
#define printf_time()                                                          \
                printf_uint8(2,2)  ":" printf_uint8(2,2) ":" printf_uint8(2,2)

/**
 * @def expand_phonenumber(Value)
 * @brief       Makes a 12 digit phone number ready to be printed by printf.
 *              It should accompany "printf_phonenumber()"
 */
#define expand_phonenumber(Value)                                              \
        (((uint64_t)((Value < 0) ? (Value * -1) : (Value))) % 0xE8D4A51000)

/**
 * @def expand_date(Year, Month, Day)
 * @brief       Makes sure the year value is in range and pass the given date
 *              to the printf function.
 *              It should accompany "printf_date()"
 */
#define expand_date(Year, Month, Day)                                          \
        ((uint16_t)((Year < 100) ? (Year + 2000) : Year)),                     \
        ((uint8_t)Month),                                                      \
        ((uint8_t)Day)

/**
 * @def expand_time(Hour, Minute, Second)
 * @brief       Passese the given time to the printf function.
 *              It should accompany "printf_time()"
 */
#define expand_time(Hour, Minute, Second) \
        ((uint8_t)Hour), ((uint8_t)Minute), ((uint8_t)Second)

/**
 * @def expand_timeZone(Hour, Minute)
 * @brief       Decides the time zone's sign and pass the correct form to the
 *              printf function.
 *              It should accompany "printf_timezone()"
 */
#define expand_timeZone(Hour, Minute)                                          \
        (((int8_t)Hour < 0) ? '-' : '+'),                                      \
        (uint8_t)(((Hour < 0) ? (Hour * -1) : (Hour))),                        \
        ((Minute == 0) ? 0 : 30)

/**
 * @def expand_hex8(value)
 * @brief       Passes the first byte of the number to the printf function to
 *              print it in the hex form.
 *              It should accompany "printf_hex8()"
 */
#define expand_hex8(value)                                                     \
    ((uint8_t)(value & 0xFF))

/**
 * @def expand_hex16(value)
 * @brief       Passes the first two bytes of the number to the printf
 *              function to print them in the hex form.
 *              It should accompany "printf_hex16()"
 */
#define expand_hex16(value)                                                    \
    ((uint8_t)((value >> 8) & 0xFF)), Expand_HEX8(value)

/**
 * @def expand_hex24(value)
 * @brief       Passes the first three bytes of the number to the printf
 *              function to print them in the hex form.
 *              It should accompany "printf_hex24()"
 */
#define expand_hex24(value)                                                    \
    ((uint8_t)((value >> 16) & 0xFF)), Expand_HEX16(value)

/**
 * @def expand_hex32(value)
 * @brief       Passes the first four bytes of the number to the printf
 *              function to print them in the hex form.
 *              It should accompany "printf_hex32()"
 */
#define expand_hex32(value)                                                    \
    ((uint8_t)(value >> 24) & 0xFF)),  Expand_HEX24(value)

/**
 * @def expand_hex48(value)
 * @brief       Passes the first six bytes of the number to the printf
 *              function to print them in the hex form.
 *              It should accompany "printf_hex48()"
 */
#define expand_hex48(value)                                                    \
    ((uint8_t)(value >> 40) & 0xFF)), ((uint8_t)(value >> 32) & 0xFF)),        \
    Expand_HEX32(value)

#define expand_MAC(value)   expand_hex48(value)

/**
 * @def expand_hex64(value)
 * @brief       Passes the first eight bytes of the number to the printf
 *              function to print them in the hex form.
 *              It should accompany "printf_hex64()"
 */
#define expand_hex64(value)                                                    \
    ((uint8_t)((value >> 56) & 0xFF)), ((uint8_t)((value >> 48) & 0xFF)),      \
    expand_hex48(value)

/**
 * @def expand_IP(value)
 * @brief       Devides the IPv4 address to four bytes so that it can be
 *              printed in a human readable format.
 *              It should accompany "printf_IP()"
 */
#define expand_IP(value)    expand_hex32(VarName)

/**
 * @brief ec_generate_progress_bar      Generate a progress bar with the given
 *                                      width, on the given progress count.
 *                                      Since some progress bars are generated
 *                                      using UTF characters, the characters
 *                                      of choice must be given in string
 *                                      format and NOT character format.
 *                                      If you are going for UTF characters,
 *                                      make sure you have enough space in the
 *                                      given pointer.
 * @param [out]ptr                      The pointer to hold the progress bar.
 * @param [in]progress                  Current progress, in percent. (0-100)
 * @param [in]width                     Width of the progress bar itself.
 * @param [in]character_empty           The character to be used for the empty
 *                                      space of the bar.
 * @param [in]character_filled          The character to be used for the filled
 *                                      space of the bar.
 * @example
 *      ec_generate_progress_bar(ptr, 20, 10, "-", "#")   =
 *              "##--------"
 *      ec_generate_progress_bar(ptr, 60, 15, "▱", "▰") =
 *              "▰▰▰▰▰▰▰▰▰▱▱▱▱▱▱"
 */
void ec_generate_progress_bar(char *ptr, double progress, int width,
                                 const char *character_empty,
                                 const char *character_filled);





#endif


