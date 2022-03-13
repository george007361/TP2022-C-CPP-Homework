#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>

extern "C" {
#include "functions.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(test_read_char, one_char) {
  char *buf = "#";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('#', read_char(f));

  fclose(f);
}

TEST(test_read_char, new_string_symb_in_input) {
  char *buf = "\n\n#\n";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('#', read_char(f));

  fclose(f);
}

TEST(test_read_char, empty_input) {
  char *buf = "\0";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('\0', read_char(f));

  fclose(f);
}

TEST(test_read_char, new_string_symb_in_empty_input) {
  char *buf = "\n\n\n\0";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  EXPECT_EQ('\0', read_char(f));

  fclose(f);
}

TEST(test_read_int, no_err_normal_input) {
  char *buf = "123";
  puts(buf);
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int is_err = 0;

  EXPECT_EQ(123, read_int(&is_err, f));
  EXPECT_FALSE(is_err);

  fclose(f);
}

TEST(test_read_int, err_not_number_input) {
  char *buf = "12X3";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int is_err = 0;

  EXPECT_EQ(0, read_int(&is_err, f));
  EXPECT_TRUE(is_err);

  fclose(f);
}

TEST(test_read_int, err_empty_input) {
  char *buf = "\0";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int is_err = 0;

  EXPECT_EQ(0, read_int(&is_err, f));
  EXPECT_TRUE(is_err);

  fclose(f);
}

TEST(test_read_int, err_empty_strs_input) {
  char *buf = "\n\n\n\n";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");
  int is_err = 0;

  EXPECT_EQ(0, read_int(&is_err, f));
  EXPECT_TRUE(is_err);

  fclose(f);
}

TEST(test_read_str, noerr_input) {
  char *buf = "Hello!";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  char *res = read_str(f);
  EXPECT_TRUE(!strcmp("Hello!", res));
  if (res)
    free(res);
  fclose(f);
}

TEST(test_read_str, noerr_empty_str_input) {
  char *buf = "";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  char *res = read_str(f);
  EXPECT_TRUE(!strcmp("", res));
  if (res)
    free(res);
  fclose(f);
}
