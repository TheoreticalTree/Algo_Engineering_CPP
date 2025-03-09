cmake_minimum_required(VERSION 3.16)
project(Algo_Engineering_CPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(default_build_type "Release")

# project
add_subdirectory(src)

# executable
add_executable(main
        src/main.cpp
        src/topsort/topsort_checker.cpp
        src/topsort/basic_topsort.cpp
        src/topsort/your_topsort.cpp
        src/graph.cpp
        src/mst/basic_mst.cpp
        src/mst/mst_checker.cpp
        src/mst/your_mst.cpp
)

target_include_directories(main
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

# executable
add_executable(generate_instances
        src/generate_instances.cpp
        src/topsort/topsort_checker.cpp
        src/topsort/basic_topsort.cpp
        src/topsort/your_topsort.cpp
        src/graph.cpp
        src/mst/basic_mst.cpp
        src/mst/mst_checker.cpp
        src/mst/your_mst.cpp
)

target_include_directories(main
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

# benchmark for top sort
add_executable(benchmark_topsort
        src/benchmark_topsort.cpp
        src/topsort/topsort_checker.cpp
        src/topsort/basic_topsort.cpp
        src/topsort/your_topsort.cpp
        src/graph.cpp
        data/topsort/topsort_instance_generator.hpp
)

target_include_directories(benchmark_topsort
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)

# benchmark for mst
add_executable(benchmark_mst
        src/benchmark_mst.cpp
        src/graph.cpp
        src/mst/basic_mst.cpp
        src/mst/mst_checker.cpp
        src/mst/your_mst.cpp
        data/mst/mst_instance_generator.hpp
)

target_include_directories(benchmark_mst
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
