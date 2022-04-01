add_executable(test_task test_task.cpp)

target_link_libraries(test_task gtest task -lpthread)

add_test(NAME test_task COMMAND test_task)