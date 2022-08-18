/* <linux.c> -*- C -*- */
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

#if !defined(_XOPEN_SOURCE) && !defined(XC16) && !defined(XC32)
#define _XOPEN_SOURCE
#endif

#include <ec/io.h>
#include <ec/linux.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __linux__

/**
 * @brief ec_io_get_terminal_name   Puts the value of $TERM in the given
 *                                  pointer. Note that this function only works
 *                                  on GNU Linux.
 * @param [out]ptr                  The pointer to the string that is going to
 *                                  hold the terminal name.
 * @param [in]pointer_size          The size of the string pointer passed to
 *                                  this function.
 */
void ec_io_get_terminal_name(char *ptr, size_t pointer_size)
{
    ec_popen("echo $TERM", ptr, pointer_size);
    *(ptr + strlen(ptr) - 1) = '\0';
}

/**
 * @brief ec_io_get_terminal_PID    Gets the process ID of the host terminal.
 * @return                          The process ID of the host terminal.
 */
int ec_io_get_terminal_PID()
{
    return ec_int_popen("echo $$");
}

/**
 * @brief ec_io_get_terminal_rows_count     Gets the number of rows the
 *                               host terminal can show at the current moment.
 * @warning     This value can be wrong in the first 10ms of running a program
 *              inside a newly invoked fullscreen terminal. For exampled:
 *              "gnome-terminal --full-screen -- program.out"
 *              Can get the gnome-terminal's default rows count instead of the
 *              actual rows count if this function is invoked as a program
 *              constructor.
 *              Generally speaking, this value becomes valid as soon as a buffer
 *              is printed, or almost always after 10ms of delays after running
 *              the terminal.
 * @return      The number of rows the host terminal has at the current moment.
 */
int ec_io_get_terminal_rows_count()
{
    return ec_int_popen("tput lines");
}

/**
 * @brief ec_io_get_terminal_columns_count    Gets the number of columns the
 *                               host terminal can show at the current moment.
 * @warning     This value can be wrong in the first 10ms of running a program
 *              inside a newly invoked fullscreen terminal. For exampled:
 *              "gnome-terminal --full-screen -- program.out"
 *              Can get the gnome-terminal's default columns count instead of
 *              the actual columns count if this function is invoked as a
 *              program constructor.
 *              Generally speaking, this value becomes valid as soon as a buffer
 *              is printed, or almost always after 10ms of delays after running
 *              the terminal.
 * @return      The number of columns the host terminal has at the current
 *              moment.
 */
int ec_io_get_terminal_columns_count()
{
    return ec_int_popen("tput cols");
}

#endif

#ifdef __cplusplus
}
#endif
