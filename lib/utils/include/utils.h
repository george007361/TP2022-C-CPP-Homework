#ifndef LIB_UTILS_INCLUDE_UTILS_H_
#define LIB_UTILS_INCLUDE_UTILS_H_

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE_MB 100
#define BUFF_SIZE_BYTES (BUFF_SIZE_MB * 1048576)

int read_arguments(char **filepath, const int argc, char *const argv[]);
int open_file(FILE **file, const char *filepath);
void usage();
int free_array(int **arr, size_t *size);
int read_array_from_file(int **arr, size_t *size, FILE *file);
int *init_array(size_t *size);

#endif // LIB_UTILS_INCLUDE_UTILS_H_
