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


#ifdef __cplusplus
}
#endif
