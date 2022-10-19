/* <vurlprintf_internal.c> -*- C -*- */
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

#include <ec/internal/text_parse/printf_format.h>
#include <ec/internal/text_parse/itoa.h>
#include <ec/internal/text_parse/ftoa.h>
#include <ec/internal/print_format_table.h>
#include <ec/internal/vurlprintf_internal.h>
#include <ec/internal/urlpad_string.h>
#include <ec/internal/pad_string.h>
#include <ec/types.h>
#include <ec/utf8.h>
#include <ec/time.h>
#include <errno.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define __ec_sprintf_int(_type, _base, _upperCase)                             \
    {                                                                          \
        __ec_printf_numBuffer = ec_itoa_##_type (EC_SCRATCH_1(_type),          \
                        __ec_printf_numBuffer_End, _base, _upperCase);         \
        ec_urlfpad_string(__s, __ec_printf_numBuffer);                         \
    }

#define __ec_sprintf_string()                                                  \
    {                                                                          \
        ec_urlfpad_string(__s, EC_SCRATCH_1(char *));                          \
    }

#define __ec_sprintf_double()                                                  \
    {                                                                          \
        __ec_printf_numBuffer = ec_ftoa(EC_SCRATCH_1(double),                  \
                                         __ec_printf_numBuffer_End,            \
                                                     __ec_args->NumberRight);  \
        ec_urlfpad_string(__s, __ec_printf_numBuffer);                         \
    }

#define __ec_sprintf_digits(value, digitsCount)                                \
    {                                                                          \
        __ec_printf_numBuffer = ec_itoa_uint64_t ((uint64_t)value,             \
                        __ec_printf_numBuffer_End, 10, 0);                     \
        ec_urlfpad_string(__s, __ec_printf_numBuffer);                         \
    }

