#include "gtest/gtest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "task.h"
#include "temperature_analyzer.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(TestParallelAlg, NoErr) {
  delta_temperature_t dt;
  char *fname = realpath("./examples/ex1.txt", NULL);
  FILE *file = fopen(fname, "r");
  EXPECT_EQ(find_max_temperature_delta_in_file(&dt, file), EXIT_SUCCESS);
  EXPECT_EQ(dt.delta, 2001);
  EXPECT_EQ(dt.index, 8);
  fclose(file);
}
