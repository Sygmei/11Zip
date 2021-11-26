cmake_minimum_required(VERSION 3.12)

project(elzip)

option(ELZIP_EXCLUDE_ZLIB "Use this to exclude internal zlib copy." OFF)
option(ELZIP_EXCLUDE_MINIZIP "Use this to exclude internal minizip copy." OFF)

if(NOT ELZIP_EXCLUDE_ZLIB)
    add_subdirectory(extlibs/zlib EXCLUDE_FROM_ALL)
endif()
if(NOT ELZIP_EXCLUDE_MINIZIP)
    set(MZ_ZLIB OFF)
    set(MZ_ZSTD OFF)
    add_subdirectory(extlibs/minizip EXCLUDE_FROM_ALL)
endif()

file(GLOB LZIP_HEADERS include/elzip/*.hpp)

if (USE_FILESYSTEM_FALLBACK)
    set(ELZIP_CPP src/elzip_fs_fallback.cpp)
else()
    set(ELZIP_CPP src/elzip.cpp)
endif()

file(GLOB LZIP_SOURCES
    ${ELZIP_CPP}
    src/unzipper.cpp
    src/zipper.cpp
)

add_library(elzip ${LZIP_HEADERS} ${LZIP_SOURCES})
target_link_libraries(elzip minizip)

if (USE_FILESYSTEM_FALLBACK)
    target_link_libraries(elzip tinydir)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(elzip stdc++fs)
endif()

target_include_directories(elzip
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/elzip>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extlibs>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
# NOTE(assertores): zlib renames the file zconf.h into zconf.h.included
# because the file is generated in the build folder.
# see https://github.com/madler/zlib/issues/133
if(NOT ELZIP_EXCLUDE_ZLIB)
target_include_directories(elzip
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/extlibs/zlib
)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)