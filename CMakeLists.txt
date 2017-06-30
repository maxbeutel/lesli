project(lesli)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3 -g") # @FIXME debug flags

# # enable pthreads for tests
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)

# SET(GTEST_HOME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest-release-1.8.0" CACHE STRING "Path to Googles test framework.")
# OPTION(TEST_ENABLE_MEMCHECK "Enable memcheck with valgrind." OFF)

# if(TEST_ENABLE_MEMCHECK)
#   MESSAGE(STATUS "Enable memcheck for test.")
#   SET(CTEST_OPTIONS "-D ExperimentalMemCheck --verbose")
# else()
#   SET(CTEST_OPTIONS "--verbose")
# endif()

# include_directories("${GTEST_HOME_DIR}/googletest/include")
# include_directories("${GTEST_HOME_DIR}/googlemock/include")

# link_directories("${GTEST_HOME_DIR}/build/googlemock/gtest")
# link_directories("${GTEST_HOME_DIR}/build/googlemock")

include_directories("/usr/local/Cellar/readline/7.0.1/lib")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# executable
set(lesliSources src/lesli/lesli.cpp)

add_executable(lesli ${lesliSources})
target_link_libraries(lesli readline)

# tests
# enable_testing()
# include(CTest)

# find_program(MEMORYCHECK_COMMAND valgrind)
# set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
# # valgrind suppressions file if needed
# #set(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/valgrind_suppress.txt")

# # test - index
# add_executable(stree_index_test tests/stree_index_test.cpp)
# add_test(stree_index_test stree_index_test)

# target_link_libraries(stree_index_test stree)
# target_link_libraries(stree_index_test gmock)
# target_link_libraries(stree_index_test gtest)
# target_link_libraries(stree_index_test Threads::Threads)

# # test - parser
# add_executable(stree_parser_test tests/stree_parser_test.cpp)
# add_test(stree_parser_test stree_parser_test)

# target_link_libraries(stree_parser_test stree)
# target_link_libraries(stree_parser_test gmock)
# target_link_libraries(stree_parser_test gtest)
# target_link_libraries(stree_parser_test Threads::Threads)

# ### !!! ADD UNIT TESTS HERE
# add_custom_target(check COMMAND ctest ${CTEST_OPTIONS}
#                   DEPENDS stree_index_test stree_parser_test)
