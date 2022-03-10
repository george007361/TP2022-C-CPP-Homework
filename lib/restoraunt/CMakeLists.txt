add_library(restoraunt SHARED src/restoraunt.c)

target_include_directories(restoraunt PUBLIC include)

target_link_libraries(restoraunt PUBLIC functions)
