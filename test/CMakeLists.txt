macro(package_add_test TESTNAME)
    # create an executable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})
    # link the Google test infrastructure, mocking library, and a default main function to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_include_directories(${TESTNAME} PRIVATE ../include)
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
    gtest_discover_tests(${TESTNAME}
            # set a working directory so your project root so that you can find test data via paths relative to the project root
            WORKING_DIRECTORY ..
            PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(basic basic.cpp
        ../src/graph.cpp
        ../include/abstract_algorithm.hpp
        ../src/topsort/basic_topsort.cpp
        ../src/topsort/topsort_checker.cpp
)

package_add_test(topsort topsort_test.cpp
        ../src/graph.cpp
        ../include/abstract_algorithm.hpp
        ../src/topsort/basic_topsort.cpp
        ../src/topsort/topsort_checker.cpp
)
package_add_test(mst mst_test.cpp
        ../src/graph.cpp
        ../include/abstract_algorithm.hpp
        ../src/mst/basic_mst.cpp
        ../src/mst/mst_checker.cpp
)
