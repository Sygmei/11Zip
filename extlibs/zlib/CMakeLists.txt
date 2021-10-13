project(zlib)

file(GLOB ZLIB_HEADERS include/zlib/*.h)
file(GLOB ZLIB_SOURCES src/*.c)

add_library(zlib ${ZLIB_HEADERS} ${ZLIB_SOURCES})

target_compile_definitions(zlib PUBLIC ZLIB_COMPAT)

target_include_directories(zlib
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/zlib>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/zlib>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
