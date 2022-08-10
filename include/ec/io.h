/* <io.h> -*- C -*- */
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

#ifndef ECLIBC_IO_H
#define ECLIBC_IO_H 1

#include <stdarg.h>
#include <ec/vector.h>
#include <ec/internal/vprintf_internal.h>

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

#define ec_fputc(_ch, _fp) fputc(_ch, _fp)

#define ec_fputs(_ch, _fp) fputs(_ch, _fp)

#define ec_fwrite(_ptr, _len, _fp)   fwrite(_ptr, 1, (size_t)_len, _fp)

#ifdef __glibc_unlikely
/* Macro taken from the glibc headers. Put here to unify the macro accross    *
 * different compilers and different platforms.                               */
#define ec_putc_unlocked(_ch, _fp)                                             \
  (!((_fp)->_IO_write_ptr >= (_fp)->_IO_write_end)                             \
   ? __overflow (_fp, (unsigned char) (_ch))                                   \
   : (unsigned char) (*(_fp)->_IO_write_ptr++ = (_ch)))
#else
#define ec_putc_unlocked(_ch, _fp) putc(_ch, _fp)
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
void ec_popen(char *command, char *respond, size_t respond_size);

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
int ec_int_popen(char *command);

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
double ec_double_popen(char *command);

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
 *              ec_printf("%s\r\n", ec_api_vector_iterator_pointer(char, itr));
 *
 *          // delete the vector when we are done with it.
 *          ec_api_vector_delete(respond_list);
 */
void ec_popen_multi_line(char *command, ec_api_vector **respond_vector,
                                                       size_t max_respond_size);
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
void ec_io_get_terminal_name(char *ptr, size_t pointer_size);

/**
 * @brief ec_io_get_terminal_PID    Gets the process ID of the host terminal.
 * @return                          The process ID of the host terminal.
 */
int ec_io_get_terminal_PID();

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
int ec_io_get_terminal_rows_count();

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
int ec_io_get_terminal_columns_count();

#endif

/**
 * @brief ec_io_flush_stdout    Just a wrapper around the standard fflush
 *                              function.
 */
void ec_io_flush_stdout();

/**
 * @brief ec_io_flush_stderr    Just a wrapper around the standard fflush
 *                              function.
 */
void ec_io_flush_stderr();

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
void ec_io_vprintf_instant(const char *__restrict format, va_list argptr);

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
void ec_io_printf_instant(const char* format, ...);

/**
 * @brief ec_io_gotoxy         Moves the cursor to the given point.
 * @warning                    This function only works on terminals that
 *                             support ansi escape sequences.
 * @param x                    The desired column number to move the curstor to.
 * @param y                    The desired row number to move the curstor to.
 * @warning                    Since this function uses fflush, it will affect
 *                             the buffering and slow it down. So, the usage of
 *                             this function is highly descouraged. As an
 *                             alternative, you can pass the ansi escape
 *                             sequence directly to the printf in middle of a
 *                             format string.
 */
void ec_io_gotoxy(int x, int y);

/**
 * @brief ec_io_clear_screen   Clears the terminal, but doesn't move the cursor.
 * @warning                    This function only works on terminals that
 *                             support ansi escape sequences.
 * @warning                    Since this function uses fflush, it will affect
 *                             the buffering and slow it down. So, the usage of
 *                             this function is highly descouraged. As an
 *                             alternative, you can pass the ansi escape
 *                             sequence directly to the printf in middle of a
 *                             format string.
 */
void ec_io_clear_screen();

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
void ec_io_cursor_save();

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
void ec_io_cursor_restore();

#ifdef __cplusplus
}
#endif

#endif
