/* <printf_fix_optimizer.h> -*- C -*- */
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

#ifndef ECLIBC_INTERNAL_PRINTF_FIX_OPTIMIZER_H
#define ECLIBC_INTERNAL_PRINTF_FIX_OPTIMIZER_H 1

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

#define __ec_printf_func__3   __ec_printf_func__2
#define __ec_printf_func__4   __ec_printf_func__2
#define __ec_printf_func__5   __ec_printf_func__2
#define __ec_printf_func__6   __ec_printf_func__2
#define __ec_printf_func__7   __ec_printf_func__2
#define __ec_printf_func__8   __ec_printf_func__2
#define __ec_printf_func__9   __ec_printf_func__2
#define __ec_printf_func__10  __ec_printf_func__2
#define __ec_printf_func__11  __ec_printf_func__2
#define __ec_printf_func__12  __ec_printf_func__2
#define __ec_printf_func__13  __ec_printf_func__2
#define __ec_printf_func__14  __ec_printf_func__2
#define __ec_printf_func__15  __ec_printf_func__2
#define __ec_printf_func__16  __ec_printf_func__2
#define __ec_printf_func__17  __ec_printf_func__2
#define __ec_printf_func__18  __ec_printf_func__2
#define __ec_printf_func__19  __ec_printf_func__2
#define __ec_printf_func__20  __ec_printf_func__2
#define __ec_printf_func__21  __ec_printf_func__2
#define __ec_printf_func__22  __ec_printf_func__2
#define __ec_printf_func__23  __ec_printf_func__2
#define __ec_printf_func__24  __ec_printf_func__2
#define __ec_printf_func__25  __ec_printf_func__2
#define __ec_printf_func__26  __ec_printf_func__2
#define __ec_printf_func__27  __ec_printf_func__2
#define __ec_printf_func__28  __ec_printf_func__2
#define __ec_printf_func__29  __ec_printf_func__2
#define __ec_printf_func__20  __ec_printf_func__2
#define __ec_printf_func__21  __ec_printf_func__2
#define __ec_printf_func__22  __ec_printf_func__2
#define __ec_printf_func__23  __ec_printf_func__2
#define __ec_printf_func__24  __ec_printf_func__2
#define __ec_printf_func__25  __ec_printf_func__2
#define __ec_printf_func__26  __ec_printf_func__2
#define __ec_printf_func__27  __ec_printf_func__2
#define __ec_printf_func__28  __ec_printf_func__2
#define __ec_printf_func__29  __ec_printf_func__2
#define __ec_printf_func__40  __ec_printf_func__2
#define __ec_printf_func__41  __ec_printf_func__2
#define __ec_printf_func__42  __ec_printf_func__2
#define __ec_printf_func__43  __ec_printf_func__2
#define __ec_printf_func__44  __ec_printf_func__2
#define __ec_printf_func__45  __ec_printf_func__2
#define __ec_printf_func__46  __ec_printf_func__2
#define __ec_printf_func__47  __ec_printf_func__2
#define __ec_printf_func__48  __ec_printf_func__2
#define __ec_printf_func__49  __ec_printf_func__2
#define __ec_printf_func__50  __ec_printf_func__2
#define __ec_printf_func__51  __ec_printf_func__2
#define __ec_printf_func__52  __ec_printf_func__2
#define __ec_printf_func__53  __ec_printf_func__2
#define __ec_printf_func__54  __ec_printf_func__2
#define __ec_printf_func__55  __ec_printf_func__2
#define __ec_printf_func__56  __ec_printf_func__2
#define __ec_printf_func__57  __ec_printf_func__2
#define __ec_printf_func__58  __ec_printf_func__2
#define __ec_printf_func__59  __ec_printf_func__2
#define __ec_printf_func__60  __ec_printf_func__2
#define __ec_printf_func__61  __ec_printf_func__2
#define __ec_printf_func__62  __ec_printf_func__2
#define __ec_printf_func__63  __ec_printf_func__2
#define __ec_printf_func__64  __ec_printf_func__2
#define __ec_printf_func__65  __ec_printf_func__2
#define __ec_printf_func__66  __ec_printf_func__2
#define __ec_printf_func__67  __ec_printf_func__2
#define __ec_printf_func__68  __ec_printf_func__2
#define __ec_printf_func__69  __ec_printf_func__2
#define __ec_printf_func__70  __ec_printf_func__2
#define __ec_printf_func__71  __ec_printf_func__2
#define __ec_printf_func__72  __ec_printf_func__2
#define __ec_printf_func__73  __ec_printf_func__2
#define __ec_printf_func__74  __ec_printf_func__2
#define __ec_printf_func__75  __ec_printf_func__2
#define __ec_printf_func__76  __ec_printf_func__2
#define __ec_printf_func__77  __ec_printf_func__2
#define __ec_printf_func__78  __ec_printf_func__2
#define __ec_printf_func__79  __ec_printf_func__2
#define __ec_printf_func__80  __ec_printf_func__2
#define __ec_printf_func__81  __ec_printf_func__2
#define __ec_printf_func__82  __ec_printf_func__2
#define __ec_printf_func__83  __ec_printf_func__2
#define __ec_printf_func__84  __ec_printf_func__2
#define __ec_printf_func__85  __ec_printf_func__2
#define __ec_printf_func__86  __ec_printf_func__2
#define __ec_printf_func__87  __ec_printf_func__2
#define __ec_printf_func__88  __ec_printf_func__2
#define __ec_printf_func__89  __ec_printf_func__2
#define __ec_printf_func__90  __ec_printf_func__2
#define __ec_printf_func__91  __ec_printf_func__2
#define __ec_printf_func__92  __ec_printf_func__2
#define __ec_printf_func__93  __ec_printf_func__2
#define __ec_printf_func__94  __ec_printf_func__2
#define __ec_printf_func__95  __ec_printf_func__2
#define __ec_printf_func__96  __ec_printf_func__2
#define __ec_printf_func__97  __ec_printf_func__2
#define __ec_printf_func__98  __ec_printf_func__2
#define __ec_printf_func__99  __ec_printf_func__2
#define __ec_printf_func__100 __ec_printf_func__2
#define __ec_printf_func__101 __ec_printf_func__2
#define __ec_printf_func__102 __ec_printf_func__2
#define __ec_printf_func__103 __ec_printf_func__2
#define __ec_printf_func__104 __ec_printf_func__2
#define __ec_printf_func__105 __ec_printf_func__2
#define __ec_printf_func__106 __ec_printf_func__2
#define __ec_printf_func__107 __ec_printf_func__2
#define __ec_printf_func__108 __ec_printf_func__2
#define __ec_printf_func__109 __ec_printf_func__2
#define __ec_printf_func__110 __ec_printf_func__2


