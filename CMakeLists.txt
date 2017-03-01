cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(elzip)

file(GLOB PG_LZIP src/*.h)
file(GLOB HD_LZIP src/*.c)

add_library(elzip ${PG_LZIP} ${HD_LZIP})