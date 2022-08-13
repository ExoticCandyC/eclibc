/* <print_format_table.h> -*- C -*- */
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

#ifndef ECLIBC_INTERNAL_PRINT_FORMAT_TABLE_H
#define ECLIBC_INTERNAL_PRINT_FORMAT_TABLE_H 1

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
    __format_raw  = 0,
    __format_std  = 1,
    __format_ecio = 2
} __format_type;

typedef enum
{
    glibc_printf_form_unknown_space     = ' ',  /* for ' '  */
    glibc_printf_form_unknown_plus      = '+',  /* for '+'  */
    glibc_printf_form_unknown_minus     = '-',  /* for '-'  */
    glibc_printf_form_unknown_asteric   = '\'', /* for '\'' */
    glibc_printf_form_unknown_star      = '*',  /* for '*'  */
    glibc_printf_form_unknown_0         = '0',  /* for '0'  */
    glibc_printf_form_unknown_1         = '1',  /* for '1'  */
    glibc_printf_form_unknown_2         = '2',  /* for '2'  */
    glibc_printf_form_unknown_3         = '3',  /* for '3'  */
    glibc_printf_form_unknown_4         = '4',  /* for '4'  */
    glibc_printf_form_unknown_5         = '5',  /* for '5'  */
    glibc_printf_form_unknown_6         = '6',  /* for '6'  */
    glibc_printf_form_unknown_7         = '7',  /* for '7'  */
    glibc_printf_form_unknown_8         = '8',  /* for '8'  */
    glibc_printf_form_unknown_9         = '9',  /* for '9'  */
    glibc_printf_form_unknown_I         = 'I',  /* for 'I'  */

    glibc_printf_precision              = '.',  /* for '.'  */

    glibc_printf_mod_half               = 'h',
    /* for 'h' , aka short     = 2 bytes */
    glibc_printf_mod_long               = 'l',
    /* for 'l' , aka long      = 4 bytes */
    glibc_printf_mod_longlong_1         = 'L',
    /* for 'L' , aka long long = 8 bytes */
    glibc_printf_mod_longlong_2         = 'q',
    /* for 'q' , aka long long = 8 bytes */

    glibc_printf_form_size_t_1          = 'z',  /* for 'z' , aka size_t */
    glibc_printf_form_size_t_2          = 'Z',  /* for 'Z' , aka size_t */
    glibc_printf_form_percent           = '%',  /* for '%' , aka size_t */

    glibc_printf_form_integer_1         = 'i',
    /* for 'i' , aka int       = 4 bytes */
    glibc_printf_form_integer_2         = 'd',
    /* for 'd' , aka int       = 4 bytes */
    glibc_printf_form_unsigned          = 'u',
    /* for 'u' , aka unsignint = 4 bytes */
    glibc_printf_form_octal             = 'o',
    /* for 'o' , aka int       = 4 bytes */
    glibc_printf_form_hexa_Cap          = 'X',
    /* for 'X' , aka int       = 4 bytes */
    glibc_printf_form_hexa_Lower        = 'x',
    /* for 'x' , aka int       = 4 bytes */
    glibc_printf_form_float_E           = 'E',
    /* for 'E' , scientific form double  */
    glibc_printf_form_float_e           = 'e',
    /* for 'e' , scientific form double  */
    glibc_printf_form_float_F           = 'F',
    /* for 'F' , double                  */
    glibc_printf_form_float_f           = 'f',
    /* for 'f' , double                  */
    glibc_printf_form_float_G           = 'G',
    /* for 'G' , shortest double form    */
    glibc_printf_form_float_g           = 'g',
    /* for 'g' , shortest double form    */
    glibc_printf_form_character         = 'c',
    /* for 'c' , aka char      = 1 byte  */
    glibc_printf_form_string_1          = 's',
    /* for 's' , aka string              */
    glibc_printf_form_string_2          = 'S',
    /* for 'S' , aka string              */
    glibc_printf_form_pointer           = 'p',
    /* for 'p' , aka pointer   = 8 bytes */
    glibc_printf_mod_ptrdiff_t          = 't',
    /* for 't' , aka pointer dif = 8 bytes */
    glibc_printf_form_strerror          = 'm',
    /* for 'm' , ="%s", strerror (errno) */

    glibc_printf_form_floathex_Cap      = 'A',               /* NOT SUPPORTED */
    /* for 'A' , aka double hex form     */                  /* NOT SUPPORTED */
    glibc_printf_form_float_hex_Lower   = 'a',               /* NOT SUPPORTED */
    /* for 'a' , aka double hex form     */                  /* NOT SUPPORTED */
    glibc_printf_mod_intmax_t           = 'j',               /* NOT SUPPORTED */
    /* for 'j' , int max, */                                 /* NOT SUPPORTED */
    glibc_printf_form_wcharacter        = 'C',               /* NOT SUPPORTED */
    /* for 'C' , aka wchar_t. */                             /* NOT SUPPORTED */
    glibc_printf_form_number            = 'n',               /* NOT SUPPORTED */
    /* for 'n' , put the printed character count before */   /* NOT SUPPORTED */
    /* this specifier into the variable. */                  /* NOT SUPPORTED */

    /* Free characters: */
    glibc_printf_free_character_01      = 'b',
    glibc_printf_free_character_02      = 'k',
    glibc_printf_free_character_03      = 'r',
    glibc_printf_free_character_04      = 'v',
    glibc_printf_free_character_05      = 'w',
    glibc_printf_free_character_06      = 'y',
    glibc_printf_free_character_07      = 'B',
    glibc_printf_free_character_08      = 'D',
    glibc_printf_free_character_09      = 'H',
    glibc_printf_free_character_10      = 'J',
    glibc_printf_free_character_11      = 'K',
    glibc_printf_free_character_12      = 'M',
    glibc_printf_free_character_13      = 'N',
    glibc_printf_free_character_14      = 'O',
    glibc_printf_free_character_15      = 'P',
    glibc_printf_free_character_16      = 'Q',
    glibc_printf_free_character_17      = 'R',
    glibc_printf_free_character_18      = 'T',
    glibc_printf_free_character_19      = 'U',
    glibc_printf_free_character_20      = 'V',
    glibc_printf_free_character_21      = 'W',
    glibc_printf_free_character_22      = 'Y',
    glibc_printf_free_character_24      = '@',
    glibc_printf_free_character_25      = '#',
    glibc_printf_free_character_26      = '$',
    glibc_printf_free_character_28      = '&',
    glibc_printf_free_character_30      = '(',
    glibc_printf_free_character_31      = ')',
    glibc_printf_free_character_32      = '_',
    glibc_printf_free_character_33      = '/',
    glibc_printf_free_character_34      = ',',
    glibc_printf_free_character_35      = ';',
    glibc_printf_free_character_36      = '[',
    glibc_printf_free_character_37      = ']',
    glibc_printf_free_character_38      = '{',
    glibc_printf_free_character_39      = '}',
    glibc_printf_free_character_40      = '|'

} glibc_printf_characters;

