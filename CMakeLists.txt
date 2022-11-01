# Preamble
cmake_minimum_required(VERSION 3.23)
project(pgeo)


# Main targets built by this project
add_subdirectory(src)


# Tests
option(PGEO_ENABLE_TESTS "Enable building the tests of PGEO library" ON)

if (${PGEO_ENABLE_TESTS})
    add_subdirectory(tests)
endif()