static inline bool
__attribute__ ((hot,unused,always_inline))
__ec_urlprintf_perform(char *__restrict __s,
                          __ec_printf_args *__restrict __ec_args, va_list __arg)
{
    /* as much to satisfy a 64 bit binary and more */
    char NumBuffer_Storage[81];
    struct tm __ec_scratch_memory;
    char * __restrict __ec_printf_numBuffer_End = NumBuffer_Storage + 80;
    char * __restrict __ec_printf_numBuffer;
    *__ec_printf_numBuffer_End = '\0';
    #define EC_SCRATCH_1(type) *((type *)(&__ec_scratch_memory))
    /*
    #define EC_SCRATCH_2(type) *((type *)((&__ec_scratch_memory) + 8))
    */
    if(__ec_args->is_ec_format == 0)
    {
        switch(__ec_args->format_chr)
        {
            case glibc_printf_form_float_E:
            case glibc_printf_form_float_e:
            case glibc_printf_form_float_F:
            case glibc_printf_form_float_f:
            case glibc_printf_form_float_G:
            case glibc_printf_form_float_g:
            {
                if((__ec_args->NumSeen & 2) == 0)
                    __ec_args->NumberRight = 6;
                EC_SCRATCH_1(double) = va_arg(__arg, double);
                __ec_sprintf_double();
                return true;
            }

            case glibc_printf_form_percent:
                strcat(__s, "%25");
                return true;

            case glibc_printf_form_character:
            {
                ec_urlpad_character(__s, (char)(va_arg(__arg, int)));
                return true;
            }

            case glibc_printf_form_strerror:
            {
                EC_SCRATCH_1(char *) = strerror(errno);
                __ec_sprintf_string();
                return true;
            }

            case glibc_printf_form_string_1:
            case glibc_printf_form_string_2:
            {
                EC_SCRATCH_1(char *) = va_arg(__arg, char *);
                __ec_sprintf_string();
                return true;
            }

            case glibc_printf_form_integer_1:
            case glibc_printf_form_integer_2:
            {
                switch(__ec_args->Size)
                {
                    case 0:
                        EC_SCRATCH_1(int8_t) = (int8_t)va_arg(__arg, int);
                        __ec_sprintf_int(int8_t, 10, 0);
                        return true;
                    case 1:
                        EC_SCRATCH_1(int16_t)
                                          = (int16_t)va_arg(__arg, int);
                        __ec_sprintf_int(int16_t, 10, 0);
                        return true;
                    case 2:
                        EC_SCRATCH_1(int32_t) = va_arg(__arg, int32_t);
                        __ec_sprintf_int(int32_t, 10, 0);
                        return true;
                    default:
                        EC_SCRATCH_1(int64_t) = va_arg(__arg, int64_t);
                        __ec_sprintf_int(int64_t, 10, 0);
                        return true;
                };
                return true;
            }

            case glibc_printf_form_size_t_1:
            case glibc_printf_form_size_t_2:
            case glibc_printf_form_pointer:
            case glibc_printf_mod_ptrdiff_t:
            {
                EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                if(EC_SCRATCH_1(int) == 0)
                    ec_urlpad_len_str(__s, "False");
                else
                    ec_urlpad_len_str(__s, "True");
                return true;
            }

            case glibc_printf_form_unsigned:
            {
                switch(__ec_args->Size)
                {
                    case 0:
                        EC_SCRATCH_1(uint8_t) = (uint8_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint8_t, 10, 0);
                        return true;
                    case 1:
                        EC_SCRATCH_1(uint16_t)
                                          = (uint16_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint16_t, 10, 0);
                        return true;
                    case 2:
                        EC_SCRATCH_1(uint32_t) = va_arg(__arg, uint32_t);
                        __ec_sprintf_int(uint32_t, 10, 0);
                        return true;
                    default:
                        EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                        __ec_sprintf_int(uint64_t, 10, 0);
                        return true;
                };
                return true;
            }

            case glibc_printf_form_octal:
            {
                switch(__ec_args->Size)
                {
                    case 0:
                        EC_SCRATCH_1(uint8_t) = (uint8_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint8_t, 8, 0);
                        return true;
                    case 1:
                        EC_SCRATCH_1(uint16_t)
                                          = (uint16_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint16_t, 8, 0);
                        return true;
                    case 2:
                        EC_SCRATCH_1(uint32_t) = va_arg(__arg, uint32_t);
                        __ec_sprintf_int(uint32_t, 8, 0);
                        return true;
                    default:
                        EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                        __ec_sprintf_int(uint64_t, 8, 0);
                        return true;
                };
                return true;
            }

            case glibc_printf_form_hexa_Cap:
            case glibc_printf_form_hexa_Lower:
            {
                switch(__ec_args->Size)
                {
                    case 0:
                        EC_SCRATCH_1(uint8_t) = (uint8_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint8_t, 16, (__ec_args->format_chr
                                        == glibc_printf_form_hexa_Cap) ? 1 : 0);
                        return true;
                    case 1:
                        EC_SCRATCH_1(uint16_t)
                                          = (uint16_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint16_t, 16, (__ec_args->format_chr
                                        == glibc_printf_form_hexa_Cap) ? 1 : 0);
                        return true;
                    case 2:
                        EC_SCRATCH_1(uint32_t) = va_arg(__arg, uint32_t);
                        __ec_sprintf_int(uint32_t, 16, (__ec_args->format_chr
                                        == glibc_printf_form_hexa_Cap) ? 1 : 0);
                        return true;
                    default:
                        EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                        __ec_sprintf_int(uint64_t, 16, (__ec_args->format_chr
                                        == glibc_printf_form_hexa_Cap) ? 1 : 0);
                        return true;
                };
                return true;
            }


            default:
                return false;
        };
    }
    else
    {
        switch(__ec_args->format_chr)
        {
            case glibc_printf_form_percent:
                strcat(__s, "%");
                return true;

            case eclibc_printf_bool:
            {
                EC_SCRATCH_1(int) = va_arg(__arg, int);
                if(EC_SCRATCH_1(int) == 0)
                    ec_urlpad_len_str(__s, "False");
                else
                    ec_urlpad_len_str(__s, "True");
                return true;
            }

            case eclibc_printf_utf8:
            {
                char UTF8_temp[5];
                EC_SCRATCH_1(ec_utf8_t) = va_arg(__arg, ec_utf8_t);
                ea_utf8_decode(EC_SCRATCH_1(ec_utf8_t), UTF8_temp);
                ec_urlpad_len_str(__s, UTF8_temp);
                return true;
            }

            case eclibc_printf_phone_number:
            {
                char tempPhone[20];
                char *__restrict phoneHead = tempPhone + 19;
                if(__ec_args->NumberLeft < 1)
                    __ec_args->NumberLeft = 12;
                else if(__ec_args->NumberLeft > 19)
                    __ec_args->NumberLeft = 19;
                tempPhone[19] = '\0';
                EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                phoneHead = ec_itoa_uint64_t(EC_SCRATCH_1(uint64_t),
                                                              phoneHead, 10, 1);
                if(phoneHead < (tempPhone + 19 - __ec_args->NumberLeft))
                    phoneHead = (tempPhone + 19 - __ec_args->NumberLeft);
                strcat(__s, "+");
                ec_urlfpad_string(__s, phoneHead);
                return true;
            }

            case eclibc_printf_IPv4_Address:
            {
                char tempIP[17];
                char *__restrict IP_head = tempIP + 16;
                if(__ec_args->alternateForm)
                    (EC_SCRATCH_1(ec_ipv4_t)).IP = va_arg(__arg, uint32_t);
                else
                    (EC_SCRATCH_1(ec_ipv4_t))    = va_arg(__arg, ec_ipv4_t);
                tempIP[16] = '\0';
                #define __EC_PRINTF_READ_NUM(INDEX)                            \
                IP_head = ec_itoa_uint8_t(                                     \
                        (EC_SCRATCH_1(ec_ipv4_t)).display_string.byte##INDEX , \
                                IP_head, 10, 1);
                __EC_PRINTF_READ_NUM(4);
                *--IP_head = '.';
                __EC_PRINTF_READ_NUM(3);
                *--IP_head = '.';
                __EC_PRINTF_READ_NUM(2);
                *--IP_head = '.';
                __EC_PRINTF_READ_NUM(1);
                #undef __EC_PRINTF_READ_NUM
                ec_urlfpad_string(__s, IP_head);
                return true;
            }

            case eclibc_printf_IPv6_Address:
            {
                char tempIP[41];
                char *__restrict IP_head = tempIP + 40;
                (EC_SCRATCH_1(ec_ipv6_t)) = va_arg(__arg, ec_ipv6_t);
                tempIP[40] = '\0';
                #define __EC_PRINTF_READ_NUM(INDEX)                            \
                IP_head = ec_itoa_uint16_t(                                    \
                        (EC_SCRATCH_1(ec_ipv6_t)).display_string.byte##INDEX , \
                                IP_head, 16, __ec_args->alternateForm);
                __EC_PRINTF_READ_NUM(8); *--IP_head = ':';
                __EC_PRINTF_READ_NUM(7); *--IP_head = ':';
                __EC_PRINTF_READ_NUM(6); *--IP_head = ':';
                __EC_PRINTF_READ_NUM(5); *--IP_head = ':';
                __EC_PRINTF_READ_NUM(4); *--IP_head = ':';
                __EC_PRINTF_READ_NUM(3); *--IP_head = ':';
                __EC_PRINTF_READ_NUM(2); *--IP_head = ':';
                __EC_PRINTF_READ_NUM(1);
                #undef __EC_PRINTF_READ_NUM
                ec_urlfpad_string(__s, IP_head);
                return true;
            }

            case eclibc_printf_MAC_PC_Version:
            case eclibc_printf_MAC_PC_Version_caps:
            {
                char tempMAC[3];
                char *__restrict MAC_head;
                if(__ec_args->alternateForm)
                    (EC_SCRATCH_1(ec_mac_t)).MAC = va_arg(__arg, uint64_t);
                else
                    (EC_SCRATCH_1(ec_mac_t))     = va_arg(__arg, ec_mac_t);
                tempMAC[2] = '\0';
                #define __EC_PRINTF_PRINT_NUM(INDEX)                           \
                MAC_head = tempMAC + 2;                                        \
                MAC_head = ec_itoa_uint8_t(                                    \
                        (EC_SCRATCH_1(ec_mac_t)).display_string.byte##INDEX ,  \
                                MAC_head, 16, ((__ec_args->format_chr ==       \
                                 eclibc_printf_MAC_PC_Version_caps) ? 1 : 0)); \
                ec_urlfpad_string(__s, MAC_head);

                __EC_PRINTF_PRINT_NUM(1);
                strcat(__s, ":");
                __EC_PRINTF_PRINT_NUM(2);
                strcat(__s, ":");
                __EC_PRINTF_PRINT_NUM(3);
                strcat(__s, ":");
                __EC_PRINTF_PRINT_NUM(4);
                strcat(__s, ":");
                __EC_PRINTF_PRINT_NUM(5);
                strcat(__s, ":");
                __EC_PRINTF_PRINT_NUM(6);

                #undef __EC_PRINTF_PRINT_NUM
                return true;
            }

            case eclibc_printf_MAC_CISCO:
            case eclibc_printf_MAC_CISCO_caps:
            {
                char tempMAC[4];
                char *__restrict MAC_head;
                if(__ec_args->alternateForm)
                    (EC_SCRATCH_1(ec_mac_t)).MAC = va_arg(__arg, uint64_t);
                else
                    (EC_SCRATCH_1(ec_mac_t))     = va_arg(__arg, ec_mac_t);
                tempMAC[3] = '\0';
                #define __EC_PRINTF_PRINT_NUM(INDEX)                           \
                MAC_head = tempMAC + 3;                                        \
                MAC_head = ec_itoa_uint16_t(                                   \
                        (EC_SCRATCH_1(ec_mac_t)).cisco_string.byte##INDEX ,    \
                                MAC_head, 16, ((__ec_args->format_chr ==       \
                                      eclibc_printf_MAC_CISCO_caps) ? 1 : 0)); \
                ec_urlfpad_string(__s, MAC_head);

                __EC_PRINTF_PRINT_NUM(1);
                strcat(__s, ".");
                __EC_PRINTF_PRINT_NUM(2);
                strcat(__s, ".");
                __EC_PRINTF_PRINT_NUM(3);

                #undef __EC_PRINTF_PRINT_NUM
                return true;
            }

            case eclibc_printf_base_2:
            {
                switch(__ec_args->Size)
                {
                    case 0:
                        EC_SCRATCH_1(uint8_t) = (uint8_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint8_t, 2, 0);
                        return true;
                    case 1:
                        EC_SCRATCH_1(uint16_t)
                                          = (uint16_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint16_t, 2, 0);
                        return true;
                    case 2:
                        EC_SCRATCH_1(uint32_t) = va_arg(__arg, uint32_t);
                        __ec_sprintf_int(uint32_t, 2, 0);
                        return true;
                    default:
                        EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                        __ec_sprintf_int(uint64_t, 2, 0);
                        return true;
                };
                return true;
            }

            case eclibc_printf_base_8:
            {
                switch(__ec_args->Size)
                {
                    case 0:
                        EC_SCRATCH_1(uint8_t) = (uint8_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint8_t, 8, 0);
                        return true;
                    case 1:
                        EC_SCRATCH_1(uint16_t)
                                          = (uint16_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint16_t, 8, 0);
                        return true;
                    case 2:
                        EC_SCRATCH_1(uint32_t) = va_arg(__arg, uint32_t);
                        __ec_sprintf_int(uint32_t, 8, 0);
                        return true;
                    default:
                        EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                        __ec_sprintf_int(uint64_t, 8, 0);
                        return true;
                };
                return true;
            }

            case eclibc_printf_base_16:
            {
                switch(__ec_args->Size)
                {
                    case 0:
                        EC_SCRATCH_1(uint8_t) = (uint8_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint8_t, 16,
                                       (__ec_args->alternateForm == 1) ? 1 : 0);
                        return true;
                    case 1:
                        EC_SCRATCH_1(uint16_t)
                                          = (uint16_t)va_arg(__arg, int);
                        __ec_sprintf_int(uint16_t, 16,
                                       (__ec_args->alternateForm == 1) ? 1 : 0);
                        return true;
                    case 2:
                        EC_SCRATCH_1(uint32_t) = va_arg(__arg, uint32_t);
                        __ec_sprintf_int(uint32_t, 16,
                                       (__ec_args->alternateForm == 1) ? 1 : 0);
                        return true;
                    default:
                        EC_SCRATCH_1(uint64_t) = va_arg(__arg, uint64_t);
                        __ec_sprintf_int(uint64_t, 16,
                                       (__ec_args->alternateForm == 1) ? 1 : 0);
                        return true;
                };
                return true;
            }

            case eclibc_printf_time_seconds:
            case eclibc_printf_time_seconds_short:
            {
                char mode[4] = "";
                __ec_scratch_memory = va_arg(__arg, struct tm);
                if(__ec_args->alternateForm == 1)
                {
                    mode[0] = ' ';
                    mode[2] = 'M';
                    mode[3] = '\0';
                    if(__ec_scratch_memory.tm_hour > 12)
                    {
                        __ec_scratch_memory.tm_hour -= 12;
                        mode[1] = 'P';
                    }
                    else
                        mode[1] = 'A';
                }
                __ec_sprintf_digits(__ec_scratch_memory.tm_hour, 2);
                strcat(__s, ":");
                __ec_sprintf_digits(__ec_scratch_memory.tm_min, 2);
                if(__ec_args->format_chr == eclibc_printf_time_seconds)
                {
                    strcat(__s, ":");
                    __ec_sprintf_digits(__ec_scratch_memory.tm_sec, 2);
                }
                strcat(__s, mode);
                return true;
            }

            case eclibc_printf_Time_struct_tm:
            case eclibc_printf_time_struct_tm_short:
            {
                char mode[4] = "";
                uint32_t tempInt = va_arg(__arg, uint32_t);
                __ec_scratch_memory.tm_hour = (int)(tempInt / 3600);
                __ec_scratch_memory.tm_min  = (int)((tempInt % 3600) / 60);
                __ec_scratch_memory.tm_sec  = (int)(tempInt % 60);
                if(__ec_args->alternateForm == 1)
                {
                    mode[0] = ' ';
                    mode[2] = 'M';
                    mode[3] = '\0';
                    if(__ec_scratch_memory.tm_hour > 12)
                    {
                        __ec_scratch_memory.tm_hour -= 12;
                        mode[1] = 'P';
                    }
                    else
                        mode[1] = 'A';
                }
                __ec_sprintf_digits(__ec_scratch_memory.tm_hour, 2);
                strcat(__s, ":");
                __ec_sprintf_digits(__ec_scratch_memory.tm_min, 2);
                if(__ec_args->format_chr == eclibc_printf_Time_struct_tm)
                {
                    strcat(__s, ":");
                    __ec_sprintf_digits(__ec_scratch_memory.tm_sec, 2);
                }
                strcat(__s, mode);
                return true;
            }

            case eclibc_printf_date_2digit:
            case eclibc_printf_date_4digit:
            {
                __ec_scratch_memory = va_arg(__arg, struct tm);
                __ec_scratch_memory.tm_year += 1900;
                if(__ec_args->alternateForm == 1)
                {
                    strcat(__s, ec_month_name_str[__ec_scratch_memory.tm_mon]);
                    strcat(__s, " ");
                    __ec_sprintf_digits(__ec_scratch_memory.tm_mday, 2);
                    if(__ec_scratch_memory.tm_mday > 3 &&
                            __ec_scratch_memory.tm_mday <= 20)
                        strcat(__s, "th ");
                    else if(__ec_scratch_memory.tm_mday % 10 == 1)
                        strcat(__s, "st ");
                    else if(__ec_scratch_memory.tm_mday % 10 == 2)
                        strcat(__s, "nd ");
                    else
                        strcat(__s, "th ");
                    __ec_sprintf_digits(__ec_scratch_memory.tm_year,
                                         ((__ec_args->format_chr ==
                                               eclibc_printf_date_4digit)
                                                                      ? 4 : 2));
                }
                else
                {
                    __ec_sprintf_digits(__ec_scratch_memory.tm_mday, 2);
                    strcat(__s, "/");
                    __ec_sprintf_digits((__ec_scratch_memory.tm_mon + 1), 2);
                    strcat(__s, "/");
                    __ec_sprintf_digits(__ec_scratch_memory.tm_year,
                                         ((__ec_args->format_chr ==
                                               eclibc_printf_date_4digit)
                                                                      ? 4 : 2));
                }
                return true;
            }

            case eclibc_printf_utc_time:
            {
                __ec_scratch_memory = va_arg(__arg, struct tm);
                __ec_scratch_memory.tm_year += 1900;
                __ec_sprintf_digits(__ec_scratch_memory.tm_year, 4);
                strcat(__s, "-");
                __ec_sprintf_digits(__ec_scratch_memory.tm_mon, 2);
                strcat(__s, "-");
                __ec_sprintf_digits(__ec_scratch_memory.tm_mday, 2);
                strcat(__s, "T");
                __ec_sprintf_digits(__ec_scratch_memory.tm_hour, 2);
                strcat(__s, ":");
                __ec_sprintf_digits(__ec_scratch_memory.tm_min, 2);
                strcat(__s, ":");
                __ec_sprintf_digits(__ec_scratch_memory.tm_sec, 2);
                strcat(__s, "Z");
                return true;
            }

            default:
                return false;
        }
    }
    #undef EC_SCRATCH_1
    #undef EC_SCRATCH_2
    return false;
}

