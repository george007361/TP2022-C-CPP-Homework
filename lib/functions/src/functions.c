#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

char read_char() {
  char c;
  while ((c = getchar()) != '\0' && c != EOF && c == '\n')
    ;
  return c != '\n' ? c : '\0';
}

int read_int(int *is_err) {
  int res = 0;
  char c;
  while ((c = getchar()) != EOF && c != '\n') {
    if (c < '0' || c > '9') {
      while ((c = getchar()) != '\n' && c != '\0' && c != EOF)
        ;
      fprintf(stderr, "Tried to read int, but it is not a number\n");
      *is_err = 1;
      return 0;
    }
    res = res * 10 + (c - '0');
  }
  return res;
}

char *read_str() {

  buffer buf = {NULL, 0, 0};
  char c;

  while ((c = getchar()) != '\n' && c != '\0' && c != EOF) {
    if (buf.size == buf.capacity) {
      buf.buff = realloc(buf.buff,
                         buf.capacity = buf.capacity ? buf.capacity *= 2 : 1);

      if (!buf.buff) {
        fprintf(stderr, "read_string error realloc buffer while reading\n");
        return NULL;
      }
    }

    buf.buff[buf.size++] = (char)c;
  }

  buf.buff = realloc(buf.buff, sizeof(char) * (buf.capacity = buf.size + 1));
  if (!buf.buff) {
    fprintf(stderr, "read_string error realloc buffer\n");
    return NULL;
  }

  buf.buff[buf.size] = '\0';

  return buf.buff;
}
