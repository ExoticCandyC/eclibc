/* <printf.c> -*- C -*- */
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

#include <ec/printf.h>

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief ec_generate_progress_bar      Generate a progress bar with the given
 *                                      width, on the given progress count.
 *                                      Since some progress bars are generated
 *                                      using UTF characters, the characters
 *                                      of choice must be given in string
 *                                      format and NOT character format.
 *                                      If you are going for UTF characters,
 *                                      make sure you have enough space in the
 *                                      given pointer.
 * @param [out]ptr                      The pointer to hold the progress bar.
 * @param [in]progress                  Current progress, in percent. (0-100)
 * @param [in]width                     Width of the progress bar itself.
 * @param [in]character_empty           The character to be used for the empty
 *                                      space of the bar.
 * @param [in]character_filled          The character to be used for the filled
 *                                      space of the bar.
 * @example
 *      ec_generate_progress_bar(ptr, 20, 10, "-", "#")   =
 *              "##--------"
 *      ec_generate_progress_bar(ptr, 60, 15, "▱", "▰") =
 *              "▰▰▰▰▰▰▰▰▰▱▱▱▱▱▱"
 */
void ec_generate_progress_bar(char *ptr, double progress, int width,
                                 const char *character_empty,
                                 const char *character_filled)
{
    int index;
    int filledCount = (int)(width * (progress / (double)100));
    ptr[0] = '\0';
    for(index = 0; index < filledCount; index++)
        strcat(ptr, character_filled);
    for(; index < width; index++)
        strcat(ptr, character_empty);
}

#ifdef XC16
__ec_xc16_printf_handler_t __ec_xc16_stdout_handler = EC_NULL;
__ec_xc16_printf_handler_t __ec_xc16_stderr_handler = EC_NULL;

__ec_xc16_printf_handler_t *__ec_xc16_printf_handler =
                                        &__ec_xc16_stdout_handler;

/**
 * @brief ec_xc16_toggle_stderr     Switches from stdout to stderr and vice
 *                                  versa.
 * @param [in]state                 true:  stderr is selected
 *                                  false: stdout is selected
 */
void ec_xc16_toggle_stderr(bool state)
{
    if(state == true)
        __ec_xc16_printf_handler = &__ec_xc16_stderr_handler;
    else
        __ec_xc16_printf_handler = &__ec_xc16_stdout_handler;
}

/**
 * @brief ec_xc16_set_stdout_handler    This function is used to set the
 *                                      function used for stdout.
 * @param [in]handler                   The function that will handle the
 *                                      transmission of characters.
 */
void ec_xc16_set_stdout_handler(__ec_xc16_printf_handler_t handler)
{
    __ec_xc16_stdout_handler = handler;
}

/**
 * @brief ec_xc16_set_stderr_handler    This function is used to set the
 *                                      function used for stderr.
 * @param [in]handler                   The function that will handle the
 *                                      transmission of characters.
 */
void ec_xc16_set_stderr_handler(__ec_xc16_printf_handler_t handler)
{
    __ec_xc16_stderr_handler = handler;
}

/**
 * @brief write         This function remaps the stdout stream in XC16 compiler
 * @param [in]handle    internal file descriptor, not needed on XC16
 * @param [in]buffer    The buffer to be printed
 * @param [in]len       Buffer length
 * @return              Printed length
 */
int
__attribute__((__section__(".libc.write")))
    write(
__attribute__((unused)) int handle,
        void *buffer, unsigned int len)
{
    unsigned int i;

    for (i = len; i; --i)
    {
        if((*__ec_xc16_printf_handler) != EC_NULL)
            (*__ec_xc16_printf_handler)(*(uint8_t *)buffer++);
    }
    return ((int)len);
}
#endif

#ifdef __cplusplus
}
#endif
