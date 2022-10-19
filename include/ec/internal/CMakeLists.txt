
cmake_minimum_required(VERSION 3.16)

EC_API_ADD_HEADER_FILE(pad_string.h)
EC_API_ADD_HEADER_FILE(spad_string.h)
EC_API_ADD_HEADER_FILE(vprintf_internal.h)
EC_API_ADD_HEADER_FILE(vsprintf_internal.h)
EC_API_ADD_HEADER_FILE(print_format_table.h)
EC_API_ADD_HEADER_FILE(printf_fix_optimizer.h)
EC_API_ADD_HEADER_FILE(sprintf_fix_optimizer.h)
EC_API_ADD_HEADER_FILE(urlpad_string.h)
EC_API_ADD_HEADER_FILE(vurlprintf_internal.h)

add_subdirectory(text_parse)

EXOTIC_CANDY_SYNC_FILES_WITH_PARENT()
