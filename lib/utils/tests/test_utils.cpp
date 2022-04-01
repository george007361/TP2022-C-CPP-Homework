#include "gtest/gtest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "utils.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(TestOpenFileFunc, NoErr) {
  char *fname = realpath("./examples/ex1.txt", NULL);
  FILE *file;
  EXPECT_EQ(open_file(&file, fname), SUCCESS);
  if (fname) {
    free(fname);
  }
  fclose(file);
}

TEST(TestOpenFileFunc, NullPtrParam) {
  FILE *file;
  EXPECT_EQ(open_file(nullptr, "file"), ERROR_NULL_PTR_PARAM);
  EXPECT_EQ(open_file(&file, nullptr), ERROR_NULL_PTR_PARAM);
//   fclose(file);
}

TEST(TestOpenFileFunc, NoSuchFile) {
  const char *fname = "./file.file";
  FILE *file;
  EXPECT_EQ(open_file(&file, fname), ERROR_CANT_OPEN_FILE);
//   fclose(file);
}

TEST(TestFreeArrayFunc, NoErr) {
  int *arr = (int *)malloc(sizeof(int));
  size_t size = 1;
  EXPECT_EQ(free_array(&arr, &size), SUCCESS);
  EXPECT_EQ(arr, nullptr);
  EXPECT_EQ(size, 0);
  if (arr) {
    free(arr);
  }
}

TEST(TestFreeArrayFunc, NullPtrParam) {
  int *arr;
  size_t size = 1;
  EXPECT_EQ(free_array(nullptr, &size), ERROR_NULL_PTR_PARAM);
  EXPECT_EQ(free_array(&arr, nullptr), ERROR_NULL_PTR_PARAM);
}

TEST(TestFreeArrayFunc, NullArr) {
  int *arr = nullptr;
  size_t size = 1;
  EXPECT_EQ(free_array(&arr, &size), SUCCESS);
  EXPECT_EQ(arr, nullptr);
  EXPECT_EQ(size, 0);
}

TEST(ReadArrayFromFileFunc, NullPtrParam) {

  int *arr;
  FILE *f;
  size_t size;

  EXPECT_EQ(read_array_from_file(nullptr, &size, f), ERROR_NULL_PTR_PARAM);
  EXPECT_EQ(read_array_from_file(&arr, nullptr, f), ERROR_NULL_PTR_PARAM);
  EXPECT_EQ(read_array_from_file(&arr, &size, nullptr), ERROR_NULL_PTR_PARAM);
}


