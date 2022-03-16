#include "gtest/gtest.h"

#include <stdio.h>
#include <string.h>

extern "C" {
#include "utils.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(TestReadCharFunc, OneChar) {
  char *buf = "#";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('#', read_char(f));

  fclose(f);
}

TEST(TestReadCharFunc, NewStringSymbInLine) {
  char *buf = "\n\n#\n";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('#', read_char(f));

  fclose(f);
}

TEST(TestReadCharFunc, EmptyInput) {
  char *buf = "\0";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('\0', read_char(f));

  fclose(f);
}

TEST(TestReadCharFunc, NewStringSymbInEmptyLine) {
  char *buf = "\n\n\n\0";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('\0', read_char(f));

  fclose(f);
}

TEST(TestReadIntFunc, NoErrors) {
  char *buf = "123";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int isErr = 0;

  EXPECT_EQ(123, read_int(&isErr, f));
  EXPECT_FALSE(isErr);

  fclose(f);
}

TEST(TestReadIntFunc, ErrorNotNubmer) {
  char *buf = "12X3";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int isErr = 0;

  EXPECT_EQ(0, read_int(&isErr, f));
  EXPECT_TRUE(isErr);

  fclose(f);
}

TEST(TestReadIntFunc, ErrorEmptyInput) {
  char *buf = "\0";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int isErr = 0;

  EXPECT_EQ(0, read_int(&isErr, f));
  EXPECT_TRUE(isErr);

  fclose(f);
}

TEST(TestReadIntFunc, ErrorOnlyNewLineSybs) {
  char *buf = "\n\n\n\n";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int isErr = 0;

  EXPECT_EQ(0, read_int(&isErr, f));
  EXPECT_TRUE(isErr);

  fclose(f);
}

TEST(TestReadStrFunc, NoError) {
  char *buf = "Hello!";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  char *res = read_str(f);
  EXPECT_TRUE(!strcmp("Hello!", res));
  if (res)
    free(res);
  fclose(f);
}

TEST(TestReadStrFunc, NoErrorEmptyInput) {
  char *buf = "";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  char *res = read_str(f);
  EXPECT_TRUE(!strcmp("", res));
  if (res)
    free(res);
  fclose(f);
}
