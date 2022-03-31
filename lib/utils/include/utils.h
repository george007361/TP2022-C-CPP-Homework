#ifndef LIB_UTILS_INCLUDE_UTILS_H_
#define LIB_UTILS_INCLUDE_UTILS_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE_MB 400
#define BUFF_SIZE_BYTES (BUFF_SIZE_MB * 1024 * 1024)
// #define BUFF_SIZE_BYTES 32

#define NULL_PTR_PARAM_ERR_MSG                                                 \
  "Some params given to func as address are null ptr "
#define CANT_OPEN_FILE_ERR_MSG "Cant open file"
#define FILE_ERROR_ERR_MSG "File error"
#define CANT_MALLOC_ERR_MSG "Cant malloc memory"
#define CANT_REALLOC_ERR_MSG "Cant realloc memory"

enum return_codes {
  SUCCESS,
  SUCCESS_ALL_DATA,
  SUCCESS_NOT_ALL_DATA,
  ERROR_WRONG_USAGE,
  ERROR_NULL_PTR_PARAM,
  ERROR_MALLOC,
  ERROR_REALLOC,
  ERROR_WRONG_PATH,
  ERROR_CANT_OPEN_FILE,
  ERORR_FILE_ERROR,
  ERROR_READING_FILE
};

int open_file(FILE **file, const char *filepath);
int free_array(int **arr, size_t *size);
int read_array_from_file(int **arr, size_t *size, FILE *file);

#endif // LIB_UTILS_INCLUDE_UTILS_H_
