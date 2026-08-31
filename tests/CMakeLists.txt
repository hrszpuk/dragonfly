include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE DRAGONFLY_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(dragonfly_tests ${DRAGONFLY_TEST_SOURCES})

target_link_libraries(dragonfly_tests
    PRIVATE
        dragonfly_core
        GTest::gtest_main
)

target_include_directories(dragonfly_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(dragonfly_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(dragonfly_tests)