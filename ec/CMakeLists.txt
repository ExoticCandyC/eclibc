
cmake_minimum_required(VERSION 3.16)

EC_API_ADD_SOURCE_FILE(map.c)
EC_API_ADD_SOURCE_FILE(vector.c)
EC_API_ADD_SOURCE_FILE(io.c)
EC_API_ADD_SOURCE_FILE(printf.c)



add_subdirectory(benchmark)

EXOTIC_CANDY_SYNC_FILES_WITH_PARENT()

