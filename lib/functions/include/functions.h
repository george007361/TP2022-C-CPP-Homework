#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef struct buffer {
  char *buff;
  int capacity;
  int size;
} buffer;

char read_char();
int read_int(int *is_err);
char *read_str();

#endif // FUNCTIONS_H_