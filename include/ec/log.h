/* <log.h> -*- C -*- */
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


/**
 * Guide:
 *
 * Optional, but HIGHLY recommended:
 *    the following macros should be defined globally, preferrably using the
 *    compiler and linker's -D flag.
 *
 *      PROJECT_LOGGER:
 *          Description:  Enables or disables the logger, project wide.
 *          Valid values: ENABLED | DISABLED
 *
 *      PROJECT_LOG_LEVEL:
 *          Description:  The global maximum level of logs allowed to be
 *                        printed.
 *          Valid values: A log_level value, as defined in <ec/types.h>
 *                        It is set to log_all by default.
 *
 *      PROJECT_NAME:
 *          Description:  A variable containing the project's name to be used
 *                        as log suffix.
 *          Valid values: Any valid string. The default is an empty string.
 *
 * The following is an example of how you should include this header:
 *
 *      #define LOG_PROJECT_NAME    DISABLED
 *      #define LOG_STATE           ENABLED
 *      #define LOG_LINE_NUMBER     ENABLED
 *      #define LOG_FILE_NAME       ENABLED
 *      #define LOG_LEVEL_INTERNAL  log_all
 *      #define LOG_HEADER_NAME     "Main"
 *      #include <ec/log.h>
 *
 *      Explanation:
 *
 *          LOG_PROJECT_NAME:   Enables/Disables printing of the project name.
 *          LOG_STATE:          Enables/disables the logger for the current
 *                              file.
 *          LOG_LINE_NUMBER:    Enables/Disables printing of the line number.
 *          LOG_FILE_NAME:      Enables/Disables printing of the file name.
 *          LOG_LEVEL_INTERNAL:
 *
 */

/*
 * This file uses a "reverse" header guard, meaning that it will throw an error
 * if a macro is defined.
 * A reverse header guard won't prevent a file from being included multiple
 * times in a source file and if it detects such an occurence, it will cause
 * an error.
 *
 * So, "#pragma once" and the usual "#ifndef ... #define... **** #endif"
 * structures would only defeat this purpose.
 */
#ifdef EC_LOG_H_REVERSE_HEADER_GUARD
#error You cant include <ec/log.h> inside a header file as it will cause \
undefined behaviour within its internal structure.
#else
#define EC_LOG_H_REVERSE_HEADER_GUARD
#endif

#include <ec/types.h>

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

#ifdef ECLIBC_INTERNAL_COMPILE

#define LOG_PROJECT_NAME    ENABLED
#define LOG_STATE           ENABLED
#define LOG_LINE_NUMBER     ENABLED
#define LOG_FILE_NAME       ENABLED
#define LOG_LEVEL_INTERNAL  log_none

#else

#ifndef LOG_STATE
#error \
<ec/log.h> module requires LOG_STATE to be defined before it is being \
included.
#endif

#ifndef LOG_HEADER_NAME
#error \
<ec/log.h> module requires LOG_HEADER_NAME to be defined before it is being \
included.
#endif

#ifndef LOG_LINE_NUMBER
#error \
<ec/log.h> module requires LOG_LINE_NUMBER to be defined before it is being \
included.
#endif

#ifndef LOG_FILE_NAME
#error \
<ec/log.h> module requires LOG_FILE_NAME to be defined before it is being \
included.
#endif

#ifndef LOG_PROJECT_NAME
#error \
<ec/log.h> module requires LOG_PROJECT_NAME to be defined before it is being \
included, it can be set to DISABLED to turn it off.
#endif

#ifndef LOG_LEVEL_INTERNAL
#error \
<ec/log.h> module requires LOG_LEVEL_INTERNAL to be defined before it is \
being included.
#endif

#endif

#ifndef PROJECT_LOGGER
#define PROJECT_LOGGER ENABLED
#ifndef ECLIBC_INTERNAL_COMPILE
#pragma message "PROJECT_LOGGER wasn't defined globally, turning it on."
#endif
#endif

#ifndef PROJECT_LOG_LEVEL
#define PROJECT_LOG_LEVEL log_all
#ifndef ECLIBC_INTERNAL_COMPILE
#pragma message "PROJECT_LOG_LEVEL wasn't defined globally, setting it to " \
                                                                      "log_all."
