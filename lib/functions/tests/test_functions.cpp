#include "gtest/gtest.h"

extern "C" {
#include "functions.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}




