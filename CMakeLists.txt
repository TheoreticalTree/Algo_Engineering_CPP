cmake_minimum_required(VERSION 3.16)
project(Algo_Engineering_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# project
add_subdirectory(src)

# executable
add_executable(main
        src/main.cpp
        )

target_include_directories(main
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

# overwrite install() command with a dummy macro that is a nop
macro (install)
endmacro ()


# tests
option(TESTS "Build the tests" ON)
if (TESTS)
    enable_testing()
    add_subdirectory(extlibs/gtest)
    include(GoogleTest)
    add_subdirectory(test)
endif ()

# benchmark
option(BENCHMARK "Additional Code" OFF)
if (BENCHMARK)
    add_subdirectory(extlibs/googlebenchmark)
    add_executable(test_benchmark)
    target_include_directories(test_benchmark
            PRIVATE
            ${PROJECT_SOURCE_DIR}/include
            )
    target_link_libraries(test_benchmark
            benchmark::benchmark)
endif ()