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

