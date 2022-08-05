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

#ifndef ECLIBC_MUTEX_H
#define ECLIBC_MUTEX_H 1

#include <pthread.h>

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

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

/**
 * @brief ec_mutex  Just a simple type name for the standard pthread_mutex.
 */
typedef pthread_mutex_t ec_mutex;

/**
 * @def ec_mutex_lock(mtx)
 * @brief           Just a wrapper around C standard pthread mutex, used to
 *                  lock a mutex.
 * @param [in]mtx   the mutex object to be used for the locking.
 */
#define ec_mutex_lock(mtx) \
    pthread_mutex_lock(&mtx)

/**
 * @def ec_mutex_unlock(mtx)
 * @brief           Just a wrapper around C standard pthread mutex, used to
 *                  unlock a mutex.
 * @param [in]mtx   the mutex object to be unlocked.
 */
#define ec_mutex_unlock(mtx) \
    pthread_mutex_unlock(&mtx)

/**
 * @def ec_mutex_init(mtx)
 * @brief           Just a wrapper around C standard pthread mutex, used to
 *                  initialize a mutex.
 * @param [in]mtx   the mutex object to be initiated.
 * @return      0   initialization was successful.
 *              1   initialization has failed.
 */
#define ec_mutex_init(mtx) \
    pthread_mutex_init(&mtx, EC_NULL)

/**
 * @def ec_mutex_delete(mtx)
 * @brief           Just a wrapper around C standard pthread mutex, used to
 *                  destroy a mutex. Note that failing to delete a mutex WONT
 *                  lead to a memory leak as tested by valgrind, but it is a
 *                  good practice to delete a mutex when the job is done.
 * @param [in]mtx   the mutex object to be destroyed.
 */
#define ec_mutex_delete(mtx) \
    pthread_mutex_destroy(&mtx)

/**
 * @def ec_mutex_create(mtx)
 * @brief               Just a wrapper around C standard pthread mutex, used to
 *                      create and initialize a mutex. Please note that this
 *                      macro WILL NOT check for the success of mutex
 *                      initialization and it is up to the user to do the proper
 *                      tests.
 * @warning             This macro can NOT be used in the global section as it
 *                      needs to run a function.
 * @param [in/out]mtx   the mutex object to be created.
 */
#define ec_mutex_create(mtx) \
    pthread_mutex_t mtx; \
    ec_mutex_init(mtx)

#ifdef __cplusplus
}
#endif

#endif