__attribute__((hot,noinline))
int
ec_vurlprintf(char *__restrict __dst, const char *__restrict __src,
                                                                 va_list __arg)
{
    const char *__restrict __ec_printf_temp_buffer_tail = __src;
    const char *__restrict __ec_printf_temp_buffer;
    __attribute__((unused)) const char *__restrict __ec_printf_temp_buffer_temp;
    const char *__restrict __ec_printf_temp_buffer_end =
                                                    __src + strlen(__src);
    __ec_printf_args __ec_args;
    __dst[0] = '\0';
    while(*__ec_printf_temp_buffer_tail != '\0')
    {
        #ifdef __EC_VPRINTF_USE_STRCHR
        __ec_printf_temp_buffer = strchr(__ec_printf_temp_buffer_tail, '%');
        #else
        __ec_printf_temp_buffer = memchr(
                            (const void*)__ec_printf_temp_buffer_tail, (int)'%',
                                     (size_t)(__ec_printf_temp_buffer_end -
                                              __ec_printf_temp_buffer_tail) );
        #endif
        /* No formatting were found */
        if(__ec_printf_temp_buffer == EC_NULL ||
                __ec_printf_temp_buffer_end <= __ec_printf_temp_buffer)
        {
            strcat(__dst, __ec_printf_temp_buffer_tail);
            return ((int)(strlen(__dst)));
        }
        else
        {
            strncat (__dst, __ec_printf_temp_buffer_tail, (size_t)
                      (__ec_printf_temp_buffer - __ec_printf_temp_buffer_tail));

            __ec_printf_temp_buffer_temp =
                      __ec_printf_extract_format (__ec_printf_temp_buffer,
                                                             &__ec_args, __arg);

            if(__ec_urlprintf_perform(__dst, &__ec_args, __arg) == false)
                strncat (__dst, __ec_printf_temp_buffer, (size_t)
                      (__ec_printf_temp_buffer_temp - __ec_printf_temp_buffer));

            __ec_printf_temp_buffer_tail = __ec_printf_temp_buffer_temp;
        }
    }
    return ((int)(strlen(__dst)));
}

__attribute__((hot,noinline))
int
ec_urlprintf(char *__restrict __dst, const char *__restrict __src, ...)
{
    int result;
    va_list argptr;
    va_start(argptr, __src);
    result = ec_vurlprintf(__dst, __src, argptr);
    va_end(argptr);
    return result;
}

#ifdef __cplusplus
}
#endif
