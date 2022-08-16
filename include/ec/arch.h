/* <arch.h> -*- C -*- */
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

#ifndef EC_ARCH

#if defined(XC8)
#   define EC_ARCH 8
#elif defined(XC16)
#   define EC_ARCH 16
#elif defined(XC32)
#   define EC_ARCH 32
#elif defined(__XC32)
#   define EC_ARCH 32
#elif defined(__MCUXPRESSO)
#   define EC_ARCH 16
#elif defined(IDF_VER)
#   define EC_ARCH 32
#elif defined(_WIN32)
#   if defined _WIN64
#       define EC_ARCH 64
#   elif defined(_WIN32)
#       define EC_ARCH 32
#   endif
#elif defined(__linux__)
#   if defined __i386__
#       define EC_ARCH 32
#   else
#       define EC_ARCH 64
#   endif
#endif

#endif
