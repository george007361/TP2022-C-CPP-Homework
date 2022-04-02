cmake_minimum_required(VERSION 3.12)

project(HW2_TEMPERATURE_LOGS)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDART_REQURED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -fPIC)

option(USE_SERIAL "User serial analyzer (def ON)" OFF)

set(BUILD_TESTS OFF)
option(TEST_UTILS "Test utils.c" OFF)
option(TEST_TASK "Test task.c" OFF)
option(TEST_TEMPERATURE_ANALYZER "Test temperature_analyzer.c" OFF)
option(TEST_ALL "Test all" OFF)

option(COVERAGE "Generate coverage files" OFF)

option(SANITIZERS "Use sanitizers" OFF)

# SANITIZERS

if(SANITIZERS)
    message("->Sanitizers flag ON")
    add_compile_options(-fno-omit-frame-pointer -g -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error)
    add_link_options(-fsanitize=address)
endif(SANITIZERS)

# END SANITIZERS

# COVERAGE

if(COVERAGE)
    message("->Coverage flag ON")
    set(TEST_ALL ON)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif(COVERAGE)

# END COVERAGE

# TESTS

if(TEST_ALL)
    message("->Test all flag ON")
    set(TEST_UTILS ON)
    set(TEST_TASK ON)
    set(TEST_TEMPERATURE_ANALYZER ON)
endif(TEST_ALL)

if(TEST_TASK)
    message("->Test task lib flag ON")
    set(BUILD_TESTS ON)
endif(TEST_TASK)

if(TEST_TEMPERATURE_ANALYZER)
    message("->Test analyzer lib flag ON")
    set(BUILD_TESTS ON)
endif(TEST_TEMPERATURE_ANALYZER)

if(TEST_UTILS)
    message("->Test utils lib flag ON")
    set(BUILD_TESTS ON)
endif(TEST_UTILS)

if(BUILD_TESTS)
    message("->Build tests flag ON")
    add_subdirectory(./gtest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif(BUILD_TESTS)

# END TESTS

if(USE_SERIAL)
    message("-> Using serial")
    add_subdirectory(lib/temperature_analyzer_serial)
else()
    message("-> Using parallel")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread  -lpthread")
    add_subdirectory(lib/temperature_analyzer_parallel)
endif()

add_subdirectory(lib/task)
add_subdirectory(lib/utils)

add_executable(main src/main.c)
target_link_libraries(main utils task)
