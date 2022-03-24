add_library(temperature_analyzer STATIC src/temperature_analyzer.c)

target_include_directories(temperature_analyzer PUBLIC include)

# Test utils
if(TEST_TEMPERATURE_ANALYZER)
    add_subdirectory(./tests)
endif()