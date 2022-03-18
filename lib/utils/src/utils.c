#include "utils.h"

#include <string.h>

char read_char(FILE *stream) {
  if (!stream) {
    fprintf(stderr, "Stream ptr is null\n");
    return END_OF_FILE;
  }

  char c;
  while ((c = getc(stream)) != END_OF_FILE && c != EOF && c == END_OF_STRING) {
  }

  return c != END_OF_STRING ? c : END_OF_FILE;
}

int read_int(int *is_err, FILE *stream) {
  if (!stream) {
    if (is_err) {
      *is_err = 1;
    }
    fprintf(stderr, "Stream ptr is null\n");
    return 0;
  }

  int res = 0;
  int is_empty = 1;
  char c;

  while ((c = getc(stream)) != END_OF_FILE && c != END_OF_STRING) {
    if (c < '0' || c > '9') {
      while ((c = getc(stream)) != END_OF_STRING && c != END_OF_FILE &&
             c != EOF) {
      }
      fprintf(stderr, "Tried to read int, but it is not a number\n");
      if (is_err) {
        *is_err = 1;
      }

      return 0;
    }

    is_empty = 0;
    res = res * 10 + (c - '0');
  }

  *is_err = is_empty ? 1 : 0;

  return res;
}

char *read_str(FILE *stream) {
  if (!stream) {
    fprintf(stderr, "Stream ptr is null\n");
    return NULL;
  }

  buffer_t buf = {NULL, 0, 0};
  char c;

  while ((c = getc(stream)) != END_OF_STRING && c != END_OF_FILE && c != EOF) {
    if (buf.size == buf.capacity) {
      char *pnew_buff = realloc(
          buf.buff,
          buf.capacity += CHUNK_SIZE); //= buf.capacity ? buf.capacity *= 2 : 1

      if (!pnew_buff) {
        fprintf(stderr, "read_string error realloc buffer while reading\n");
        free(buf.buff);

        return NULL;
      }

      buf.buff = pnew_buff;
    }

    buf.buff[buf.size++] = (char)c;
  }

  char *pnew_buff =
      realloc(buf.buff, sizeof(char) * (buf.capacity = buf.size + 1));
  if (!pnew_buff) {
    fprintf(stderr, "read_string error realloc buffer\n");
    free(buf.buff);

    return NULL;
  }

  buf.buff = pnew_buff;
  buf.buff[buf.size] = END_OF_FILE;

  return buf.buff;
}
