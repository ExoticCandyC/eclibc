/* <io.c> -*- C -*- */
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

#include <stdio.h>
#include <string.h>

#include <ec/io.h>
#include <ec/printf.h>
#include <ec/vector.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__linux__) || defined(_WIN32)

/**
 * @brief ec_popen             A wrapper around standard popen function. It runs
 *                             the given command and puts the first line of the
 *                             response inside the given string pointer.
 * @param [in]command          The command to be run.
 * @param [out]respond         The pointer to the string to hold the response.
 * @param [int]respond_size    The maximum number of bytes the given pointer
 *                             can hold.
 */
void ec_popen(char *command, char *respond, size_t respond_size)
{
    FILE *fp;

    fp = popen(command, "r");

    if(fgets(respond, (int)respond_size, fp) == EC_NULL)
        return;

    pclose(fp);
}

/**
 * @brief ec_int_popen          A wrapper around standard popen function. It
 *                              runs the given command that is supposed to only
 *                              return an integer value. Then converts the
 *                              given respond to integer and returns the value.
 *                              If the respond is not an integer, the builtin
 *                              atoi function's behaviour is returning 0.
 * @param command               The command to be run.
 * @return                      The respond converted to integer.
 */
int ec_int_popen(char *command)
{
    /* max uint64 = 0xFFFFFFFFFFFFFFFF = 18446744073709551615 */
    /* A 64bit unsigned integer can take up to 21 characters  */
    char temp[25];
    ec_popen(command, temp, sizeof(temp));
    return atoi(temp);
}

/**
 * @brief ec_double_popen       A wrapper around standard popen function. It
 *                              runs the given command that is supposed to
 *                              return an integer value or a double value. Then
 *                              converts the given respond to double and
 *                              returns the value.
 *                              If the respond is not a valid number, the
 *                              builtin atof function's behavior is returning 0.
 * @param command               The command to be run.
 * @return                      The respond converted to double.
 */
double ec_double_popen(char *command)
{
    /* max integer stored in double = 9007199254740992 */
    /* A 64bit double can hold a 18 characters long integer. roughly
     * it can hold a 20~22 characters long floating value. */
    char temp[25];
    ec_popen(command, temp, sizeof(temp));
    return atof(temp);
}

/**
 * @brief ec_popen_multi_line   A wrapper around standard popen function. It
 *                              runs the givens command and puts all the
 *                              responds in the given vector.
 *                              Note that the end line character will be
 *                              removed at the end of each respond line.
 * @warning                     Like any other standard or eclibc C functions
 *                              this function assumes the user knows what they
 *                              are doing. A small value for max_respond_size
 *                              can and will end up in memory corruption.
 * @param command               The command to be run.
 * @param respond_vector        The POINTER to the vector that is supposed to
 *                              hold the reponses.
 * @param max_respond_size      The maximum number of bytes the user expect
 *                              each respond to have.
 * @example:
 *  The following example runs "ls -l" and prints all the output to the stdout
 *  buffer.
 *          // optional: define the maximum length of each answer
 *          size_t max_repond_length = 1024;
 *
 *          // create the target vector
 *          ec_api_vector_create(respond_list);
 *
 *          // create an iterator to be used inside the for loop.
 *          ec_api_vector_iterator itr;
 *
 *          // run the "ls -l" command and save the responds to the vector.
 *          ec_popen_multi_line("ls -l", &respond_list, max_repond_length);
 *
 *          // iterate through all the items inside the vector and print them.
 *          ec_api_vector_for_each(itr, respond_list)
 *              printf("%s\r\n", ec_api_vector_iterator_pointer(char, itr));
 *
 *          // delete the vector when we are done with it.
 *          ec_api_vector_delete(respond_list);
 */
