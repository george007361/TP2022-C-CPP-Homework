#include <stdio.h>
#include <string.h>

#include "functions.h"

char read_char() {
  char c;
  while ((c = getchar()) != '\0' && c != EOF && c == '\n') {
  }
  return c != '\n' ? c : '\0';
}

int read_int(int *is_err) {
  int res = 0;
  char c;
  while ((c = getchar()) != EOF && c != '\n') {
    if (c < '0' || c > '9') {
      while ((c = getchar()) != '\n' && c != '\0' && c != EOF) {
      }
      fprintf(stderr, "Tried to read int, but it is not a number\n");
      if (is_err)
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

  buf.buff[buf.size] = '\0';

  return buf.buff;
}

// char *read_str() {
//   buffer buf = {(char *)malloc(sizeof(char) * CHUNK_SIZE), CHUNK_SIZE, 0};
//   if (!buf.buff) {
//     fprintf(stderr, "Cant malloc read_str\n");
//     return NULL;
//   }

//   size_t read = 0;
//     get
//   for (;;) {
//     size_t read = fread(buf.buff /* + buf.size */, sizeof(char), CHUNK_SIZE,
//     stdin); if (read == 0)
//       break;
//     buf.size += read;

//     char *nbuff =
//         (char *)realloc(buf.buff, sizeof(char) * (buf.capacity +=
//         CHUNK_SIZE));

//     if (!nbuff) {
//       fprintf(stderr, "Error realloc mem in read_str\n");
//       free(buf.buff);
//       return NULL;
//     }
//     buf.buff = nbuff;
//   }

//   // while (!feof(stdin)) {
//   //   char *nbuff =
//   //       (char *)realloc(buf.buff, sizeof(char) * (buf.capacity +=
//   //       CHUNK_SIZE));

//   //   if (!nbuff) {
//   //     fprintf(stderr, "Error realloc mem in read_str\n");
//   //     free(buf.buff);
//   //     return NULL;
//   //   }
//   //   buf.buff = nbuff;

//   //   int a = feof(stdin);

//   //   fgets(buf.buff, CHUNK_SIZE, stdin);
//   //   int b = feof(stdin);

//   //   if (ferror(stdin)) {
//   //     fprintf(stderr, "Error read stdin in read_str()\n");
//   //     free(buf.buff);
//   //     return NULL;
//   //   }
//   // }

//   if ((buf.size = strlen(buf.buff)) < buf.capacity - 1) {
//     char *nbuf = (char *)realloc(buf.buff, sizeof(char) * (buf.size + 1));
//     if (!nbuf) {
//       fprintf(stderr, "Error realloc buffer read_str\n");
//     } else {
//       buf.buff = nbuf;
//     }
//   }
//   return buf.buff;
// }