#endif
#endif

#ifndef PROJECT_NAME
#define PROJECT_NAME ""
#undef  LOG_PROJECT_NAME
#define LOG_PROJECT_NAME DISABLED
#endif

#ifdef __PC__
#ifdef LOG_LEVEL_INTERNAL
#ifdef __cplusplus
static_assert(LOG_LEVEL_INTERNAL < log_MAX, "Invalid log level.");
#else
_Static_assert(LOG_LEVEL_INTERNAL < log_MAX, "Invalid log level.");
#endif
#endif

#ifdef LOG_HEADER_NAME
#ifdef __cplusplus
static_assert(sizeof(LOG_HEADER_NAME) > 3,
                                    "Minimum log header name is 3 characters.");
#else
_Static_assert(sizeof(LOG_HEADER_NAME) > 3,
                                    "Minimum log header name is 3 characters.");
#endif
#endif

#ifdef LOG_STATE
#ifdef __cplusplus
static_assert((LOG_STATE == DISABLED || LOG_STATE == ENABLED),
                                                          "Invalid log state.");
#else
_Static_assert((LOG_STATE == DISABLED || LOG_STATE == ENABLED),
                                                          "Invalid log state.");
#endif
#endif

#ifdef LOG_PROJECT_NAME
#ifdef __cplusplus
static_assert((LOG_PROJECT_NAME == DISABLED || LOG_PROJECT_NAME == ENABLED),
                                 "Invalid state for logging the project name.");
#else
_Static_assert((LOG_PROJECT_NAME == DISABLED || LOG_PROJECT_NAME == ENABLED),
                                 "Invalid state for logging the project name.");
#endif
#endif

#ifdef LOG_FILE_NAME
#ifdef __cplusplus
static_assert((LOG_FILE_NAME == DISABLED || LOG_FILE_NAME == ENABLED),
                                                    "Invalid file name state.");
#else
_Static_assert((LOG_FILE_NAME == DISABLED || LOG_FILE_NAME == ENABLED),
                                                    "Invalid file name state.");
#endif
#endif

#ifdef LOG_LINE_NUMBER
#ifdef __cplusplus
static_assert((LOG_LINE_NUMBER == DISABLED || LOG_LINE_NUMBER == ENABLED),
                                                  "Invalid line number state.");
#else
_Static_assert((LOG_LINE_NUMBER == DISABLED || LOG_LINE_NUMBER == ENABLED),
                                                  "Invalid line number state.");
#endif
#endif
#endif

#if (PROJECT_LOGGER == ENABLED && LOG_STATE == ENABLED)

#ifdef __cplusplus
#define ____LOGGER_CXX_SUFFIX color_text_yellow() "C++:" color_reset() " "
#else
#define ____LOGGER_CXX_SUFFIX ""
#endif

void eclogprintf(const char *CXXsuffix, const char* header, const char* project,
                    const uint16_t lineNumber, const char* filename,
                    const log_level logLevel, const log_level levelInternal,
                    const log_level projectLevel, const char* format, ...);

/**
 * @def eclog(level, ...)
 * @brief               prints the given log message using the printf and unto
 *                      the stdio buffer
 * @param [in]level     the level of the given log
 * @param [in]...       printf formatted string and arguments
 */
#define ec_log(level, ...) \
    eclogprintf(____LOGGER_CXX_SUFFIX, LOG_HEADER_NAME, \
                ((LOG_PROJECT_NAME == DISABLED) ? NULL : PROJECT_NAME), \
                ((LOG_LINE_NUMBER == DISABLED) ? 0 : (uint16_t)__LINE__), \
                ((LOG_FILE_NAME   == DISABLED) ? NULL : __FILE__), \
                ((log_level)level), ((log_level)LOG_LEVEL_INTERNAL), \
                ((log_level)PROJECT_LOG_LEVEL), ##__VA_ARGS__)

#else

/* This macro makes sure you dont trigger a warning after disabling the logger
 * project-wide. */
#define ec_log(...) {}

#endif

#ifdef __cplusplus
}
#endif
