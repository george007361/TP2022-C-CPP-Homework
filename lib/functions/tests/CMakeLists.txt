add_executable(test_functions test_functions.cpp)

target_link_libraries(test_functions gtest functions -lpthread)

add_test(NAME test_functions COMMAND test_functions)