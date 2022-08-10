
cmake_minimum_required(VERSION 3.16)

EC_API_ADD_SOURCE_FILE(digits.c)
EC_API_ADD_SOURCE_FILE(vprintf_internal.c)
EC_API_ADD_SOURCE_FILE(vprintf_mtx_internal.c)
EC_API_ADD_SOURCE_FILE(vprintf_safe_internal.c)



EXOTIC_CANDY_SYNC_FILES_WITH_PARENT()
