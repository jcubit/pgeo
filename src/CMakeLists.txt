# Project wide setup
set(CMAKE_CXX_STANDARD 20)

add_library(pgeo INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Point.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Vector3.h>
)