typedef enum
{
    /**************************************************************************/
    /*                           General Character                            */
    /**************************************************************************/
    eclibc_printf_form_unknown_space    = ' ',  /* for ' '  */
    eclibc_printf_form_unknown_plus     = '+',  /* for '+'  */
    eclibc_printf_form_unknown_minus    = '-',  /* for '-'  */
    eclibc_printf_form_unknown_asteric  = '\'', /* for '\'' */
    eclibc_printf_form_unknown_star     = '*',  /* for '*'  */
    eclibc_printf_form_unknown_0        = '0',  /* for '0'  */
    eclibc_printf_form_unknown_1        = '1',  /* for '1'  */
    eclibc_printf_form_unknown_2        = '2',  /* for '2'  */
    eclibc_printf_form_unknown_3        = '3',  /* for '3'  */
    eclibc_printf_form_unknown_4        = '4',  /* for '4'  */
    eclibc_printf_form_unknown_5        = '5',  /* for '5'  */
    eclibc_printf_form_unknown_6        = '6',  /* for '6'  */
    eclibc_printf_form_unknown_7        = '7',  /* for '7'  */
    eclibc_printf_form_unknown_8        = '8',  /* for '8'  */
    eclibc_printf_form_unknown_9        = '9',  /* for '9'  */

    eclibc_printf_precision             = '.',  /* for '.'  */

    /**************************************************************************/
    /*                            format modifiers                            */
    /**************************************************************************/
    eclibc_printf_custom_mode           = '!', /* enter eclibc mode           */
    eclibc_printf_upper_case            = '^', /* prints the hex in uppercase */

    /**************************************************************************/
    /*                           format characters                            */
    /**************************************************************************/


                              /* Date-Time formats */

    /* upper casing a time value will cause AM/PM mode */
    /* upper casing a date value will cause the month name to be printed */
    eclibc_printf_time_seconds          = 't',
    /* time of day, using time_seconds_t                     12:13:14         */
    eclibc_printf_Time_struct_tm        = 'T',
    /* time of day, using struct tm                          12:13:14         */
    eclibc_printf_time_seconds_short    = 's',
    /* time of day, using time_seconds_t                     12:13            */
    eclibc_printf_time_struct_tm_short  = 'S',
    /* time of day, using struct tm, dropping the seconds    12:13            */

    eclibc_printf_date_2digit           = 'd',
    /* date       , using struct tm                          DD/MM/YY         */
    eclibc_printf_date_4digit           = 'D',
    /* date       , using struct tm                          DD/MM/YYYY       */
    eclibc_printf_utc_time              = 'Z',
    /* utc time string, using struct tm                yyyy-mm-ddThh:mm:ssZ   */

                            /* Different number bases */
    eclibc_printf_base_2                = 'b', /* ALWAYS a multiple of 8      */
    eclibc_printf_base_8                = 'o', /* can be any number of digits */
    eclibc_printf_base_16               = 'H', /* ALWAYS a multuple of 2      */
    /* ^ can be used to capitalize hex values                                 */
    /* adding + to the format will turn the value unsigned                    */
    /* all the sizings are regardless of the CPU architecture                 */
    /* '.'  format will make it a 8 bit value                                 */
    /* no size format will make it a 16 bit value                             */
    /* 'l'  format will make it a 32 bit value, regardless of architecture    */
    /* 'll' format will make it a 64 bit value, regardless of architecture    */
    /*          (8bit CPUS dont have the support for 64 bit values)           */

                            /* Boolean (True, False) */
    eclibc_printf_bool                  = 'B', /* False = 0 / True = ?        */

                              /* Special Character */

    eclibc_printf_utf8                  = 'U',
    /* prints UTF characters, using ec_utf8_t                                 */


                               /* Network formats */
    eclibc_printf_phone_number          = 'P',               /* +XXYYYZZZZZZZ */
    /* prints a phone number, the international form, using ec_phonenumber_t  */
    /* The same as %+llu but with the adition of % to make sure it's always   */
    /* 12 digits.                                                             */


    eclibc_printf_IPv4_Address          = 'i', /* expects a uin32_t */
    eclibc_printf_IPv6_Address          = 'I',
                             /* IPv6: 2001:0db8:85a3:0000:0000:8a2e:0370:7334 */
                             /* Expects the ec_ipv6_t data_type               */

    eclibc_printf_MAC_PC_Version        = 'm', /* 00:00:5e:00:53:af */
    eclibc_printf_MAC_PC_Version_caps   = 'M', /* 00:00:5E:00:53:AF */
    eclibc_printf_MAC_CISCO             = 'c', /* 0123.4567.89ab    */
    eclibc_printf_MAC_CISCO_caps        = 'C'  /* 0123.4567.89ab    */
                             /* Both mac addresses require the ec_mac_t type  */
} eclibc_printf_characters;

#ifdef __cplusplus
}
#endif

#endif
