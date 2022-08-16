/* <earg_helper.h> -*- C -*- */
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

#ifndef ECLIBC_MACRO_EARG_HELPER_H
#define ECLIBC_MACRO_EARG_HELPER_H 1

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

#define __EC_COMPILER_OPTIMIZER_ARG_N(                                         \
  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9,  _10,                            \
 _11, _12, _13, _14, _15, _16, _17, _18, _19,  _20,                            \
 _21, _22, _23, _24, _25, _26, _27, _28, _29,  _30,                            \
 _31, _32, _33, _34, _35, _36, _37, _38, _39,  _40,                            \
 _41, _42, _43, _44, _45, _46, _47, _48, _49,  _50,                            \
 _51, _52, _53, _54, _55, _56, _57, _58, _59,  _60,                            \
 _61, _62, _63, _64, _65, _66, _67, _68, _69,  _70,                            \
 _71, _72, _73, _74, _75, _76, _77, _78, _79,  _80,                            \
 _81, _82, _83, _84, _85, _86, _87, _88, _89,  _90,                            \
 _91, _92, _93, _94, _95, _96, _97, _98, _99, _100,                            \
_101,_102,_103,_104,_105,_106,_107,_108,_109, _110, N, ...) N

#define __EC_COMPILER_OPTIMIZER_RSEQ_N()                                       \
110,109,108,107,106,105,104,103,102,101,100,                                   \
99,98,97,96,95,94,93,92,91,90,                                                 \
89,88,87,86,85,84,83,82,81,80,                                                 \
79,78,77,76,75,74,73,72,71,70,                                                 \
69,68,67,66,65,64,63,62,61,60,                                                 \
59,58,57,56,55,54,53,52,51,50,                                                 \
49,48,47,46,45,44,43,42,41,40,                                                 \
39,38,37,36,35,34,33,32,31,30,                                                 \
29,28,27,26,25,24,23,22,21,20,                                                 \
19,18,17,16,15,14,13,12,11,10,                                                 \
9,8,7,6,5,4,3,2,1,0

#define __EC_COMPILER_OPTIMIZER_COUNT(...)                                     \
            __EC_COMPILER_OPTIMIZER_ARG_N(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
