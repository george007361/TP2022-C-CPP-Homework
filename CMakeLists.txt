cmake_minimum_required(VERSION 3.12)

project(HW1_RESTORAUNT)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDART_REQURED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# COVERAGE

option(COVERAGE "Generate coverage files" OFF)
if(COVERAGE)
    set(TEST_ALL ON)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif(COVERAGE)

# END COVERAGE

# TESTS
set(BUILD_TESTS OFF)
option(TEST_FUNCTIONS "Test functions.c" OFF)
option(TEST_RESTORAUNT "Test restoraunt.c" OFF)
option(TEST_ALL "Test all" OFF)

if(TEST_ALL)
    set(TEST_FUNCTIONS ON)
    set(TEST_RESTORAUNT ON)
endif(TEST_ALL)

if(TEST_RESTORAUNT)
    set(BUILD_TESTS ON)
endif(TEST_RESTORAUNT)

if(TEST_FUNCTIONS)
    set(BUILD_TESTS ON)
endif(TEST_FUNCTIONS)

if(BUILD_TESTS)
    add_subdirectory(./gtest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif(BUILD_TESTS)

# END TESTS

add_compile_options(-Wall -Wextra -pedantic -fPIC)

add_subdirectory(lib/restoraunt)
add_subdirectory(lib/functions)

add_executable(main src/main.c)
target_link_libraries(main restoraunt)

# --------------
# set(BUILD_TESTS OFF)
# option(TEST_GRAPHS "Enable graphs library test" OFF)
# option(TEST_PARSER "Enable parser library test" OFF)
# option(TEST_ALL "Enable all tests" OFF)
# option(WITH_COVERAGE "Add coverage estimation")
# option(WITH_SANITIZERS "Add sanitizers")

# if(WITH_COVERAGE)
#     set(BUILD_TESTS ON)
#     add_compile_options(--coverage)
#     add_link_options(--coverage)
# endif()

# if(WITH_SANITIZERS)
#     add_compile_options(-fno-omit-frame-pointer -g -fsanitize=address)
#     add_link_options(-fsanitize=address)
# endif()

# if(TEST_ALL)
#     set(TEST_GRAPHS  ON)
#     set(TEST_PARSER  ON)
#     set(BUILD_TESTS  ON)
# endif()

# if(BUILD_TESTS)
#     add_subdirectory(./gtest)
#     enable_testing()
#     include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# endif()


# add_subdirectory(lib/utils)
# add_subdirectory(lib/graphs)
# option(USE_SERIAL "Enable using parallel library" NO)
# if(USE_SERIAL)
#     message("Using serial parser")
#     add_subdirectory(lib/serial_parser) 
# else()
#     message("Using parallel parser")
#     add_subdirectory(lib/parallel_parser)
# endif()
