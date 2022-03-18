add_executable(test_utils test_utils.cpp)

target_link_libraries(test_utils gtest utils -lpthread)

add_test(NAME test_utils COMMAND test_utils)