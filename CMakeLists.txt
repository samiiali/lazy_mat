cmake_minimum_required(VERSION 3.10)

project(lazy_mat LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# adding support for target_sources
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0079 NEW)

include(git_ver)
git_ver(GIT_TAG GIT_BRANCH GIT_COMMIT_HASH)
message ("++ Git current tag: ${GIT_TAG}")
message ("++ Git current branch: ${GIT_BRANCH}")
message ("++ Git commit hash: ${GIT_COMMIT_HASH}")

include_directories(src)

add_compile_options("-Wshadow;-Werror")
add_executable(lazy_mat)
add_executable(tests)

add_subdirectory(src)
add_subdirectory(test)

set(GTEST_ROOT "~/Programs/googletest/install")
find_package(GTest)
target_link_libraries(tests GTest::GTest GTest::Main)

include(CTest)
gtest_discover_tests(tests)

include(CodeCoverage)
append_coverage_compiler_flags()

setup_target_for_coverage_gcovr_xml(
    NAME xmlcov
    EXECUTABLE tests
    DEPENDENCIES tests
    BASE_DIRECTORY "../"
    EXCLUDE "/usr/*;${GTEST_ROOT}/*;src/main.cpp;test/tests.cpp"
)
setup_target_for_coverage_gcovr_html(
    NAME htmlcov
    EXECUTABLE tests
    DEPENDENCIES tests
    BASE_DIRECTORY "../"
    EXCLUDE "/usr/*;${GTEST_ROOT}/*;src/main.cpp;test/tests.cpp"
)
setup_target_for_coverage_lcov(
    NAME cov
    EXECUTABLE tests
    DEPENDENCIES tests
    BASE_DIRECTORY "../"
    EXCLUDE "/usr/*;${GTEST_ROOT}/*;src/main.cpp;test/tests.cpp"
)
