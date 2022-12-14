/* <digits.c> -*- C -*- */
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

/* Inclusion just to get compile messages for the inline functions inside the
 * file.                                                                      */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Lower-case digits.
 */
const char __ec_lower_digits[36]
        = "0123456789abcdefghijklmnopqrstuvwxyz";

/**
 * @brief Upper-case digits.
 */
const char __ec_upper_digits[36]
        = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

#ifdef __cplusplus
}
#endif
