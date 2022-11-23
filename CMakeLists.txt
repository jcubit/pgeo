# Preamble
cmake_minimum_required(VERSION 3.23)
project(pgeo VERSION 0.0.1)

# Project wide setup
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Externally provided content
add_subdirectory(dependencies)

# Main targets built by this project
add_library(pgeo INTERFACE)

target_include_directories(pgeo
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

target_sources(pgeo
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo/Matrix.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo/MatrixEngine.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo/MatrixEngineSupport.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo/MatrixViewEngine.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo/Addition.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo/Multiplication.h>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include/pgeo/Inverse.h>
        )

target_compile_features(pgeo
        INTERFACE
        cxx_std_20
        )

target_link_libraries(pgeo
        INTERFACE
        std::mdspan
        )

# Tests
option(PGEO_ENABLE_TESTS "Enable building the tests of PGEO library" ON)

if (${PGEO_ENABLE_TESTS})
    add_subdirectory(tests)
endif()