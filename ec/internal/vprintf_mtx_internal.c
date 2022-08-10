/* <vprintf_mtx_internal.c> -*- C -*- */
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

#if !(defined(XC16) || defined(XC32))

#include <time.h>
#include <ec/io.h>
#include <ec/itoa.h>
#include <ec/ftoa.h>
#include <ec/types.h>
#include <ec/internal/pad_string.h>
#include <ec/internal/vprintf_internal.h>
#include <ec/internal/print_format_table.h>
#include <ec/mutex.h>

#ifdef __cplusplus
extern "C"
{
#endif

__attribute__ ((visibility("hidden")))
ec_mutex __ec_printf_mtx_mutext;

void __ec_printf_mtx_init_mutex()
{
    ec_mutex_init(__ec_printf_mtx_mutext);
}

__attribute__ ((visibility("hidden")))
const char    *__restrict __ec_printf_mtx_temp_buffer_tail;

__attribute__ ((visibility("hidden")))
const char    *__restrict __ec_printf_mtx_temp_buffer;

__attribute__ ((visibility("hidden")))
char    *__restrict __ec_printf_mtx_numBuffer_End;

__attribute__ ((visibility("hidden")))
char    *__restrict __ec_printf_mtx_numBuffer;

__attribute__ ((visibility("hidden")))
int     __ec_printf_mtx_leftNumber;

__attribute__ ((visibility("hidden")))
int     __ec_printf_mtx_rightNumber;

__attribute__ ((visibility("hidden")))
uint8_t __ec_printf_mtx_Number_set;      /* | 1 = right ...... | 2 = left */

__attribute__ ((visibility("hidden")))
uint8_t __ec_printf_mtx_Number_negative; /* | 1 = right ...... | 2 = left */

__attribute__ ((visibility("hidden")))
uint8_t __ec_printf_mtx_long_count;      /* 0: half, 1: normal, 2: long, 2 >: ll */

__attribute__ ((visibility("hidden")))
uint8_t __ec_printf_mtx_show_sign;       /* 1 = Do, 0 = Dont, 2 = Maybe*/

__attribute__ ((visibility("hidden")))
bool    __ec_printf_mtx_side_right;

__attribute__ ((visibility("hidden")))
struct tm __ec_printf_mtx_scratch_memory;

#define EC_SCRATCH(type) *((type *)(&__ec_printf_mtx_scratch_memory))

#define __ec_printf_int(_type, _base, _upperCase)                              \
    {                                                                          \
        if(__ec_printf_mtx_Number_negative & 1)                                    \
            __ec_printf_mtx_rightNumber = __ec_printf_mtx_rightNumber * -1;            \
        if(__ec_printf_mtx_Number_negative & 2)                                    \
            __ec_printf_mtx_leftNumber = __ec_printf_mtx_leftNumber * -1;              \
        if((__ec_printf_mtx_Number_set & 2) == 0)                                  \
            __ec_printf_mtx_leftNumber = 0;                                        \
        if((__ec_printf_mtx_Number_set & 1) == 0)                                  \
            __ec_printf_mtx_rightNumber = 0;                                       \
        __ec_printf_mtx_numBuffer = ec_itoa_##_type (EC_SCRATCH(_type),            \
                        __ec_printf_mtx_numBuffer_End, _base, _upperCase);         \
        __ec_printf_mtx_numBuffer = ec_pad_num_string(__ec_printf_mtx_rightNumber,     \
                            __ec_printf_mtx_numBuffer, __ec_printf_mtx_numBuffer_End); \
        ec_fpad_string(__stream, __ec_printf_mtx_leftNumber, ' ',                  \
                         __ec_printf_mtx_numBuffer, __ec_printf_mtx_numBuffer_End);    \
    }

#define __ec_printf_double()                                                   \
    {                                                                          \
        if(__ec_printf_mtx_Number_negative & 1)                                    \
            __ec_printf_mtx_rightNumber = __ec_printf_mtx_rightNumber * -1;            \
        if(__ec_printf_mtx_Number_negative & 2)                                    \
            __ec_printf_mtx_leftNumber = __ec_printf_mtx_leftNumber * -1;              \
        if((__ec_printf_mtx_Number_set & 2) == 0)                                  \
            __ec_printf_mtx_leftNumber = 0;                                        \
        if((__ec_printf_mtx_Number_set & 1) == 0)                                  \
            __ec_printf_mtx_rightNumber = 6;                                       \
        __ec_printf_mtx_numBuffer = ec_ftoa(EC_SCRATCH(double),                    \
                                     __ec_printf_mtx_numBuffer_End,                \
                                                    __ec_printf_mtx_rightNumber);  \
        ec_fpad_string(__stream, __ec_printf_mtx_leftNumber, ' ',                  \
                                     __ec_printf_mtx_numBuffer,                    \
                                                __ec_printf_mtx_numBuffer_End);    \
    }

