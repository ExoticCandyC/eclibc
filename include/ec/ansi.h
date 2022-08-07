/* <ansi.h> -*- C -*- */
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

#include <sys/cdefs.h>
#ifdef __linux__
#include <stdio.h>
#include <signal.h>
#endif

#include <stdint.h>
#include <ec/printf.h>

#ifndef ECLIBC_ANSI_H
#define ECLIBC_ANSI_H 1

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
 * @def terminal_echo_off()     disables the linux terminal's input echo
 */
#define terminal_echo_off() system("stty -echo");

/**
 * @def terminal_echo_on()      enables the linux terminal's input echo
 */
#define terminal_echo_on()  system("stty sane");

/**
 * @brief ____dummy_sig_int_handler   a handler used to disable sig-int
 * @param sig_num                     signal code, SIGINT in sig-int case.
 */
#ifndef ____DUMMY_SIG_INIT_HANDLER
#define ____DUMMY_SIG_INIT_HANDLER
 __attribute__((weak  )) void ____dummy_sig_int_handler
(__attribute__((unused)) int  sig_num)
        { signal(SIGINT, ____dummy_sig_int_handler); }
#endif

/**
* @def terminal_echo_on()      enables the linux terminal's input echo
*/
#define terminal_sigint_turn_on()    signal(SIGINT, NULL)

/**
* @def terminal_echo_on()      disables the linux terminal's input echo
*/
#define terminal_sigint_turn_off()   signal(SIGINT, ____dummy_sig_int_handler)

#endif

/**
 * @def cursor_invisible()
 * @brief   the ansi sequence used to make the cursor invisible.
 */
#define cursor_invisible()           "\x1B[?25l"

/**
 * @def cursor_visible()
 * @brief   the ansi sequence used to make the cursor visible.
 */
#define cursor_visible()             "\x1B[?25h"

/**
 * @def cursor_goto(x, y)
 * @brief   moves the cursor to the given point. Note that this macro only
 *          accepts constant values, and should be used as a part of the printf
 *          format string.
 */
#define cursor_goto(x, y)            "\033[" #y ";" #x "H"

/**
 * @def cursor_goto_variable()
 * @brief   used to move the cursor, using variables instead of constant values
 *          it is used on the format part of the printf, and should be
 *          accompanied by "cursor_goto_expand(x, y)" to define the X and Y of
 *          the target.
 */
#define cursor_goto_variable()       "\033[" printf_uint8(1,1) ";" \
                                             printf_uint8(1,1) "H"

/**
 * @def cursor_goto_expand(x, y)
 * @brief   expands the given variables to be used in the arguments section of
 *          the printf function, to set the values for "cursor_goto_variable()"
 */
#define cursor_goto_expand(x, y)     (uint8_t)y, (uint8_t)x

/**
 * @def cursor_move_up(N)
 * @brief   Generates the ansi escape sequence required to move the cursor up
 *          bu N lines. N must be a constant value.
 */
#define cursor_move_up(N)            "\033[" #N "A"

/**
 * @def cursor_move_down(N)
 * @brief   Generates the ansi escape sequence required to move the cursor down
 *          bu N lines. N must be a constant value.
 */
#define cursor_move_down(N)          "\033[" #N "B"

/**
 * @def cursor_move_right(N)
 * @brief   Generates the ansi escape sequence required to move the cursor right
 *          bu N lines. N must be a constant value.
 */
#define cursor_move_right(N)         "\033[" #N "C"

/**
 * @def cursor_move_left(N)
 * @brief   Generates the ansi escape sequence required to move the cursor left
 *          bu N lines. N must be a constant value.
 */
#define cursor_move_left(N)          "\033[" #N "D"

/**
 * @def cursor_move_up_variable()
 * @brief   Generates the required format for the printf function to accept a
 *          uint8_t value to move the cursor up by that amount.
 */
#define cursor_move_up_variable()    "\033[" printf_uint8(1,1) "A"

/**
 * @def cursor_move_down_variable()
 * @brief   Generates the required format for the printf function to accept a
 *          uint8_t value to move the cursor down by that amount.
 */
#define cursor_move_down_variable()  "\033[" printf_uint8(1,1) "B"

/**
 * @def cursor_move_right_variable()
 * @brief   Generates the required format for the printf function to accept a
 *          uint8_t value to move the cursor right by that amount.
 */
#define cursor_move_right_variable() "\033[" printf_uint8(1,1) "C"

