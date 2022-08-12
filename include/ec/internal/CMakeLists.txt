
cmake_minimum_required(VERSION 3.16)

EC_API_ADD_HEADER_FILE(pad_string.h)
EC_API_ADD_HEADER_FILE(vprintf_internal.h)
EC_API_ADD_HEADER_FILE(print_format_table.h)



add_subdirectory(text_parse)

EXOTIC_CANDY_SYNC_FILES_WITH_PARENT()
