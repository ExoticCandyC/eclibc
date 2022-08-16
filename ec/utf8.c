/* <utf8.c> -*- C -*- */
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

#include <ec/utf8.h>
#include <ec/arch.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Using a union to automatically do the decoding is the fastest (literally)
 * way to do a decoding and byte separation, since compiler does no unnecessary
 * instructions to shift bytes, fix the over-heads, calculate the overflows and
 * most importantly, when working on embeded systems, you are limited on the
 * resources, so, having the same RAM space doing 5 different things for you at
 * the same time is invaluable.
 * The only downside to using bit-field unions is that they dont support arrays
 * and it causes the code to be expanded, because you cant use loops to go
 * through the data.
 */
typedef union
{
    struct
    {
        int byte1 : 7;
        int : 13; /* Expanded cause int is 16bits in 16bit processors*/
        int : 12; /* Expanded cause int is 16bits in 16bit processors*/
    } size1;
    struct
    {
        unsigned int byte2 : 6;
        unsigned int byte1 : 5;
        unsigned int : 11; /* Expanded cause int is 16bits in 16bit processors*/
        unsigned int : 10; /* Expanded cause int is 16bits in 16bit processors*/
    } size2;
    struct
    {
        unsigned int byte3 : 6;
        unsigned int byte2 : 6;
        unsigned int byte1 : 4;
        unsigned int : 16;
    } size3;
    struct
    {
        unsigned int byte4 : 6;
        unsigned int byte3 : 6;
        unsigned int byte2 : 6;
        unsigned int byte1 : 3;
        unsigned int : 11;
    } size4;
    ec_utf8_t data;
} __utf_decoder;

/**
 * @brief ea_utf_get_byte   Gets the Nth byte used to print a UTF8 character
 * @param value             The UTF8 value to be decoded
 * @param index             The number of the byte that is being requested.
 * @return                  0 if the value doesn't expand to the given index,
 *                          and the appropriate character if it exists.
 */
char ea_utf8_get_byte(ec_utf8_t value, uint8_t index)
{
    __utf_decoder Template;
    Template.data = value;
    if(value < 0x0080)
    {
        if(index == 1)
            return (char)(Template.size1.byte1);
    }
    else if(value < 0x0800)
    {
        if(index == 1)
            return (char)(Template.size2.byte1 | 0xC0);
        if(index == 2)
            return (char)(Template.size2.byte2 | 0x80);
    }
    else if(value < 0x10000)
    {
        if(index == 1)
            return (char)(Template.size3.byte1 | 0xE0);
        if(index == 2)
            return (char)(Template.size3.byte2 | 0x80);
        if(index == 3)
            return (char)(Template.size3.byte3 | 0x80);
    }
    else
    {
        if(index == 1)
            return (char)(Template.size4.byte1 | 0xF0);
        if(index == 2)
            return (char)(Template.size4.byte2 | 0x80);
        if(index == 3)
            return (char)(Template.size4.byte3 | 0x80);
        if(index == 4)
            return (char)(Template.size4.byte4 | 0x80);
    }
    return (char)0;
}

/**
 * @brief ea_utf8_decode    Prints the given UTF8 character into the string
 *                          pointer passed to this function. This is the
 *                          recommended way of using UTF8 characters, compared
 *                          to "printf_utf8"
 * @param [in]value         The UTF8 value to be decoded
 * @param [out]pointer      The pointer to the target string to hold the
 *                          decoded string.
 */
void ea_utf8_decode  (ec_utf8_t value, char *pointer)
{
    uint8_t index;
    for(index = 0; index < 5; index++)
    {
        pointer[index] = (char)ea_utf8_get_byte(value, (uint8_t)(index + 1));
        if(pointer[index] == (char)0)
            break;
    }
}

#ifdef __cplusplus
}
#endif
