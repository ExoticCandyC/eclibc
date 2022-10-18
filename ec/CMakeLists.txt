
cmake_minimum_required(VERSION 3.16)

EC_API_ADD_SOURCE_FILE(map.c)
EC_API_ADD_SOURCE_FILE(vector.c)
EC_API_ADD_SOURCE_FILE(io.c)
EC_API_ADD_SOURCE_FILE(log.c)
EC_API_ADD_SOURCE_FILE(emoji.c)
EC_API_ADD_SOURCE_FILE(utf8.c)
EC_API_ADD_SOURCE_FILE(time.c)
EC_API_ADD_SOURCE_FILE(linux.c)
EC_API_ADD_SOURCE_FILE(socket.c)


add_subdirectory(benchmark)
add_subdirectory(internal)

EXOTIC_CANDY_SYNC_FILES_WITH_PARENT()
