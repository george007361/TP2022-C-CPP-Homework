add_library(restoraunt SHARED src/restoraunt.c)

target_include_directories(restoraunt PUBLIC include)

target_link_libraries(restoraunt PUBLIC utils)

# Test restoraunt
if(TEST_RESTORAUNT)
    add_subdirectory(./tests)
endif()