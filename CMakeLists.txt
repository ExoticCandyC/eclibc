
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
                ${PROJECT_SOURCE_DIR}/ec/vector.c
                #${PROJECT_SOURCE_DIR}/ec/mutex.c
    )

set  (EC_API_HEADER_FILES
                ${EC_API_INCLUDE_DIR}/ec/map.h
                ${EC_API_INCLUDE_DIR}/ec/vector.h
                ${EC_API_INCLUDE_DIR}/ec/mutex.h
     )

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

set_target_properties(eclibcStatic   PROPERTIES OUTPUT_NAME eclibc)
set_target_properties(eclibc32       PROPERTIES OUTPUT_NAME eclibc32)
set_target_properties(eclibcStatic32 PROPERTIES OUTPUT_NAME eclibc32)

add_compile_options(-I"${EC_API_INCLUDE_DIR}" -O3 -flto -fPIC -ansi -pedantic -ftree-loop-vectorize -fstack-protector -Waggressive-loop-optimizations -Werror -Wpedantic -Wall -Wextra -Wfloat-equal -Wshadow -Wswitch-enum -Wcast-qual -Wconversion -Wundef -Wunused-macros -Wduplicated-cond -Wduplicated-branches)
add_link_options(-O3 -flto -fPIC -ansi -pedantic -ftree-loop-vectorize -fstack-protector -Waggressive-loop-optimizations -Werror -Wpedantic -Wall -Wextra -Wfloat-equal -Wshadow -Wswitch-enum -Wcast-qual -Wconversion -Wundef -Wunused-macros -Wduplicated-cond -Wduplicated-branches)

target_compile_options  (eclibc32       PUBLIC -m32)
target_compile_options  (eclibcStatic32 PUBLIC -m32)
target_link_options     (eclibc32       PUBLIC -m32)
target_link_options     (eclibcStatic32 PUBLIC -m32)

#shared library
set_target_properties(eclibc PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibc PROPERTIES SOVERSION 1)
target_include_directories(eclibc PUBLIC ${EC_API_INCLUDE_DIR} )
set_target_properties(eclibc PROPERTIES PUBLIC_HEADER "${EC_API_HEADER_FILES}")
install(TARGETS eclibc
    LIBRARY       DESTINATION "/usr/lib"
    ARCHIVE       DESTINATION "/usr/lib"
    RUNTIME       DESTINATION "/usr/bin"
    PUBLIC_HEADER DESTINATION "/usr/include/ec"
       )

#static library
set_target_properties(eclibcStatic PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibcStatic PROPERTIES SOVERSION 1)
target_include_directories(eclibcStatic PUBLIC ${EC_API_INCLUDE_DIR} )
install(TARGETS eclibcStatic
    LIBRARY       DESTINATION "/usr/lib"
    ARCHIVE       DESTINATION "/usr/lib"
       )

#shared32 library
set_target_properties(eclibc32 PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibc32 PROPERTIES SOVERSION 1)
target_include_directories(eclibc32 PUBLIC ${EC_API_INCLUDE_DIR} )
install(TARGETS eclibc32
    LIBRARY       DESTINATION "/usr/lib32"
    ARCHIVE       DESTINATION "/usr/lib32"
       )

#static32 library
set_target_properties(eclibcStatic32 PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(eclibcStatic32 PROPERTIES SOVERSION 1)
target_include_directories(eclibcStatic32 PUBLIC ${EC_API_INCLUDE_DIR} )
install(TARGETS eclibcStatic32
    LIBRARY       DESTINATION "/usr/lib32"
    ARCHIVE       DESTINATION "/usr/lib32"
       )


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ec/eclibc.pc.in ${CMAKE_CURRENT_SOURCE_DIR}/.pkgconfig/eclibc.pc @ONLY)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/.pkgconfig/eclibc.pc DESTINATION "/lib/pkgconfig")

#link eclibc32 targets to eclibc names in /usr/lib32
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.so.${PROJECT_VERSION} /usr/lib32/libeclibc.so.${PROJECT_VERSION} 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.so.${PROJECT_VERSION}\")")
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.so.${PROJECT_VERSION_MAJOR} /usr/lib32/libeclibc.so.${PROJECT_VERSION_MAJOR} 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.so.${PROJECT_VERSION_MAJOR}\")")
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.so /usr/lib32/libeclibc.so 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.so\")")
install (CODE "execute_process(COMMAND bash -c \"ln -s /usr/lib32/libeclibc32.a /usr/lib32/libeclibc.a 2> /dev/null\")")
install (CODE "execute_process(COMMAND echo \"-- Up-to-date: /usr/lib32/libeclibc.a\")")

install (CODE "execute_process(COMMAND ldconfig)")
install (CODE "execute_process(COMMAND pkg-config eclibc)")

