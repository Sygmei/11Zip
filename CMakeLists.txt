cmake_minimum_required(VERSION 3.12)

project(elzip)

option(ELZIP_EXCLUDE_MINIZIP "Use this to exclude internal minizip copy." OFF)
option(ELZIP_TESTS "includes tests for 11Zip." OFF)
option(ELZIP_DECOMPRESS_ONLY "Only support decompression" OFF)

if(NOT ELZIP_EXCLUDE_MINIZIP)
    set(MZ_BZIP2 OFF)
    set(MZ_ICONV OFF)
    set(MZ_LZMA OFF)
    set(MZ_SIGNING OFF)
    set(MZ_ZSTD OFF)
    set(MZ_FETCH_LIBS ON)
    # Enabling MZ_COMPAT
    set(MZ_COMPAT ON)

    if (ELZIP_DECOMPRESS_ONLY)
        set(MZ_LIBCOMP OFF)
        set(MZ_PKCRYPT OFF)
        set(MZ_WZAES OFF)
        set(MZ_OPENSSL OFF)
        set(MZ_LIBBSD OFF)
        set(MZ_ZLIB OFF)
        set(MZ_PKCRYPT OFF)
        set(MZ_WZAES OFF)

        set(MZ_DECOMPRESS_ONLY ON)
    else()
        set(MZ_ZLIB ON)
        set(MZ_PKCRYPT ON)
        set(MZ_WZAES ON)

    endif()

    add_subdirectory(extlibs/minizip EXCLUDE_FROM_ALL)
endif()

list(FIND "${CMAKE_CXX_COMPILE_FEATURES}" "cxx_std_17" __hascxx17)
if ("${__hascxx17}" STREQUAL "-1")
    set(HAS_FILESYSTEM ON)
else()
    set(HAS_FILESYSTEM NO)
endif()

file(GLOB LZIP_HEADERS include/elzip/*.hpp)

if (NOT HAS_FILESYSTEM)
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

if (NOT HAS_FILESYSTEM)
    target_link_libraries(elzip tinydir)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(elzip stdc++fs)
endif()

if (HAS_FILESYSTEM)
    target_compile_features(elzip PUBLIC
        cxx_std_17 # Require at least c++17
    )
else()
    target_compile_features(elzip PUBLIC
        cxx_std_11 # Require at least c++11
    )
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

if(ELZIP_TESTS)
    set(BUILD_TESTING ON)
    include(CTest)
    add_subdirectory(tests)
endif()
