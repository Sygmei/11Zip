project(minizip)

file(GLOB MZIP_HEADERS include/minizip/*.h)
file(GLOB MZIP_SOURCES src/*.c)

if (NOT WIN32)
    list(REMOVE_ITEM MZIP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/mz_crypt_win32.c)
    list(REMOVE_ITEM MZIP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/mz_os_win32.c)
    list(REMOVE_ITEM MZIP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/mz_strm_os_win32.c)
ENDIF()
if (NOT POSIX)
    list(REMOVE_ITEM MZIP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/mz_os_posix.c)
    list(REMOVE_ITEM MZIP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/mz_strm_os_posix.c)
endif()
if (NOT APPLE)
    list(REMOVE_ITEM MZIP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/mz_crypt_apple.c)
endif()

add_library(minizip ${MZIP_HEADERS} ${MZIP_SOURCES})

target_link_libraries(minizip zlib)

target_compile_definitions(minizip PUBLIC HAVE_ZLIB)
target_compile_definitions(minizip PUBLIC HAVE_WZAES)

target_include_directories(minizip
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/minizip>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
