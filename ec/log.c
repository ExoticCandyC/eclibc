
#include <ec/log.h>

#include <ec/io.h>
#include <stdarg.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if (PROJECT_LOGGER == ENABLED) || defined(ECLIBC_INTERNAL_COMPILE)

void eclogprintf(const char *CXXsuffix, const char* header, const char* project,
                    const uint16_t lineNumber, const char* filename,
                    const log_level logLevel, const log_level levelInternal,
                    const log_level projectLevel, const char* format, ...)
{
    FILE *__restrict target = stdout;
    va_list argptr;
    if(logLevel > levelInternal || logLevel > projectLevel)
        return;
    #if defined(_WIN32) || defined(__linux__)
    if(logLevel == log_error)
        target = stderr;
    #endif
    va_start(argptr, format);
    ec_fprintf(target, "%s", CXXsuffix);
    if(filename != EC_NULL)
        ec_fprintf(target, "%s:%s", filename, (lineNumber == 0 ? " " : ""));
    if(lineNumber != 0)
        ec_fprintf(target, "%u: ", lineNumber);
    if(project != EC_NULL)
        ec_fprintf(target, "%s: ", project);
    ec_fprintf(target, "%s: ", header);
    ec_vfprintf(target, format, argptr);
    ec_fprintf(target, "\r\n");
    va_end(argptr);
}

#endif

#ifdef __cplusplus
}
#endif
