
cmake_minimum_required(VERSION 3.16)

EC_API_ADD_SOURCE_FILE(digits.c)
EC_API_ADD_SOURCE_FILE(vprintf_internal.c)
EC_API_ADD_SOURCE_FILE(vsprintf_internal.c)
EC_API_ADD_SOURCE_FILE(vurlprintf_internal.c)


EXOTIC_CANDY_SYNC_FILES_WITH_PARENT()
