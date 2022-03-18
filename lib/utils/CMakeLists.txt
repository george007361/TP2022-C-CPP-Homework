add_library(utils STATIC src/utils.c)

target_include_directories(utils PUBLIC include)

# Test utils
if(TEST_UTILS)
    add_subdirectory(./tests)
endif()