#define __ec_printf_string()                                                   \
    {                                                                          \
        size_t __temp = strlen(EC_SCRATCH(char *));                            \
        if(__ec_printf_mtx_Number_negative & 1)                                    \
            __ec_printf_mtx_rightNumber = __ec_printf_mtx_rightNumber * -1;            \
        if(__ec_printf_mtx_Number_negative & 2)                                    \
            __ec_printf_mtx_leftNumber = __ec_printf_mtx_leftNumber * -1;              \
        if((__ec_printf_mtx_Number_set & 2) == 0)                                  \
            __ec_printf_mtx_leftNumber = 0;                                        \
        if((__ec_printf_mtx_Number_set & 1) == 0 ||                                \
                                    (size_t)__ec_printf_mtx_rightNumber > __temp)  \
            __ec_printf_mtx_rightNumber = (int)__temp;                             \
        ec_fpad_string(__stream, __ec_printf_mtx_leftNumber, ' ',                  \
                                                  EC_SCRATCH(char *),          \
                              (EC_SCRATCH(char *) + __ec_printf_mtx_rightNumber)); \
    }

#define __ec_printf_add_digit(_value)                                          \
    {                                                                          \
        if(__ec_printf_mtx_side_right == true)                                     \
        {                                                                      \
            __ec_printf_mtx_rightNumber *= 10;                                     \
            __ec_printf_mtx_rightNumber += _value;                                 \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            __ec_printf_mtx_leftNumber  *= 10;                                     \
            __ec_printf_mtx_leftNumber += _value;                                  \
        }                                                                      \
    }

#define EC_PRINTF_GO_TO_RAW_FORMAT()                                           \
    {                                                                          \
        __ec_printf_mtx_temp_buffer_tail = __format + 1;                           \
        format_type = __format_raw;                                            \
    }

