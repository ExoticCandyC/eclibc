
################################################################################
# CMake pre requirements - It cant be higher than the minimum required by ESP
# IDF, because then it would cause erros during cmake process in some cases.
################################################################################
cmake_minimum_required(VERSION 3.16)

################################################################################
# Setting up the versioning system and internal variables
################################################################################
set(Developement 0)
set(Nightly      1)
set(Alpha        2)
set(Beta         3)
set(Release      4)

set(EC_PROJECT_NAME         eclibc)
set(EC_PROJECT_VERSION      1.0.0.${Developement})
set(EC_PROJECT_HOMEPAGE_URL "https://github.com/ExoticCandyC/eclibc")
set(EC_PROJECT_DESCRIPTION  "FOSS C library used in software developed by " /
    "https://github.com/ExoticCandyC")

################################################################################
# Creating the CMake Project
################################################################################
project(                  ${EC_PROJECT_NAME}
    VERSION       ${EC_PROJECT_VERSION}
    HOMEPAGE_URL "${EC_PROJECT_HOMEPAGE_URL}"
    DESCRIPTION  "${EC_PROJECT_DESCRIPTION}"
    LANGUAGES C
)

################################################################################
# Asking CMake to export all symbols
################################################################################
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

################################################################################
# Setting up the include directory path
################################################################################
set (EC_API_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

################################################################################
# Setting up a navigator variable
################################################################################
set(ENV{ECLIBC_MAIN_CMAKE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Defining the modules used to add files
################################################################################
macro(EC_API_ADD_SOURCE_FILE)
    file(
        RELATIVE_PATH
        _relPath
        $ENV{ECLIBC_MAIN_CMAKE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
if (_relPath)
    list (APPEND EC_API_SOURCE_FILES "${_relPath}/${ARGV0}")
else()
    list (APPEND EC_API_SOURCE_FILES "${ARGV0}")
endif()
set (EC_API_SOURCE_FILES ${EC_API_SOURCE_FILES} PARENT_SCOPE)
endmacro()

macro(EC_API_ADD_HEADER_FILE)
    file(
        RELATIVE_PATH
        _relPath
        $ENV{ECLIBC_MAIN_CMAKE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
if (_relPath)
    list (APPEND EC_API_HEADER_FILES "${_relPath}/${ARGV0}")
else()
    list (APPEND EC_API_HEADER_FILES "${ARGV0}")
endif()
set (EC_API_HEADER_FILES ${EC_API_HEADER_FILES} PARENT_SCOPE)
endmacro()

macro (EXOTIC_CANDY_SYNC_FILES_WITH_PARENT)
    set (EC_API_SOURCE_FILES ${EC_API_SOURCE_FILES} PARENT_SCOPE)
    set (EC_API_HEADER_FILES ${EC_API_HEADER_FILES} PARENT_SCOPE)
endmacro()

################################################################################
# Adding sub directories
################################################################################
add_subdirectory(ec)
add_subdirectory(include)

################################################################################
# Setting general compile options
################################################################################
add_compile_options(-I"${EC_API_INCLUDE_DIR}")
add_compile_options(-lm)
add_compile_options(-fPIC)
add_compile_options(-std=c99)
add_compile_options(-Werror)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wfloat-equal)
add_compile_options(-Wshadow)
add_compile_options(-Wswitch-enum)
add_compile_options(-Wcast-qual)
add_compile_options(-Wconversion)
add_compile_options(-Wundef)
add_compile_options(-Wunused-macros)

################################################################################
# Setting general link options
################################################################################
add_link_options(-lm)
add_link_options(-fPIC)
add_link_options(-std=c99)
add_link_options(-Werror)
add_link_options(-Wall)
add_link_options(-Wextra)
add_link_options(-Wfloat-equal)
add_link_options(-Wshadow)
add_link_options(-Wswitch-enum)
add_link_options(-Wcast-qual)
add_link_options(-Wconversion)
add_link_options(-Wundef)
add_link_options(-Wunused-macros)

################################################################################
# Building the package config file
################################################################################
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ec/eclibc.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/.pkgconfig/eclibc.pc
    @ONLY
)

################################################################################
# Defining the functions used to print with color during configuration
# Credit: 
# https://stackoverflow.com/questions/18968979/how-to-get-colorized-output-with-cmakeules 
################################################################################
macro ( print_color NAME )
    print ( COLOR ${NAME} "     ${NAME}" )
endmacro ()

function  ( text )
    cmake_parse_arguments ( PARSE_ARGV 0 "_TEXT" "BOLD" "COLOR" "" )

    set ( _TEXT_OPTIONS -E cmake_echo_color --no-newline )

    if ( _TEXT_COLOR )
        string ( TOLOWER "${_TEXT_COLOR}" _TEXT_COLOR_LOWER )
        if ( NOT ${_TEXT_COLOR_LOWER} MATCHES "^normal|black|red|green|yellow|blue|magenta|cyan|white" )
            print ( "Only these colours are supported:" )
            print_color ( NORMAL )
            print_color ( BLACK )
            print_color ( RED )
            print_color ( GREEN )
            print_color ( YELLOW )
            print_color ( BLUE )
            print_color ( MAGENTA )
            print_color ( CYAN )
            print_color ( WHITE )
            TEXT ( WARING "Color ${_TEXT_COLOR} is not support." )
        else ()
            list ( APPEND _TEXT_OPTIONS --${_TEXT_COLOR_LOWER} )
        endif ()
    endif ()

    if ( _TEXT_BOLD )
        list ( APPEND _TEXT_OPTIONS --bold )
    endif ()

    execute_process ( COMMAND ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1 ${CMAKE_COMMAND} ${_TEXT_OPTIONS} ${_TEXT_UNPARSED_ARGUMENTS}
        OUTPUT_VARIABLE _TEXT_RESULT
        ECHO_ERROR_VARIABLE
    )

set ( TEXT_RESULT ${_TEXT_RESULT} PARENT_SCOPE )
endfunction ()
unset ( print_color )
function ( print )
    text ( ${ARGN} )
    message ( ${TEXT_RESULT} )
endfunction ()

################################################################################
# Compiler detection macro
#       @param ARGV0    compiler name
#       @param ARGV1    library type {SHARED | STATIC}
# 	@param ARGV2	report not found {"REPORT" | "MACRO" | "DONT REPORT"}
# 	@param ARGV3	report text, leave blank if ARGV2 is not set to "REPORT"
#       @param ARGV4	target name
#       @param ARGV5	target final name (will be used as OUTPUT_NAME)
#       @param ARGV6	additional PUBLIC compile flags, "NONE" to skip
#	@param ARGV7    library target directory relative to the compiler parent
#                       path. Usually "lib" but "lib32" for linux 32bit target.
#	@param ARGV8    archive target directory relative to the compiler parent
#                       path. Usually "lib" but "lib32" for linux 32bit target.
#	@param ARGV9    header target directory relative to the compiler parent
#                       path. ALmost always "include"
################################################################################
macro(EC_API_SEARCH_FOR_COMPILER)
    unset(EC_THE_COMPILER_${ARGV0}_${ARGV1})
    unset(EC_COMPILER_PATH_${ARGV0}_${ARGV1})
    find_program(EC_THE_COMPILER_${ARGV0}_${ARGV1} ${ARGV0})
    if(EC_THE_COMPILER_${ARGV0}_${ARGV1})
        get_filename_component(EC_COMPILER_PATH_${ARGV0}_${ARGV1}
            ${EC_THE_COMPILER_${ARGV0}_${ARGV1}} DIRECTORY)
        get_filename_component(EC_COMPILER_PATH_${ARGV0}_${ARGV1}
            ${EC_COMPILER_PATH_${ARGV0}_${ARGV1}} DIRECTORY)
        set(EC_TARGET_LIBRARY_PATH
            "${EC_COMPILER_PATH_${ARGV0}_${ARGV1}}/${ARGV7}")
        set(EC_TARGET_ARCHIVE_PATH
            "${EC_COMPILER_PATH_${ARGV0}_${ARGV1}}/${ARGV8}")
        set(EC_TARGET_HEADER_PATH
            "${EC_COMPILER_PATH_${ARGV0}_${ARGV1}}/${ARGV9}")
        print(BOLD COLOR GREEN "-- Found ${ARGV0} for target: ${ARGV4}")

        #add the target
        add_library(
            ${ARGV4} ${ARGV1}
            ${EC_API_SOURCE_FILES}
            ${EC_API_HEADER_FILES}
        )
    #set the output file's name
    set_target_properties(
        ${ARGV4}
        PROPERTIES
        OUTPUT_NAME
        ${ARGV5}
    )


target_compile_options(${ARGV4} PRIVATE -DECLIBC_INTERNAL_COMPILE)
target_link_options   (${ARGV4} PRIVATE -DECLIBC_INTERNAL_COMPILE)

# for an unknown reason, __XTENSA__ is not defined while making a
# library. so i manually add it to the compiler.
# Also, IDF_VER is not defined when compiling directly with xtensa.
# so for compatibility reasons, IDF_VER is defined as well.
if(${ARGV4} MATCHES eclibcESP32)
    target_compile_options(${ARGV4} PRIVATE -D__XTENSA__)
    target_compile_options(${ARGV4} PRIVATE -DIDF_VER)
    target_link_options   (${ARGV4} PRIVATE -D__XTENSA__)
    target_link_options   (${ARGV4} PRIVATE -DIDF_VER)
elseif(${ARGV4} MATCHES eclibcESP32s2)
    target_compile_options(${ARGV4} PRIVATE -D__XTENSA__)
    target_compile_options(${ARGV4} PRIVATE -DIDF_VER)
    target_link_options   (${ARGV4} PRIVATE -D__XTENSA__)
    target_link_options   (${ARGV4} PRIVATE -DIDF_VER)
elseif(${ARGV4} MATCHES eclibcESP32s3)
    target_compile_options(${ARGV4} PRIVATE -D__XTENSA__)
    target_compile_options(${ARGV4} PRIVATE -DIDF_VER)
    target_link_options   (${ARGV4} PRIVATE -D__XTENSA__)
    target_link_options   (${ARGV4} PRIVATE -DIDF_VER)
endif()

# Just in case I want to export DLLs in the future, the definition
# is added here.
if(${ARGV5} MATCHES eclibcMinGW32)
    target_compile_options(${ARGV4} PRIVATE -DEC_API_DLL_EXPORT)
    target_link_options   (${ARGV4} PRIVATE -DEC_API_DLL_EXPORT)
elseif(${ARGV5} MATCHES eclibc32MinGW32)
    target_compile_options(${ARGV4} PRIVATE -DEC_API_DLL_EXPORT)
    target_link_options   (${ARGV4} PRIVATE -DEC_API_DLL_EXPORT)
endif()

# XC16 and XC32 dont support these flags, so add them selectively
# Also O3 is not a feww option on XC16 and XC32, And O1 makes
# smaller code on PIC24 than O2. So we choose O1 for XC16 and
# O2 for XC32
if(${ARGV4} MATCHES eclibcXC16)
    target_compile_options(${ARGV4} PRIVATE -DXC16)
    target_compile_options(${ARGV4} PRIVATE -O1)
    target_link_options(${ARGV4} PRIVATE -DXC16)
    target_link_options(${ARGV4} PRIVATE -O1)
elseif(${ARGV4} MATCHES eclibcXC32)
    target_compile_options(${ARGV4} PRIVATE -DXC32)
    target_compile_options(${ARGV4} PRIVATE -O2)
    target_link_options(${ARGV4} PRIVATE -DXC32)
    target_link_options(${ARGV4} PRIVATE -O2)
else()
    target_compile_options(${ARGV4} PRIVATE -Os)
    target_compile_options(${ARGV4} PRIVATE -Wduplicated-cond)
    target_compile_options(${ARGV4} PRIVATE -Wduplicated-branches)
    target_compile_options(${ARGV4} PRIVATE -Wno-variadic-macros)
    target_compile_options(${ARGV4} PRIVATE -pedantic)
    target_compile_options(${ARGV4} PRIVATE -Wpedantic)
    target_compile_options(${ARGV4} PRIVATE -fstack-protector)
    target_compile_options(${ARGV4} PRIVATE -flto)

    target_link_options(${ARGV4} PRIVATE -Os)
    target_link_options(${ARGV4} PRIVATE -Wduplicated-cond)
    target_link_options(${ARGV4} PRIVATE -Wduplicated-branches)
    target_link_options(${ARGV4} PRIVATE -pedantic)
    target_link_options(${ARGV4} PRIVATE -fstack-protector)
    target_link_options(${ARGV4} PRIVATE -flto)

    if(${ARGV0} MATCHES "gcc")
        target_link_options(${ARGV4} PRIVATE -ftree-loop-vectorize)
        target_link_options(${ARGV4} PRIVATE
            -Waggressive-loop-optimizations)
        target_compile_options(${ARGV4} PRIVATE -ftree-loop-vectorize)
        target_compile_options(${ARGV4} PRIVATE
            -Waggressive-loop-optimizations)
    endif()
endif()

#add extra compile and link options if necessary
if(${ARGV6} MATCHES "NONE")
else()
    target_compile_options(${ARGV4} PUBLIC ${ARGV6})
    target_link_options   (${ARGV4} PUBLIC ${ARGV6})
endif()

# generate the compiler intermediatory script to avoid passing
#      /usr/bin/cc to all the compilers
set(EC_COMPILER_SCRIPT_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/.compiler_scripts")
set(EC_COMPILER_SCRIPT_FILE "${EC_COMPILER_SCRIPT_DIR}/${ARGV4}")
set(EC_COMPILER_SCRIPT_GIT  "${EC_COMPILER_SCRIPT_DIR}/.gitignore")
execute_process(COMMAND bash -c "mkdir ${EC_COMPILER_SCRIPT_DIR}/ 2> /dev/null")
execute_process(COMMAND bash -c "echo \"*\" > ${EC_COMPILER_SCRIPT_GIT}")
execute_process(COMMAND bash -c "echo \"\#\!/bin/bash\" > ${EC_COMPILER_SCRIPT_FILE}")
    execute_process(COMMAND bash -c "echo \"set -- \\\"${EC_THE_COMPILER_${ARGV0}_${ARGV1}}\\\" \\\"\\\${@:2}\\\"\" >> ${EC_COMPILER_SCRIPT_FILE}")
    execute_process(COMMAND bash -c "echo \"\\\$@\" >> ${EC_COMPILER_SCRIPT_FILE}")
    execute_process(COMMAND bash -c "chmod +x ${EC_COMPILER_SCRIPT_FILE}")

    # setup the target's configurations
    set_target_properties(${ARGV4} PROPERTIES VERSION ${PROJECT_VERSION})
    set_target_properties(${ARGV4} PROPERTIES SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
    set_target_properties(${ARGV4} PROPERTIES C_COMPILER_LAUNCHER "${EC_COMPILER_SCRIPT_FILE}")
    set_target_properties(${ARGV4} PROPERTIES C_LINKER_LAUNCHER "${EC_COMPILER_SCRIPT_FILE}")
    target_include_directories(${ARGV4} PUBLIC ${EC_API_INCLUDE_DIR} )

    # report the start of the target's installaton
    install(
        CODE "execute_process(COMMAND echo -e \"\r\nStarting to install target: \\\"${ARGV4}\\\"\")"
        TARGETS ${ARGV4}
    )
# set the destination for header files
install(
    DIRECTORY ${EC_API_INCLUDE_DIR}/ec/
    TARGETS ${ARGV4}
    DESTINATION "${EC_TARGET_HEADER_PATH}/ec"
    FILES_MATCHING PATTERN "*.h"
)
# XC16 uses "lega-c" as the include source when c90 is selected
if(${ARGV4} MATCHES eclibcXC16)
    install(
        DIRECTORY ${EC_API_INCLUDE_DIR}/ec/
        TARGETS ${ARGV4}
        DESTINATION "${EC_TARGET_HEADER_PATH}/lega-c/ec"
        FILES_MATCHING PATTERN "*.h"
    )
endif()

# set the library and archive destination
install(
    TARGETS ${ARGV4}
    LIBRARY DESTINATION "${EC_TARGET_LIBRARY_PATH}"
    ARCHIVE DESTINATION "${EC_TARGET_ARCHIVE_PATH}"
)
# make appropriate symlinks if needed
if("x__${ARGV4}__x" MATCHES "x__eclibc__x")
else()
    if(${ARGV1} MATCHES SHARED)
        install(
            CODE "execute_process(COMMAND bash -c \"ln -s ${EC_TARGET_LIBRARY_PATH}/lib${ARGV4}.so.${PROJECT_VERSION} ${EC_TARGET_LIBRARY_PATH}/libeclibc.so.${PROJECT_VERSION} 2> /dev/null\")"
            TARGETS ${ARGV4}
        )
    install(
        CODE "execute_process(COMMAND echo \"-- Up-to-date: ${EC_TARGET_LIBRARY_PATH}/libeclibc.so.${PROJECT_VERSION}\")"
        TARGETS ${ARGV4}
    )
install(
    CODE "execute_process(COMMAND bash -c \"ln -s ${EC_TARGET_LIBRARY_PATH}/lib${ARGV4}.so.${PROJECT_VERSION_MAJOR} ${EC_TARGET_LIBRARY_PATH}/libeclibc.so.${PROJECT_VERSION_MAJOR} 2> /dev/null\")"
    TARGETS ${ARGV4}
)
install(
    CODE "execute_process(COMMAND echo \"-- Up-to-date: ${EC_TARGET_LIBRARY_PATH}/libeclibc.so.${PROJECT_VERSION_MAJOR}\")"
    TARGETS ${ARGV4}
)
install(
    CODE "execute_process(COMMAND bash -c \"ln -s ${EC_TARGET_LIBRARY_PATH}/lib${ARGV4}.so ${EC_TARGET_LIBRARY_PATH}/libeclibc.so 2> /dev/null\")"
    TARGETS ${ARGV4}
)
install(
    CODE "execute_process(COMMAND echo \"-- Up-to-date: ${EC_TARGET_LIBRARY_PATH}/libeclibc.so\")"
    TARGETS ${ARGV4}
)
else()
    install(
        CODE "execute_process(COMMAND bash -c \"ln -s ${EC_TARGET_LIBRARY_PATH}/lib${ARGV4}.a ${EC_TARGET_LIBRARY_PATH}/libeclibc.a 2> /dev/null\")"
        TARGETS ${ARGV4}
    )
install(
    CODE "execute_process(COMMAND echo \"-- Up-to-date: ${EC_TARGET_LIBRARY_PATH}/libeclibc.a\")"
    TARGETS ${ARGV4}
)
endif()
endif()

# install the package configuration file
install(
    CODE "execute_process(COMMAND bash -c \"cp ${CMAKE_CURRENT_SOURCE_DIR}/.pkgconfig/eclibc.pc /lib/pkgconfig/${ARGV4}.pc && echo '-- Installing: /lib/pkgconfig/${ARGV4}.pc'\")"
    TARGETS ${ARGV4}
)
# report the end of the installation for the target
install(
    CODE "execute_process(COMMAND echo -e \"Target \\\"${ARGV4}\\\" finished installing\r\n\")"
    TARGETS ${ARGV4}
)
else()
    if(${ARGV2} MATCHES "REPORT")
        print(BOLD COLOR YELLOW "${ARGV3}")
    elseif(${ARGV2} MATCHES "MACRO")
        if(${ARGV3} MATCHES "CC")
            EC_API_LOAD_CC()
        elseif(${ARGV3} MATCHES "CLANG")
            EC_API_LOAD_CLANG()
        endif()
    endif()
endif()
endmacro()



################################################################################
# Defining targets.
#       The configuration script will detect the compilers installed in PATH
#       and then it will generate appropriate headers.
#
# Targets:
#    1) eclibc                   Linux X86_64 shared library
#    2) eclibcStatic             Linux X86_64 static library
#    3) eclibc32                 Linux X86_32 shared library
#    4) eclibc32Static           Linux X86_32 static library
#    5) eclibcMinGW32            x86_64-w64-mingw32 shared library
#    6) eclibcMinGW32Static      x86_64-w64-mingw32 static library
#    7) eclibc32MinGW32          i686-w64-mingw32 shared library
#    8) eclibc32MinGW32Static    i686-w64-mingw32 static library
#    9) eclibcXC16               XC16 static library
#   10) eclibcXC32               XC32 static library
#   11) eclibcESP32              ESP32 static library
#   12) eclibcESP32s2            ESP32s2 static library
#   13) eclibcESP32s3            ESP32s3 static library
################################################################################

macro(EC_API_LOAD_NATIVE_LINUX)
    EC_API_SEARCH_FOR_COMPILER(
        "gcc"
        SHARED
        "DONT"
        ""
        eclibc
        eclibc
        "NONE"
        "lib"
        "lib"
        "include"
    )
EC_API_SEARCH_FOR_COMPILER(
    "gcc"
    SHARED
    "DONT"
    ""
    eclibc32
    eclibc32
    -m32
    "lib32"
    "lib32"
    "include"
)
EC_API_SEARCH_FOR_COMPILER(
    "gcc"
    STATIC
    "DONT"
    ""
    eclibcStatic
    eclibc
    "NONE"
    "lib"
    "lib"
    "include"
)
EC_API_SEARCH_FOR_COMPILER(
    "gcc"
    STATIC
    "MACRO"
    "CLANG"
    eclibc32Static
    eclibc32
    -m32
    "lib32"
    "lib32"
    "include"
)
endmacro()

macro(EC_API_LOAD_CLANG)
    EC_API_SEARCH_FOR_COMPILER(
        "clang"
        SHARED
        "DONT"
        ""
        eclibc
        eclibc
        "NONE"
        "lib"
        "lib"
        "include"
    )
EC_API_SEARCH_FOR_COMPILER(
    "clang"
    SHARED
    "DONT"
    ""
    eclibc32
    eclibc32
    -m32
    "lib32"
    "lib32"
    "include"
)
EC_API_SEARCH_FOR_COMPILER(
    "clang"
    STATIC
    "DONT"
    ""
    eclibcStatic
    eclibc
    "NONE"
    "lib"
    "lib"
    "include"
)
EC_API_SEARCH_FOR_COMPILER(
    "clang"
    STATIC
    "MACRO"
    "CC"
    eclibc32Static
    eclibc32
    -m32
    "lib32"
    "lib32"
    "include"
)
endmacro()

macro(EC_API_LOAD_CC)
    EC_API_SEARCH_FOR_COMPILER(
        "cc"
        SHARED
        "DONT"
        ""
        eclibc
        eclibc
        "NONE"
        "lib"
        "lib"
        "include"
    )
EC_API_SEARCH_FOR_COMPILER(
    "cc"
    SHARED
    "DONT"
    ""
    eclibc32
    eclibc32
    -m32
    "lib32"
    "lib32"
    "include"
)
EC_API_SEARCH_FOR_COMPILER(
    "cc"
    STATIC
    "DONT"
    ""
    eclibcStatic
    eclibc
    "NONE"
    "lib"
    "lib"
    "include"
)
EC_API_SEARCH_FOR_COMPILER(
    "cc"
    STATIC
    "REPORT"
    "-- No Linux-Native C compilers were found in PATH. Skipping linux targets"
    eclibc32Static
    eclibc32
    -m32
    "lib32"
    "lib32"
    "include"
)
endmacro()

macro(EC_API_LOAD_MINGW_64)
    EC_API_SEARCH_FOR_COMPILER(
        "x86_64-w64-mingw32-gcc"
        SHARED
        "DONT"
        ""
        eclibcMinGW32
        eclibcMinGW32
        "NONE"
        "x86_64-w64-mingw32/lib"
        "x86_64-w64-mingw32/lib"
        "x86_64-w64-mingw32/include"
    )
EC_API_SEARCH_FOR_COMPILER(
    "x86_64-w64-mingw32-gcc"
    STATIC
    "REPORT"
    "-- Unable to find MinGW32 X86_64 in PATH needed by eclibcMinGW32 and eclibcMinGW32Static. Skipping WindowsX64 targets"
    eclibcMinGW32Static
    eclibcMinGW32
    "NONE"
    "x86_64-w64-mingw32/lib"
    "x86_64-w64-mingw32/lib"
    "x86_64-w64-mingw32/include"
)
endmacro()

macro(EC_API_LOAD_MINGW_32)
    EC_API_SEARCH_FOR_COMPILER(
        "i686-w64-mingw32-gcc"
        SHARED
        "DONT"
        ""
        eclibc32MinGW32
        eclibc32MinGW32
        "NONE"
        "i686-w64-mingw32/lib"
        "i686-w64-mingw32/lib"
        "i686-w64-mingw32/include"
    )
EC_API_SEARCH_FOR_COMPILER(
    "i686-w64-mingw32-gcc"
    STATIC
    "REPORT"
    "-- Unable to find MinGW32 i686 in PATH needed by eclibc32MinGW32 and eclibc32MinGW32Static. Skipping WindowsX86 targets"
    eclibc32MinGW32Static
    eclibc32MinGW32
    "NONE"
    "i686-w64-mingw32/lib"
    "i686-w64-mingw32/lib"
    "i686-w64-mingw32/include"
)
endmacro()

macro(EC_API_LOAD_MICROCHIP)
    EC_API_SEARCH_FOR_COMPILER(
        "xc16-gcc"
        STATIC
        "REPORT"
        "-- Unable to find XC16 in PATH needed by eclibcXC16. Skipping 16bit PIC micro-controller unit targets"
        eclibcXC16
        eclibcXC16
        "NONE"
        "lib"
        "lib"
        "include"
    )
EC_API_SEARCH_FOR_COMPILER(
    "xc32-gcc"
    STATIC
    "REPORT"
    "-- Unable to find XC32 in PATH needed by eclibcXC32. Skipping 32bit PIC micro-controller unit targets"
    eclibcXC32
    eclibcXC32
    "NONE"
    "lib"
    "lib"
    "include"
)
endmacro()

macro(EC_API_LOAD_ESP)
    EC_API_SEARCH_FOR_COMPILER(
        "xtensa-esp32-elf-gcc"
        STATIC
        "REPORT"
        "-- Unable to find xtensa-esp32-elf-gcc in PATH needed by eclibcESP32. Skipping ESP32 targets"
        eclibcESP32
        eclibcESP32
        "NONE"
        "lib"
        "lib"
        "include"
    )
EC_API_SEARCH_FOR_COMPILER(
    "xtensa-esp32s2-elf-gcc"
    STATIC
    "REPORT"
    "-- Unable to find xtensa-esp32s2-elf-gcc in PATH needed by eclibcESP32s2. Skipping ESP32s2 targets"
    eclibcESP32s2
    eclibcESP32s2
    "NONE"
    "lib"
    "lib"
    "include"
)
EC_API_SEARCH_FOR_COMPILER(
    "xtensa-esp32s3-elf-gcc"
    STATIC
    "REPORT"
    "-- Unable to find xtensa-esp32s3-elf-gcc in PATH needed by eclibcESP32s3. Skipping ESP32s3 targets"
    eclibcESP32s3
    eclibcESP32s3
    "NONE"
    "lib"
    "lib"
    "include"
)
endmacro()

################################################################################
# Searching for compilers and adding them to the targets
################################################################################
print(BOLD COLOR CYAN "-- Searching for installed compilers in PATH")
EC_API_LOAD_NATIVE_LINUX()
EC_API_LOAD_MINGW_64()
EC_API_LOAD_MINGW_32()
EC_API_LOAD_MICROCHIP()
EC_API_LOAD_ESP()

################################################################################
# updating operating system library files
################################################################################
install (CODE "execute_process(COMMAND ldconfig)")