/**
 * @def cursor_move_left_variable()
 * @brief   Generates the required format for the printf function to accept a
 *          uint8_t value to move the cursor left by that amount.
 */
#define cursor_move_left_variable()  "\033[" printf_uint8(1,1) "D"

/**
 * @def clear_screen()
 * @brief   The ansi sequence to clear the screen. Note that it doesn't change
 *          the cursor position.
 */
#define clear_screen()               "\033[2J"

/**
 * @def cursor_home()
 * @brief   The character to move the cursor back to the begining of the line.
 */
#define cursor_home()                "\r"

/**
 * @def cursor_clear_line()
 * @brief   The ansi sequence to clear the current line.
 */
#define cursor_clear_line()          cursor_home() "\033[K"

/**
 * @def cursor_save()
 * @brief   The ansi sequence to save the current position of the cursor.
 */
#define cursor_save()                "\033[s"

/**
 * @def cursor_restore()
 * @brief   The ansi sequence to restore the saved position of the cursor.
 */
#define cursor_restore()             "\033[u"

/**
 * @def end_line()
 * @brief   Simply an endline string. "\r\n"
 */
#define end_line()                   cursor_home() "\n"

/**
 * @def new_line()
 * @brief   Simply an endline string. "\r\n"
 */
#define new_line()                   cursor_home() "\n"

/**
 * @def color_reset()
 * @brief   The escape sequence to reset all text decorations applied inside
 *          the terminal.
 */
#define color_reset()                "\x1B[0m"

/**
 * @def color_text_black()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_black()           "\x1B[30m"

/**
 * @def color_text_red()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_red()             "\x1B[31m"

/**
 * @def color_text_green()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_green()           "\x1B[32m"

/**
 * @def color_text_yellow()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_yellow()          "\x1B[33m"

/**
 * @def color_text_blue()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_blue()            "\x1B[34m"

/**
 * @def color_text_magenta()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_magenta()         "\x1B[35m"

/**
 * @def color_text_cyan()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_cyan()            "\x1B[36m"

/**
 * @def color_text_white()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_white()           "\x1B[37m"

/**
 * @def color_text_light_black()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_black()     "\x1B[90m"

/**
 * @def color_text_light_red()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_red()       "\x1B[91m"

/**
 * @def color_text_light_green()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_green()     "\x1B[92m"

/**
 * @def color_text_light_yellow()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_yellow()    "\x1B[93m"

/**
 * @def color_text_light_blue()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_blue()      "\x1B[94m"

/**
 * @def color_text_light_magenta()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_magenta()   "\x1B[95m"

/**
 * @def color_text_light_cyan()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_cyan()      "\x1B[96m"

/**
 * @def color_text_light_white()
 * @brief   The escape sequence to change the text color to the aforementioned
 *          color.
 */
#define color_text_light_white()     "\x1B[97m"

/**
 * @def color_bg_black()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_black()             "\x1B[100m"

/**
 * @def color_bg_red()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_red()               "\x1B[101m"

/**
 * @def color_bg_green()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_green()             "\x1B[102m"

/**
 * @def color_bg_yellow()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_yellow()            "\x1B[103m"

/**
 * @def color_bg_blue()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_blue()              "\x1B[104m"

/**
 * @def color_bg_magenta()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_magenta()           "\x1B[105m"

/**
 * @def color_bg_cyan()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_cyan()              "\x1B[106m"

/**
 * @def color_bg_white()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_white()             "\x1B[107m"

/**
 * @def color_bg_light_black()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_black()       "\x1B[40m"

/**
 * @def color_bg_light_red()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_red()         "\x1B[41m"

/**
 * @def color_bg_light_green()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_green()       "\x1B[42m"

/**
 * @def color_bg_light_yellow()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_yellow()      "\x1B[43m"

/**
 * @def color_bg_light_blue()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_blue()        "\x1B[44m"

/**
 * @def color_bg_light_magenta()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_magenta()     "\x1B[45m"

/**
 * @def color_bg_light_cyan()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_cyan()        "\x1B[46m"

/**
 * @def color_bg_light_white()
 * @brief   The escape sequence to change the background color to the
 *          aforementioned color.
 */
#define color_bg_light_white()       "\x1B[47m"

/**
 * @brief ansi_4bit_color_t     a description over a character array that is
 *                              long enough to hold an ansi 4 bit color
 *                              sequence.
 */
typedef char ansi_4bit_color_t[sizeof(color_text_magenta())];


#ifdef __cplusplus
}
#endif

#endif