__attribute__((hot,noinline))
void
ec_vfprintf_mtx(FILE *__restrict __stream,
                            const char *__restrict __format, va_list __arg)
{
    /* as much to satisfy a 64 bit binary and more */
    char NumBuffer_Storage[81];
    __format_type format_type = __format_raw;
    __ec_printf_mtx_numBuffer_End = NumBuffer_Storage + 80;
    *__ec_printf_mtx_numBuffer_End = '\0';
    __ec_printf_mtx_temp_buffer      = __format;
    __ec_printf_mtx_temp_buffer_tail = __format;
    while(*__ec_printf_mtx_temp_buffer != '%')
    {
        if(*__ec_printf_mtx_temp_buffer++ == '\0')
        {
            fputs(__format, __stream);
            return;
        }
    }
    ec_fwrite(__ec_printf_mtx_temp_buffer_tail, (__ec_printf_mtx_temp_buffer -
                                       __ec_printf_mtx_temp_buffer_tail), __stream);
    __ec_printf_mtx_temp_buffer_tail = __ec_printf_mtx_temp_buffer;
    __format = __ec_printf_mtx_temp_buffer - 1;
    while(*++__format != '\0')
    {
        if(format_type != __format_raw)
        {
            switch((*__format))
            {
                #define CheckDigit(_char, _digit)                              \
                case _char:                                                    \
                    __ec_printf_mtx_Number_set =                                   \
                            (uint8_t)(__ec_printf_mtx_Number_set |                 \
                                    ((__ec_printf_mtx_side_right == true)          \
                                            ? 1 : 2));                         \
                    __ec_printf_add_digit(_digit);                             \
                    continue;
                CheckDigit('0', 0);
                CheckDigit('1', 1);
                CheckDigit('2', 2);
                CheckDigit('3', 3);
                CheckDigit('4', 4);
                CheckDigit('5', 5);
                CheckDigit('6', 6);
                CheckDigit('7', 7);
                CheckDigit('8', 8);
                CheckDigit('9', 9);
                #undef CheckDigit
                /* Size modifiers */
                case glibc_printf_mod_half:
                    __ec_printf_mtx_long_count = 0;
                    continue;
                case glibc_printf_mod_long:
                    __ec_printf_mtx_long_count++;
                    continue;
                case glibc_printf_mod_longlong_1:
                case glibc_printf_mod_longlong_2:
                    __ec_printf_mtx_long_count = 3;
                    continue;
                case '-':
                    __ec_printf_mtx_Number_negative =
                            (uint8_t)(__ec_printf_mtx_Number_negative |
                                    ((__ec_printf_mtx_side_right == true) ? 1 : 2));
                    continue;
                case '.':
                    __ec_printf_mtx_side_right = true;
                    continue;
                case '+':
                    continue;
            };
        }
        switch(format_type)
        {
            case __format_std:
            {
                switch ((*__format))
                {
                    /* The ticket to go into ec format mode */
                    case eclibc_printf_custom_mode:
                    {
                        format_type = __format_ecio;
                        continue;
                    }

                    /* Raw characters */
                    case glibc_printf_form_percent:
                    {
                        ec_fputc('%', __stream);
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_character:
                    {
                        EC_SCRATCH(char) = (char)(va_arg(__arg, int));
                        ec_fputc(EC_SCRATCH(char), __stream);
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }

                    /* Format characters */
                    case glibc_printf_form_integer_1:
                    case glibc_printf_form_integer_2:
                    {
                        switch(__ec_printf_mtx_long_count)
                        {
                            case 0:
                                EC_SCRATCH(int8_t) = (int8_t)va_arg(__arg, int);
                                __ec_printf_int(int8_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 1:
                                EC_SCRATCH(int16_t)
                                                  = (int16_t)va_arg(__arg, int);
                                __ec_printf_int(int16_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 2:
                                EC_SCRATCH(int32_t) = va_arg(__arg, int32_t);
                                __ec_printf_int(int32_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            default:
                                EC_SCRATCH(int64_t) = va_arg(__arg, int64_t);
                                __ec_printf_int(int64_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                        };
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_unsigned:
                    {
                        switch(__ec_printf_mtx_long_count)
                        {
                            case 0:
                                EC_SCRATCH(uint8_t) =
                                                    (uint8_t)va_arg(__arg, int);
                                __ec_printf_int(uint8_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 1:
                                EC_SCRATCH(uint16_t)
                                                 = (uint16_t)va_arg(__arg, int);
                                __ec_printf_int(uint16_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 2:
                                EC_SCRATCH(uint32_t) = va_arg(__arg, uint32_t);
                                __ec_printf_int(uint32_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            default:
                                EC_SCRATCH(uint64_t) = va_arg(__arg, uint64_t);
                                __ec_printf_int(uint64_t, 10, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                        };
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_octal:
                    {
                        switch(__ec_printf_mtx_long_count)
                        {
                            case 0:
                                EC_SCRATCH(uint8_t) =
                                                    (uint8_t)va_arg(__arg, int);
                                __ec_printf_int(uint8_t, 8, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 1:
                                EC_SCRATCH(uint16_t)
                                                 = (uint16_t)va_arg(__arg, int);
                                __ec_printf_int(uint16_t, 8, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 2:
                                EC_SCRATCH(uint32_t) = va_arg(__arg, uint32_t);
                                __ec_printf_int(uint32_t, 8, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            default:
                                EC_SCRATCH(uint64_t) = va_arg(__arg, uint64_t);
                                __ec_printf_int(uint64_t, 8, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                        };
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_hexa_Cap:
                    {
                        switch(__ec_printf_mtx_long_count)
                        {
                            case 0:
                                EC_SCRATCH(uint8_t) =
                                                    (uint8_t)va_arg(__arg, int);
                                __ec_printf_int(uint8_t, 16, 1);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 1:
                                EC_SCRATCH(uint16_t)
                                                 = (uint16_t)va_arg(__arg, int);
                                __ec_printf_int(uint16_t, 16, 1);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 2:
                                EC_SCRATCH(uint32_t) = va_arg(__arg, uint32_t);
                                __ec_printf_int(uint32_t, 16, 1);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            default:
                                EC_SCRATCH(uint64_t) = va_arg(__arg, uint64_t);
                                __ec_printf_int(uint64_t, 16, 1);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                        };
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_hexa_Lower:
                    {
                        switch(__ec_printf_mtx_long_count)
                        {
                            case 0:
                                EC_SCRATCH(uint8_t) =
                                                    (uint8_t)va_arg(__arg, int);
                                __ec_printf_int(uint8_t, 16, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 1:
                                EC_SCRATCH(uint16_t)
                                                 = (uint16_t)va_arg(__arg, int);
                                __ec_printf_int(uint16_t, 16, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            case 2:
                                EC_SCRATCH(uint32_t) = va_arg(__arg, uint32_t);
                                __ec_printf_int(uint32_t, 16, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                            default:
                                EC_SCRATCH(uint64_t) = va_arg(__arg, uint64_t);
                                __ec_printf_int(uint64_t, 16, 0);
                                EC_PRINTF_GO_TO_RAW_FORMAT();
                                continue;
                        };
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_string_1:
                    case glibc_printf_form_string_2:
                    {
                        EC_SCRATCH(char *) = va_arg(__arg, char *);
                        __ec_printf_string();
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_size_t_1:
                    case glibc_printf_form_size_t_2:
                    case glibc_printf_form_pointer:
                    case glibc_printf_mod_ptrdiff_t:
                    {
                        EC_SCRATCH(uint64_t) = va_arg(__arg, uint64_t);
                        __ec_printf_int(uint64_t, 10, 1);
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }
                    case glibc_printf_form_float_E:
                    case glibc_printf_form_float_e:
                    case glibc_printf_form_float_F:
                    case glibc_printf_form_float_f:
                    case glibc_printf_form_float_G:
                    case glibc_printf_form_float_g:
                    {
                        EC_SCRATCH(double) = va_arg(__arg, double);
                        __ec_printf_double();
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        continue;
                    }

                    #ifdef EC_API_EXPERIMENTAL_PRINTF_API
                    /* The dot */
                    case glibc_printf_precision:
                        break;

                    /* Signs */
                    case glibc_printf_form_unknown_plus:
                        break;
                    case glibc_printf_form_unknown_minus:
                        break;

                    /* Digits */
                    case glibc_printf_form_unknown_0:
                        break;
                    case glibc_printf_form_unknown_1:
                        break;
                    case glibc_printf_form_unknown_2:
                        break;
                    case glibc_printf_form_unknown_3:
                        break;
                    case glibc_printf_form_unknown_4:
                        break;
                    case glibc_printf_form_unknown_5:
                        break;
                    case glibc_printf_form_unknown_6:
                        break;
                    case glibc_printf_form_unknown_7:
                        break;
                    case glibc_printf_form_unknown_8:
                        break;
                    case glibc_printf_form_unknown_9:
                        break;
                    #endif

                    /* Unknown section */
                    case glibc_printf_form_unknown_asteric:
                    case glibc_printf_form_unknown_star:
                    case glibc_printf_form_unknown_space:
                    case glibc_printf_form_unknown_I:
                    case glibc_printf_form_floathex_Cap:
                    case glibc_printf_form_float_hex_Lower:
                    case glibc_printf_form_strerror:
                    case glibc_printf_mod_intmax_t:
                    case glibc_printf_form_wcharacter:
                    case glibc_printf_form_number:
                    case glibc_printf_free_character_01:
                    case glibc_printf_free_character_02:
                    case glibc_printf_free_character_03:
                    case glibc_printf_free_character_04:
                    case glibc_printf_free_character_05:
                    case glibc_printf_free_character_06:
                    case glibc_printf_free_character_07:
                    case glibc_printf_free_character_08:
                    case glibc_printf_free_character_09:
                    case glibc_printf_free_character_10:
                    case glibc_printf_free_character_11:
                    case glibc_printf_free_character_12:
                    case glibc_printf_free_character_13:
                    case glibc_printf_free_character_14:
                    case glibc_printf_free_character_15:
                    case glibc_printf_free_character_16:
                    case glibc_printf_free_character_17:
                    case glibc_printf_free_character_18:
                    case glibc_printf_free_character_19:
                    case glibc_printf_free_character_20:
                    case glibc_printf_free_character_21:
                    case glibc_printf_free_character_22:
                    case glibc_printf_free_character_24:
                    case glibc_printf_free_character_25:
                    case glibc_printf_free_character_26:
                    case glibc_printf_free_character_28:
                    case glibc_printf_free_character_30:
                    case glibc_printf_free_character_31:
                    case glibc_printf_free_character_32:
                    case glibc_printf_free_character_33:
                    case glibc_printf_free_character_34:
                    case glibc_printf_free_character_35:
                    case glibc_printf_free_character_36:
                    case glibc_printf_free_character_37:
                    case glibc_printf_free_character_38:
                    case glibc_printf_free_character_39:
                    case glibc_printf_free_character_40:
                    default:
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        break;
                }
                break;
            }
            case __format_ecio:
            {
                switch ((*__format))
                {
                    /* Toggle upper case mode */
                    case eclibc_printf_upper_case:
                        break;

                    /* Format characters */
                    case eclibc_printf_time_seconds:
                        break;
                    case eclibc_printf_Time_struct_tm:
                        break;
                    case eclibc_printf_time_seconds_short:
                        break;
                    case eclibc_printf_time_struct_tm_short:
                        break;
                    case eclibc_printf_date_2digit:
                        break;
                    case eclibc_printf_date_4digit:
                        break;
                    case eclibc_printf_utc_time:
                        break;
                    case eclibc_printf_base_2:
                        break;
                    case eclibc_printf_base_8:
                        break;
                    case eclibc_printf_base_16:
                        break;
                    case eclibc_printf_bool:
                        break;
                    case eclibc_printf_utf8:
                        break;
                    case eclibc_printf_phone_number:
                        break;
                    case eclibc_printf_IPv4_Address:
                        break;
                    case eclibc_printf_IPv6_Address:
                        break;
                    case eclibc_printf_MAC_PC_Version:
                        break;
                    case eclibc_printf_MAC_CISCO:
                        break;

                    #ifdef EC_API_EXPERIMENTAL_PRINTF_API
                    /* The dot */
                    case eclibc_printf_precision:
                        break;

                    /* Signs */
                    case eclibc_printf_form_unknown_plus:
                        break;
                    case eclibc_printf_form_unknown_minus:
                        break;

                    /* Digits */
                    case eclibc_printf_form_unknown_0:
                        break;
                    case eclibc_printf_form_unknown_1:
                        break;
                    case eclibc_printf_form_unknown_2:
                        break;
                    case eclibc_printf_form_unknown_3:
                        break;
                    case eclibc_printf_form_unknown_4:
                        break;
                    case eclibc_printf_form_unknown_5:
                        break;
                    case eclibc_printf_form_unknown_6:
                        break;
                    case eclibc_printf_form_unknown_7:
                        break;
                    case eclibc_printf_form_unknown_8:
                        break;
                    case eclibc_printf_form_unknown_9:
                        break;
                    #endif

                    /* Wrong formating, leaving formating mode */
                    case eclibc_printf_form_unknown_star:
                    case eclibc_printf_custom_mode:
                    case eclibc_printf_form_unknown_space:
                    case eclibc_printf_form_unknown_asteric:
                    default:
                        EC_PRINTF_GO_TO_RAW_FORMAT();
                        break;
                };
                break;
            }
            case __format_raw:
            {
                if(*__format == '%')
                {
                    format_type = __format_std;
                    __ec_printf_mtx_leftNumber = 0;
                    __ec_printf_mtx_rightNumber = 0;
                    __ec_printf_mtx_Number_set = 0;
                    __ec_printf_mtx_side_right = false;
                    __ec_printf_mtx_Number_negative = 0;
                    __ec_printf_mtx_long_count = 1;
                    if(*(__format + 1) == '+')
                        __ec_printf_mtx_show_sign = 1;
                    else
                        __ec_printf_mtx_show_sign = 0;
                    if(__format != __ec_printf_mtx_temp_buffer_tail)
                        ec_fwrite(__ec_printf_mtx_temp_buffer_tail, (__format -
                                       __ec_printf_mtx_temp_buffer_tail), __stream);
                }
                /*else
                    ec_fputc(*__format, __stream);*/
                break;
            }
        };
    }
    ec_fputs(__ec_printf_mtx_temp_buffer_tail, __stream);
}

#undef EC_SCRATCH
#undef __ec_printf_int
#undef __ec_printf_double
#undef __ec_printf_string
#undef __ec_printf_add_digit
#undef EC_PRINTF_GO_TO_RAW_FORMAT

__attribute__((hot,noinline))
void
ec_fprintf_mtx(FILE *__restrict __stream, const char *__restrict __format, ...)
{
    va_list argptr;
    va_start(argptr, __format);
    ec_vfprintf(__stream, __format, argptr);
    va_end(argptr);
}

__attribute__((hot,noinline))
void
ec_vprintf_mtx(const char *__restrict __format, va_list __arg)
{
    ec_vfprintf(stdout, __format, __arg);
}

__attribute__((hot,noinline))
void
ec_printf_mtx(const char *__restrict __format, ...)
{
    va_list argptr;
    va_start(argptr, __format);
    ec_vfprintf(stdout, __format, argptr);
    va_end(argptr);
}

#ifdef __cplusplus
}
#endif

#else

typedef int DUMMY_TYPEDEF_TO_AVOID_PEDANTIC_ERROR;

#endif
