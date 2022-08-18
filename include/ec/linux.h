/* <linux.h> -*- C -*- */
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

#ifndef ECLIBC_LINUX_H
#define ECLIBC_LINUX_H 1

#include <stdlib.h>
#include <ec/types.h>

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
void
ec_io_get_terminal_name(char *ptr, size_t pointer_size);

/**
 * @brief ec_io_get_terminal_PID    Gets the process ID of the host terminal.
 * @return                          The process ID of the host terminal.
 */
int
ec_io_get_terminal_PID();

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
int
ec_io_get_terminal_rows_count();

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
int
ec_io_get_terminal_columns_count();

/**
 * @brief ec_current_directory      Gets the current user's name.
 * @param [out]ptr                  The pointer used to store the user name.
 * @param [in]ptr_size              The maximum number of bytes the pointer
 *                                  can hold.
 */
void
ec_find_username(char *ptr, size_t ptr_size);

/**
 * @brief ec_current_directory      Gets the computer's host name.
 * @param [out]ptr                  The pointer used to store the host name.
 * @param [in]ptr_size              The maximum number of bytes the pointer
 *                                  can hold.
 */
void
ec_find_hostname(char *ptr, size_t ptr_size);

/**
 * @brief ec_current_directory      Gets the current directory's path.
 * @param [out]ptr                  The pointer used to store the path.
 * @param [in]ptr_size              The maximum number of bytes the pointer
 *                                  can hold.
 */
void
ec_current_path(char *ptr, size_t ptr_size);

/**
 * @brief ec_current_directory      Gets the current directory name. User's
 *                                  home directory is represented as "~" and
 *                                  the root directory is represented as "/"
 * @param [out]ptr                  The pointer used to store the directory
 *                                  name.
 * @param [in]ptr_size              The maximum number of bytes the pointer
 *                                  can hold.
 */
void
ec_current_directory(char *ptr, size_t ptr_size);

/**
 * @brief ec_directory_writable     Checks if the current directory is
 *                                  writable by the current user or not.
 * @return                          True: Directory is writable.
 *                                  False: Directory is not writable.
 */
bool
ec_directory_writable();

/**
 * @brief ec_net_interface_name     Finds the Nth network interface name.
 *                                  It is worth mentioning that the interface
 *                                  #0 is the default interface used for
 *                                  networking.
 * @param [out]ptr                  The pointer to the string to store the
 *                                  interface name.
 * @param [in]ifIndex               The index of the target interface.
 * @return                          True if the queried interface existed.
 *                                  False otherwise.
 */
bool
ec_net_interface_name(char *ptr, int ifIndex);


/**
 * @brief ec_net_get_interface_ipv4     gets the IPv4 of the given network
 *                                      interface.
 * @param [in]ifName                    The target interface name.
 * @return                              The interface's IPv4 address.
 */
ec_ipv4_t ec_net_get_interface_ipv4(char *ifName);

/**
 * @brief ec_net_get_interface_ipv6     gets the Nth IPv6 of the given network
 *                                      interface.
 * @param [in]ifName                    The target interface name.
 * @param [in]ipIndex                   The IPv6 index.
 * @return                              The interface's Nth IPv6 address.
 */
ec_ipv6_t ec_net_get_interface_ipv6(char *ifName, int ipIndex);

#endif

#ifdef __cplusplus
}
#endif

#endif
