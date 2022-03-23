add_library(task STATIC src/task.c)

target_include_directories(task PUBLIC include)

target_link_libraries(task PUBLIC utils temperature_analyzer)

# Test utils
if(TEST_TASK)
    add_subdirectory(./tests)
endif()