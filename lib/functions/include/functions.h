#ifndef LIB_FUNCTIONS_INCLUDE_FUNCTIONS_H_
#define LIB_FUNCTIONS_INCLUDE_FUNCTIONS_H_

#include <stdlib.h>

#define CHUNK_SIZE 32

typedef struct buffer {
  char *buff;
  size_t capacity;
  size_t size;
} buffer;

char read_char();
int read_int(int *is_err);
char *read_str();

#endif // LIB_FUNCTIONS_INCLUDE_FUNCTIONS_H_
