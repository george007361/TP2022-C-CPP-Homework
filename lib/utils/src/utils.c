#include "utils.h"

int free_array(int **arr, size_t *size) {
  if (!arr || !size) {
    fprintf(stderr, "free_array() : %s\n", NULL_PTR_PARAM_ERR_MSG);

    return ERROR_NULL_PTR_PARAM;
  }
  if (*arr) {
    free(*arr);
    *arr = NULL;
  }
  *size = 0;

  return SUCCESS;
}

int open_file(FILE **file, const char *filepath) {
  if (!file || !filepath) {
    fprintf(stderr, "open_file() : %s\n", NULL_PTR_PARAM_ERR_MSG);

    return EXIT_FAILURE;
  }

  *file = fopen(filepath, "r");
  if (!*file) {
    fprintf(stderr, "open_file() : %s %s %s\n", CANT_OPEN_FILE_ERR_MSG,
            filepath, strerror(errno));

    return ERROR_CANT_OPEN_FILE;
  }

  return SUCCESS;
}

int read_array_from_file(int **arr, size_t *size, FILE *file) {
  if (!arr || !size || !file) {
    fprintf(stderr, "read_array_from_file() : %s\n", NULL_PTR_PARAM_ERR_MSG);

    return ERROR_NULL_PTR_PARAM;
  }
  free_array(arr, size);

  if (ferror(file)) {
    fprintf(stderr, "read_array_from_file() : %s\n", FILE_ERROR_ERR_MSG);

    return ERORR_FILE_ERROR;
  }

  if (feof(file)) {
    return SUCCESS_ALL_DATA;
  }

  int exit_code = SUCCESS_NOT_ALL_DATA;
  const size_t max_size = BUFF_SIZE_BYTES / sizeof(int);
  *arr = (int *)malloc(BUFF_SIZE_BYTES);
  if (!*arr) {
    fprintf(stderr, "read_array_from_file() : %s\n", CANT_MALLOC_ERR_MSG);

    return ERROR_MALLOC;
  }

  for (*size = 0; *size < max_size; *size += 1) {
    if (fscanf(file, "%i", &(*arr)[*size]) != 1) {
      if (feof(file)) {
        exit_code = SUCCESS_ALL_DATA;
        break;
      } else {
        fprintf(stderr, "read_array_from_file() : %s\n", CANT_MALLOC_ERR_MSG);

        free_array(arr, size);

        return ERROR_READING_FILE;
      }
    }
  }

  if (*size<max_size && * size> 0) {
    int *new_arr = (int *)realloc(*arr, *size * sizeof(int));
    if (!new_arr) {
      fprintf(stderr, "read_array_from_file() : %s\n", CANT_REALLOC_ERR_MSG);
    } else {
      *arr = new_arr;
    }
  }

  return exit_code;
}
