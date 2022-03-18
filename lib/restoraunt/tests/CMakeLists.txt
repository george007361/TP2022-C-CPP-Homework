add_executable(test_restoraunt test_restoraunt.cpp)

target_link_libraries(test_restoraunt gtest restoraunt -lpthread)

add_test(NAME test_restoraunt COMMAND test_restoraunt)