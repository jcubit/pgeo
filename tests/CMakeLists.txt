cmake_minimum_required (VERSION 3.22)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 #v1.12.1
)

# Populate and add to the main build Catch2, skipping over if already been populated
FetchContent_MakeAvailable(googletest)

add_executable(pgeoTest)

target_sources(pgeoTest PRIVATE
        test_main.cpp
        test_matrix.cpp
        test_matrix_views.cpp
        test_vector.cpp
        test_addition.cpp
        test_subtraction.cpp
        test_multiplication.cpp
        test_inverse.cpp
        test_point.cpp
        test_plane.cpp
        test_determinant.cpp
        test_join_and_meet.cpp
        test_line.cpp
        utilities.h
)

target_link_libraries(pgeoTest
        PRIVATE
        pgeo
        GTest::gtest_main
        GTest::gtest
        spdlog::spdlog
        )