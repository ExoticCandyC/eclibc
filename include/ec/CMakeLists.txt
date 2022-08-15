
cmake_minimum_required(VERSION 3.16)

EC_API_ADD_HEADER_FILE(map.h)
EC_API_ADD_HEADER_FILE(vector.h)
EC_API_ADD_HEADER_FILE(mutex.h)
EC_API_ADD_HEADER_FILE(io.h)
EC_API_ADD_HEADER_FILE(types.h)
EC_API_ADD_HEADER_FILE(arch.h)
EC_API_ADD_HEADER_FILE(log.h)
EC_API_ADD_HEADER_FILE(ansi.h)
EC_API_ADD_HEADER_FILE(emoji.h)
EC_API_ADD_HEADER_FILE(utf8.h)
EC_API_ADD_HEADER_FILE(ieee754.h)
EC_API_ADD_HEADER_FILE(time.h)
EC_API_ADD_HEADER_FILE(preprocessor.h)
EC_API_ADD_HEADER_FILE(string.h)



add_subdirectory(benchmark)
add_subdirectory(internal)
add_subdirectory(macro)

EXOTIC_CANDY_SYNC_FILES_WITH_PARENT()