#define __ec_fprintf_func__4   __ec_fprintf_func__3
#define __ec_fprintf_func__5   __ec_fprintf_func__3
#define __ec_fprintf_func__6   __ec_fprintf_func__3
#define __ec_fprintf_func__7   __ec_fprintf_func__3
#define __ec_fprintf_func__8   __ec_fprintf_func__3
#define __ec_fprintf_func__9   __ec_fprintf_func__3
#define __ec_fprintf_func__10  __ec_fprintf_func__3
#define __ec_fprintf_func__11  __ec_fprintf_func__3
#define __ec_fprintf_func__12  __ec_fprintf_func__3
#define __ec_fprintf_func__13  __ec_fprintf_func__3
#define __ec_fprintf_func__14  __ec_fprintf_func__3
#define __ec_fprintf_func__15  __ec_fprintf_func__3
#define __ec_fprintf_func__16  __ec_fprintf_func__3
#define __ec_fprintf_func__17  __ec_fprintf_func__3
#define __ec_fprintf_func__18  __ec_fprintf_func__3
#define __ec_fprintf_func__19  __ec_fprintf_func__3
#define __ec_fprintf_func__30  __ec_fprintf_func__3
#define __ec_fprintf_func__31  __ec_fprintf_func__3
#define __ec_fprintf_func__32  __ec_fprintf_func__3
#define __ec_fprintf_func__33  __ec_fprintf_func__3
#define __ec_fprintf_func__34  __ec_fprintf_func__3
#define __ec_fprintf_func__35  __ec_fprintf_func__3
#define __ec_fprintf_func__36  __ec_fprintf_func__3
#define __ec_fprintf_func__37  __ec_fprintf_func__3
#define __ec_fprintf_func__38  __ec_fprintf_func__3
#define __ec_fprintf_func__39  __ec_fprintf_func__3
#define __ec_fprintf_func__30  __ec_fprintf_func__3
#define __ec_fprintf_func__31  __ec_fprintf_func__3
#define __ec_fprintf_func__32  __ec_fprintf_func__3
#define __ec_fprintf_func__33  __ec_fprintf_func__3
#define __ec_fprintf_func__34  __ec_fprintf_func__3
#define __ec_fprintf_func__35  __ec_fprintf_func__3
#define __ec_fprintf_func__36  __ec_fprintf_func__3
#define __ec_fprintf_func__37  __ec_fprintf_func__3
#define __ec_fprintf_func__38  __ec_fprintf_func__3
#define __ec_fprintf_func__39  __ec_fprintf_func__3
#define __ec_fprintf_func__40  __ec_fprintf_func__3
#define __ec_fprintf_func__41  __ec_fprintf_func__3
#define __ec_fprintf_func__42  __ec_fprintf_func__3
#define __ec_fprintf_func__43  __ec_fprintf_func__3
#define __ec_fprintf_func__44  __ec_fprintf_func__3
#define __ec_fprintf_func__45  __ec_fprintf_func__3
#define __ec_fprintf_func__46  __ec_fprintf_func__3
#define __ec_fprintf_func__47  __ec_fprintf_func__3
#define __ec_fprintf_func__48  __ec_fprintf_func__3
#define __ec_fprintf_func__49  __ec_fprintf_func__3
#define __ec_fprintf_func__50  __ec_fprintf_func__3
#define __ec_fprintf_func__51  __ec_fprintf_func__3
#define __ec_fprintf_func__52  __ec_fprintf_func__3
#define __ec_fprintf_func__53  __ec_fprintf_func__3
#define __ec_fprintf_func__54  __ec_fprintf_func__3
#define __ec_fprintf_func__55  __ec_fprintf_func__3
#define __ec_fprintf_func__56  __ec_fprintf_func__3
#define __ec_fprintf_func__57  __ec_fprintf_func__3
#define __ec_fprintf_func__58  __ec_fprintf_func__3
#define __ec_fprintf_func__59  __ec_fprintf_func__3
#define __ec_fprintf_func__60  __ec_fprintf_func__3
#define __ec_fprintf_func__61  __ec_fprintf_func__3
#define __ec_fprintf_func__62  __ec_fprintf_func__3
#define __ec_fprintf_func__63  __ec_fprintf_func__3
#define __ec_fprintf_func__64  __ec_fprintf_func__3
#define __ec_fprintf_func__65  __ec_fprintf_func__3
#define __ec_fprintf_func__66  __ec_fprintf_func__3
#define __ec_fprintf_func__67  __ec_fprintf_func__3
#define __ec_fprintf_func__68  __ec_fprintf_func__3
#define __ec_fprintf_func__69  __ec_fprintf_func__3
#define __ec_fprintf_func__70  __ec_fprintf_func__3
#define __ec_fprintf_func__71  __ec_fprintf_func__3
#define __ec_fprintf_func__72  __ec_fprintf_func__3
#define __ec_fprintf_func__73  __ec_fprintf_func__3
#define __ec_fprintf_func__74  __ec_fprintf_func__3
#define __ec_fprintf_func__75  __ec_fprintf_func__3
#define __ec_fprintf_func__76  __ec_fprintf_func__3
#define __ec_fprintf_func__77  __ec_fprintf_func__3
#define __ec_fprintf_func__78  __ec_fprintf_func__3
#define __ec_fprintf_func__79  __ec_fprintf_func__3
#define __ec_fprintf_func__80  __ec_fprintf_func__3
#define __ec_fprintf_func__81  __ec_fprintf_func__3
#define __ec_fprintf_func__82  __ec_fprintf_func__3
#define __ec_fprintf_func__83  __ec_fprintf_func__3
#define __ec_fprintf_func__84  __ec_fprintf_func__3
#define __ec_fprintf_func__85  __ec_fprintf_func__3
#define __ec_fprintf_func__86  __ec_fprintf_func__3
#define __ec_fprintf_func__87  __ec_fprintf_func__3
#define __ec_fprintf_func__88  __ec_fprintf_func__3
#define __ec_fprintf_func__89  __ec_fprintf_func__3
#define __ec_fprintf_func__90  __ec_fprintf_func__3
#define __ec_fprintf_func__91  __ec_fprintf_func__3
#define __ec_fprintf_func__92  __ec_fprintf_func__3
#define __ec_fprintf_func__93  __ec_fprintf_func__3
#define __ec_fprintf_func__94  __ec_fprintf_func__3
#define __ec_fprintf_func__95  __ec_fprintf_func__3
#define __ec_fprintf_func__96  __ec_fprintf_func__3
#define __ec_fprintf_func__97  __ec_fprintf_func__3
#define __ec_fprintf_func__98  __ec_fprintf_func__3
#define __ec_fprintf_func__99  __ec_fprintf_func__3
#define __ec_fprintf_func__100 __ec_fprintf_func__3
#define __ec_fprintf_func__101 __ec_fprintf_func__3
#define __ec_fprintf_func__102 __ec_fprintf_func__3
#define __ec_fprintf_func__103 __ec_fprintf_func__3
#define __ec_fprintf_func__104 __ec_fprintf_func__3
#define __ec_fprintf_func__105 __ec_fprintf_func__3
#define __ec_fprintf_func__106 __ec_fprintf_func__3
#define __ec_fprintf_func__107 __ec_fprintf_func__3
#define __ec_fprintf_func__108 __ec_fprintf_func__3
#define __ec_fprintf_func__109 __ec_fprintf_func__3
#define __ec_fprintf_func__110 __ec_fprintf_func__3

#ifdef __cplusplus
}
#endif

#endif
