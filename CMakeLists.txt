
cmake_minimum_required(VERSION 3.16)

set(Developement 0)
set(Nightly      1)
set(Alpha        2)
set(Beta         3)
set(Release      4)

project(eclibc VERSION 1.0.0.${Developement} DESCRIPTION "FOSS C library used in software \
developed by https://github.com/ExoticCandyC")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

#add_compile_options("-I${CMAKE_CURRENT_SOURCE_DIR}/include")

set (EC_API_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set (EC_API_SOURCE_FILES
                ${PROJECT_SOURCE_DIR}/ec/map.c
                ${PROJECT_SOURCE_DIR}/ec/vector.c)

set  (EC_API_HEADER_FILES
                ${EC_API_INCLUDE_DIR}/ec/map.h
                ${EC_API_INCLUDE_DIR}/ec/vector.h)

add_library(eclibc SHARED
    ${EC_API_SOURCE_FILES}
)

add_compile_options(-I"${EC_API_INCLUDE_DIR}")

set_target_properties(eclibc PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibc PROPERTIES SOVERSION 1)

target_include_directories(eclibc PUBLIC ${EC_API_INCLUDE_DIR} )

set_target_properties(eclibc PROPERTIES PUBLIC_HEADER "${EC_API_HEADER_FILES}")

install(TARGETS eclibc
    LIBRARY       DESTINATION "/usr/lib"
    ARCHIVE       DESTINATION "/usr/lib"
    RUNTIME       DESTINATION "/usr/bin"
    PUBLIC_HEADER DESTINATION "/usr/include/ec")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ec/eclibc.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/eclibc.pc @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/eclibc.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install (CODE "execute_process(COMMAND ldconfig)")
