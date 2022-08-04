
################################################################################
# CMake pre requirements
################################################################################
cmake_minimum_required(VERSION 3.16)

################################################################################
# Setting up the versioning system
################################################################################
set(Developement 0)
set(Nightly      1)
set(Alpha        2)
set(Beta         3)
set(Release      4)

################################################################################
# Defining the project description
################################################################################
project(eclibc VERSION 1.0.0.${Developement} DESCRIPTION "FOSS C library used \
in software developed by https://github.com/ExoticCandyC")

################################################################################
# Asking CMake to export all symbols
################################################################################
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

################################################################################
# Setting up the include directory path
################################################################################
set (EC_API_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

################################################################################
# Defining the modules used to add files
################################################################################
macro(EC_API_ADD_SOURCE_FILE)
    list(APPEND EC_API_SOURCE_FILES ${PROJECT_SOURCE_DIR}/ec/${ARGV0})
endmacro()

macro(EC_API_ADD_HEADER_FILE)
    list(APPEND EC_API_HEADER_FILES ${EC_API_INCLUDE_DIR}/ec/${ARGV0})
endmacro()

################################################################################
# Adding files. This MAY move to subdirectory
################################################################################
EC_API_ADD_SOURCE_FILE(map.c)
EC_API_ADD_SOURCE_FILE(vector.c)

EC_API_ADD_HEADER_FILE(map.h)
EC_API_ADD_HEADER_FILE(vector.h)
EC_API_ADD_HEADER_FILE(mutex.h)

################################################################################
# Defining targets.
#       Default configuration script will build all the targets. This behaviour
#       will change in later versions to install ONLY the native target by
#       default.
#
# Targets:
#   1) eclibc                   Linux X86_64 shared library
#   2) eclibcStatic             Linux X86_64 static library
#   3) eclibc32                 Linux X86_32 shared library
#   4) eclibc32Static           Linux X86_32 static library
#
# To be added in later versions:
#   *) eclibcMinGW32            x86_64-w64-mingw32 shared library
#   *) eclibcMinGW32Static      x86_64-w64-mingw32 static library
#   *) eclibc32MinGW32          i686-w64-mingw32 shared library
#   *) eclibc32MinGW32Static    i686-w64-mingw32 static library
#   *) eclibcXC16               XC16 static library
#   *) eclibcXC32               XC32 static library
#   *) eclibcESP32              ESP32 static library
#   *) eclibcESP32s2            ESP32s2 static library
#   *) eclibcESP32s3            ESP32s3 static library
################################################################################
add_library(eclibc SHARED
     ${EC_API_SOURCE_FILES}
     ${EC_API_HEADER_FILES}
)

add_library(eclibc32 SHARED
    ${EC_API_SOURCE_FILES}
)

add_library(eclibcStatic STATIC
    ${EC_API_SOURCE_FILES}
)

add_library(eclibcStatic32 STATIC
    ${EC_API_SOURCE_FILES}
)

################################################################################
# Setting general compile options
################################################################################
add_compile_options(-I"${EC_API_INCLUDE_DIR}")
add_compile_options(-O3)
add_compile_options(-flto)
add_compile_options(-fPIC)
add_compile_options(-ansi)
add_compile_options(-pedantic)
add_compile_options(-ftree-loop-vectorize)
add_compile_options(-fstack-protector)
add_compile_options(-Waggressive-loop-optimizations)
add_compile_options(-Werror)
add_compile_options(-Wpedantic)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wfloat-equal)
add_compile_options(-Wshadow)
add_compile_options(-Wswitch-enum)
add_compile_options(-Wcast-qual)
add_compile_options(-Wconversion)
add_compile_options(-Wundef)
add_compile_options(-Wunused-macros)
add_compile_options(-Wduplicated-cond)
add_compile_options(-Wduplicated-branches)

################################################################################
# Setting general link options
################################################################################
add_link_options(-O3)
add_link_options(-flto)
add_link_options(-fPIC)
add_link_options(-ansi)
add_link_options(-pedantic)
add_link_options(-ftree-loop-vectorize)
add_link_options(-fstack-protector)
add_link_options(-Waggressive-loop-optimizations)
add_link_options(-Werror)
add_link_options(-Wpedantic)
add_link_options(-Wall)
add_link_options(-Wextra)
add_link_options(-Wfloat-equal)
add_link_options(-Wshadow)
add_link_options(-Wswitch-enum)
add_link_options(-Wcast-qual)
add_link_options(-Wconversion)
add_link_options(-Wundef)
add_link_options(-Wunused-macros)
add_link_options(-Wduplicated-cond)
add_link_options(-Wduplicated-branches)