void ec_popen_multi_line(char *command, ec_api_vector **respond_vector,
                                                        size_t max_respond_size)
{
    FILE *fp;
    char * ptr;
    char *respond = malloc(sizeof(char) * max_respond_size);
    fp = popen(command, "r");
    do
    {
        ptr = fgets(respond, (sizeof(char) * max_respond_size), fp);
        if(ptr != EC_NULL)
        {
            /* remove the new line from each repond line */
            *(respond + strlen(respond) - 1) = '\0';
            ec_api_vector_push_back(*respond_vector, char[max_respond_size],
                                                     respond, max_respond_size);
        }
    } while(ptr != EC_NULL);
    pclose(fp);
    free(respond);
}

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

/**
 * @brief ec_io_flush_stdout    Just a wrapper around the standard fflush
 *                              function.
 */
void ec_io_flush_stdout()
{
    fflush(stdout);
}

/**
 * @brief ec_io_flush_stderr    Just a wrapper around the standard fflush
 *                              function.
 */
void ec_io_flush_stderr()
{
    fflush(stderr);
}

/**
 * @brief ec_io_vprintf_instant     A wrapper around the standard vprintf, which
 *                                  flush the given content on the host terminal
 *                                  regardless of the OS's buffering policies.
 * @warning             This function should be avoided as much as possible,
 *                      since this function can and will lead to poor buffering
 *                      and the program's performance will greatly suffer.
 * @param [in]format    the format string to be passed onto the vprintf
 *                      function.
 * @param [in]argptr    the va_list, containing all the arguments needed by
 *                      vprintf to print the formatted string.
 */
void ec_io_vprintf_instant(const char *__restrict format, va_list argptr)
{
    vprintf(format, argptr);
    fflush(stdout);
}

/**
 * @brief ec_io_printf_instant  A wrapper around the standard vprintf, which
 *                              flush the given content on the host terminal
 *                              regardless of the OS's buffering policies.
 * @warning             This function should be avoided as much as possible,
 *                      since this function can and will lead to poor buffering
 *                      and the program's performance will greatly suffer.
 * @param [in]format    the format string to be passed onto the vprintf
 * @param [in]...       the extra arguments to be passed to the printf function.
 */
void ec_io_printf_instant(const char* format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    ec_io_vprintf_instant(format, argptr);
    va_end(argptr);
}

/**
 * @brief ec_io_gotoxy         Moves the cursor to the given point.
 * @warning                    This function only works on terminals that
 *                             support ansi escape sequences.
 * @param x                    The desired column number to move the curstor to.
 * @param y                    The desired row number to move the curstor to.
 */
void ec_io_gotoxy(int x, int y)
{
    ec_io_printf_instant("\033[" printf_int(1,1) ";" printf_int(1,1) "H", y, x);
}

/**
 * @brief ec_io_clear_screen   Clears the terminal, but doesn't move the cursor.
 * @warning                    This function only works on terminals that
 *                             support ansi escape sequences.
 */
void ec_io_clear_screen()
{
    ec_io_printf_instant("\033[2J");
}

/**
 * @brief ec_io_cursor_save    Saves the current position of cursor inside the
 *                             host terminal's buffer.
 * @warning                    This function only works on terminals that
 *                             support ansi escape sequences.
 * @warning                    Since this function uses fflush, it will affect
 *                             the buffering and slow it down. So, the usage of
 *                             this function is highly descouraged. As an
 *                             alternative, you can pass the ansi escape
 *                             sequence directly to the printf in middle of a
 *                             format string.
 */
void ec_io_cursor_save()
{
    ec_io_printf_instant("\033[s");
}

/**
 * @brief ec_io_cursor_restore Restores the save cursor position.
 * @warning                    This function only works on terminals that
 *                             support ansi escape sequences.
 * @warning                    Since this function uses fflush, it will affect
 *                             the buffering and slow it down. So, the usage of
 *                             this function is highly descouraged. As an
 *                             alternative, you can pass the ansi escape
 *                             sequence directly to the printf in middle of a
 *                             format string.
 */
void ec_io_cursor_restore()
{
    ec_io_printf_instant("\033[u");
}

#ifdef __cplusplus
}
#endif











