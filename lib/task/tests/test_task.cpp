#include "gtest/gtest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "task.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(RunTaskFunc, NullPtrParam) {
  int argv;
  EXPECT_EQ(run_task(argv, nullptr), EXIT_FAILURE);
}

TEST(FindMaxDeltaTempInFile, NullPtrParam) {
  delta_temperature_t dt;
  FILE *file;
  EXPECT_EQ(find_max_temperature_delta_in_file(&dt, nullptr), EXIT_FAILURE);
  EXPECT_EQ(find_max_temperature_delta_in_file(nullptr, file), EXIT_FAILURE);
}

TEST(FindMaxDeltaTempInFile, NoErr) {
  delta_temperature_t dt;
  char *fname = realpath("./examples/ex1.txt", NULL);
  FILE *file;
  EXPECT_EQ(find_max_temperature_delta_in_file(&dt, file), EXIT_SUCCESS);
  EXPECT_EQ(dt.delta, 2001);
  EXPECT_EQ(dt.index, 8);
  if (fname) {
    free(fname);
  }
  fclose(file);
}
