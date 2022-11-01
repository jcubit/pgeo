include(FetchContent)

FetchContent_Declare(
        mdspan
        GIT_REPOSITORY https://github.com/kokkos/mdspan.git
        GIT_TAG 9d1acac543053cbe6839273f550b1ece218e9696
)

add_subdirectory(mdspan)