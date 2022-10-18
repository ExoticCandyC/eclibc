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
#include <ec/string.h>

#ifdef __linux__

#include <netdb.h>
#include <ifaddrs.h>

#ifndef NI_NUMERICHOST
#define NI_NUMERICHOST 1
#endif

#ifndef NI_MAXHOST
#define NI_MAXHOST 1025
#endif

#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __linux__

/* Translate a socket address to a location and service name.
 *
 * This function is a possible cancellation point and therefore not
 * marked with __THROW.
 *
 * Defined in glibc.
 */
extern int getnameinfo (const struct sockaddr *__restrict __sa,
            socklen_t __salen, char *__restrict __host,
            socklen_t __hostlen, char *__restrict __serv,
            socklen_t __servlen, int __flags);

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

/**
 * @brief ec_current_directory      Gets the current user's name.
 * @param [out]ptr                  The pointer used to store the user name.
 * @param [in]ptr_size              The maximum number of bytes the pointer
 *                                  can hold.
 */
void
ec_find_username(char *ptr, size_t ptr_size)
{
    ec_popen("whoami", ptr, ptr_size);
    ptr[strlen(ptr) - 1] = '\0';
}

/**
 * @brief ec_current_directory      Gets the computer's host name.
 * @param [out]ptr                  The pointer used to store the host name.
 * @param [in]ptr_size              The maximum number of bytes the pointer
 *                                  can hold.
 */
void
ec_find_hostname(char *ptr, size_t ptr_size)
{
    ec_popen("uname -n", ptr, ptr_size);
    ptr[strlen(ptr) - 1] = '\0';
}

/**
 * @brief ec_current_directory      Gets the current directory's path.
 * @param [out]ptr                  The pointer used to store the path.
 * @param [in]ptr_size              The maximum number of bytes the pointer
 *                                  can hold.
 */
void
ec_current_path(char *ptr, size_t ptr_size)
{
    ec_popen("pwd", ptr, ptr_size);
    ptr[strlen(ptr) - 1] = '\0';
}

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
ec_current_directory(char *ptr, size_t ptr_size)
{
    char user[1024];
    char path[1024];

    ec_find_username(user, sizeof(user));
    ec_current_path(path, sizeof(path));

    ec_popen("echo \"${PWD##*/}\"", ptr, ptr_size);
    ptr[strlen(ptr) - 1] = '\0';
    if (ptr[0] == '\0')
    {
        ptr[0] = '/';
        ptr[1] = '\0';
    }

    if (strcmp(user, "root") == 0)
    {
        if (strcmp(path, "/root") == 0)
            strcpy(ptr, "~");
    }
    else
    {
        char *_ptr;
        _ptr = strstr(path, "/home");
        if (_ptr == path)
        {
            if (*(path + sizeof("/home") + strlen(user)) == '\0')
            {
                _ptr = strstr(path + sizeof("/home"), user);
                if (_ptr == (path + sizeof("/home")))
                    strcpy(ptr, "~");
            }
        }
    }
}

/**
 * @brief ec_directory_writable     Checks if the current directory is
 *                                  writable by the current user or not.
 * @return                          True: Directory is writable.
 *                                  False: Directory is not writable.
 */
bool
ec_directory_writable()
{
    char temp[10];
    ec_popen("if [ -w \"$(pwd)\" ]; then echo \"1\"; else echo \"0\"; fi",
             temp, sizeof(temp));
    if (temp[0] == '1')
        return true;
    return false;
}

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
ec_net_interface_name(char *ptr, int ifIndex)
{
    FILE *f;
    char line[100] , *p , *c;

    f = fopen("/proc/net/route" , "r");

    while(fgets(line , 100 , f))
    {
        p = strtok(line , " \t");
        c = strtok(NULL , " \t");

        if(p != NULL && c != NULL)
        {
            if(strcmp(c , "00000000") == 0)
            {
                if(ifIndex-- == 0)
                {
                    strcpy(ptr, p);
                    fclose(f);
                    return true;
                }
            }
        }
    }
    fclose(f);
    *ptr = '\0';
    return false;
}

/**
 * @brief ec_net_get_interface_ipv4     gets the IPv4 of the given network
 *                                      interface.
 * @param [in]ifName                    The target interface name.
 * @return                              The interface's IPv4 address.
 */
ec_ipv4_t ec_net_get_interface_ipv4(char *ifName)
{
    int fm = AF_INET;
    struct ifaddrs *ifaddr, *ifa;
    int family , s;
    char host[NI_MAXHOST];
    char *ptr;
    ec_ipv4_t result;
    result.IP = 0;

    if (getifaddrs(&ifaddr) == -1)
        return result;

    for (ifa = ifaddr; ifa != EC_NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == EC_NULL)
        {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        if(strcmp( ifa->ifa_name , ifName) == 0)
        {
            if (family == fm)
            {
                s = getnameinfo( ifa->ifa_addr,
                                 (family == AF_INET) ?
                                     sizeof(struct sockaddr_in) :
                                     sizeof(struct sockaddr_in6),
                                 host,
                                 NI_MAXHOST, EC_NULL, 0, NI_NUMERICHOST);
                if (s != 0)
                    break;

                #define __readToken(index)                                     \
                ptr = strtok(((index == 1) ? host : EC_NULL) , ".");           \
                result.display_string.byte##index =                            \
                                            (unsigned int)atoi(ptr) & 0xFF;
                __readToken(1);
                __readToken(2);
                __readToken(3);
                __readToken(4);
                #undef __readToken
            }
        }
    }

    freeifaddrs(ifaddr);
    return result;
}

/**
 * @brief ec_net_get_interface_ipv6     gets the Nth IPv6 of the given network
 *                                      interface.
 * @param [in]ifName                    The target interface name.
 * @param [in]ipIndex                   The IPv6 index.
 * @return                              The interface's Nth IPv6 address.
 */
ec_ipv6_t ec_net_get_interface_ipv6(char *ifName, int ipIndex)
{
    int fm = AF_INET6;
    struct ifaddrs *ifaddr, *ifa;
    int family , s;
    char host[NI_MAXHOST];
    char *ptr;
    ec_ipv6_t result;
    result._64bit.part1 = 0;
    result._64bit.part2 = 0;

    if (getifaddrs(&ifaddr) == -1)
        return result;

    for (ifa = ifaddr; ifa != EC_NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == EC_NULL)
        {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        if(strcmp( ifa->ifa_name , ifName) == 0)
        {
            if (family == fm)
            {
                s = getnameinfo( ifa->ifa_addr,
                                 (family == AF_INET) ?
                                     sizeof(struct sockaddr_in) :
                                     sizeof(struct sockaddr_in6),
                                 host,
                                 NI_MAXHOST, EC_NULL, 0, NI_NUMERICHOST);
                if (s != 0)
                    break;
                if(strchr(host, '%') != EC_NULL)
                    continue;

                #define __readToken(index)                                     \
                ptr = strtok(((index == 1) ? host : EC_NULL) , ":");           \
                result.display_string.byte##index =                            \
                        (unsigned int)strtol(ptr, EC_NULL, 16) & 0xFFFF;
                __readToken(1);
                __readToken(2);
                __readToken(3);
                __readToken(4);
                __readToken(5);
                __readToken(6);
                __readToken(7);
                __readToken(8);
                #undef __readToken

                if(ipIndex-- == 0)
                    break;
            }
        }
        result._64bit.part1 = 0;
        result._64bit.part2 = 0;
    }
    freeifaddrs(ifaddr);
    return result;
}

#endif

#ifdef __cplusplus
}
#endif