################################################################################
# Setting target specific compile options
################################################################################
target_compile_options  (eclibc32       PUBLIC -m32)
target_compile_options  (eclibcStatic32 PUBLIC -m32)

################################################################################
# Setting target specific link options
################################################################################
target_link_options     (eclibc32       PUBLIC -m32)
target_link_options     (eclibcStatic32 PUBLIC -m32)

################################################################################
# Setting target output names
################################################################################
set_target_properties(eclibcStatic   PROPERTIES OUTPUT_NAME eclibc)
set_target_properties(eclibc32       PROPERTIES OUTPUT_NAME eclibc32)
set_target_properties(eclibcStatic32 PROPERTIES OUTPUT_NAME eclibc32)

################################################################################
# Defining install behaviour for target: eclibc
################################################################################
set_target_properties(eclibc PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibc PROPERTIES SOVERSION 1)
target_include_directories(eclibc PUBLIC ${EC_API_INCLUDE_DIR} )
set_target_properties(eclibc
                         PROPERTIES PUBLIC_HEADER
                         "${EC_API_HEADER_FILES}"
                     )
install(TARGETS eclibc
    LIBRARY       DESTINATION "/usr/lib"
    ARCHIVE       DESTINATION "/usr/lib"
    RUNTIME       DESTINATION "/usr/bin"
    PUBLIC_HEADER DESTINATION "/usr/include/ec"
       )

################################################################################
# Defining install behaviour for target: eclibcStatic
################################################################################
set_target_properties(eclibcStatic PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibcStatic PROPERTIES SOVERSION 1)
target_include_directories(eclibcStatic PUBLIC ${EC_API_INCLUDE_DIR} )
set_target_properties(eclibcStatic
                         PROPERTIES PUBLIC_HEADER
                         "${EC_API_HEADER_FILES}"
                     )
install(TARGETS eclibcStatic
    LIBRARY       DESTINATION "/usr/lib"
    ARCHIVE       DESTINATION "/usr/lib"
    PUBLIC_HEADER DESTINATION "/usr/include/ec"
       )

################################################################################
# Defining install behaviour for target: eclibc32
################################################################################
set_target_properties(eclibc32 PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibc32 PROPERTIES SOVERSION 1)
target_include_directories(eclibc32 PUBLIC ${EC_API_INCLUDE_DIR} )
set_target_properties(eclibc32
                         PROPERTIES PUBLIC_HEADER
                         "${EC_API_HEADER_FILES}"
                     )
install(TARGETS eclibc32
    LIBRARY       DESTINATION "/usr/lib32"
    ARCHIVE       DESTINATION "/usr/lib32"
    PUBLIC_HEADER DESTINATION "/usr/include/ec"
       )

################################################################################
# Defining install behaviour for target: eclibcStatic32
################################################################################
set_target_properties(eclibcStatic32 PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibcStatic32 PROPERTIES SOVERSION 1)
target_include_directories(eclibcStatic32 PUBLIC ${EC_API_INCLUDE_DIR} )
set_target_properties(eclibcStatic32
                         PROPERTIES PUBLIC_HEADER
                         "${EC_API_HEADER_FILES}"
                     )
install(TARGETS eclibcStatic32
    LIBRARY       DESTINATION "/usr/lib32"
    ARCHIVE       DESTINATION "/usr/lib32"
    PUBLIC_HEADER DESTINATION "/usr/include/ec"
       )

################################################################################
# Building the package config file
################################################################################
configure_file(
                  ${CMAKE_CURRENT_SOURCE_DIR}/ec/eclibc.pc.in
                  ${CMAKE_CURRENT_SOURCE_DIR}/.pkgconfig/eclibc.pc
                  @ONLY
              )

################################################################################
# installing the package config file
################################################################################
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/.pkgconfig/eclibc.pc
        DESTINATION "/lib/pkgconfig")

################################################################################
# making symbolic links from eclibc32 to eclibc
################################################################################
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.so.${PROJECT_VERSION} /usr/lib32/libeclibc.so.${PROJECT_VERSION} 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.so.${PROJECT_VERSION}\")")
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.so.${PROJECT_VERSION_MAJOR} /usr/lib32/libeclibc.so.${PROJECT_VERSION_MAJOR} 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.so.${PROJECT_VERSION_MAJOR}\")")
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.so /usr/lib32/libeclibc.so 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.so\")")
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.a /usr/lib32/libeclibc.a 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.a\")")

################################################################################
# updating operating system library files
################################################################################
install (CODE "execute_process(COMMAND ldconfig)")

