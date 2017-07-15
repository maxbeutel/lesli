project(lesli)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3 -g") # @FIXME debug flags

# @FIXME hardcoded readline path
include_directories("/usr/local/Cellar/readline/7.0.1/lib")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# executable
set(lesliSources src/lesli/lesli.cpp)

add_executable(lesli ${lesliSources})
target_link_libraries(lesli readline)

# tests
enable_testing()

# @FIXME add proper dependencies here, so that make knows when to rebuild
add_executable(util_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/util_test.cpp")
add_test(util_test util_test)
