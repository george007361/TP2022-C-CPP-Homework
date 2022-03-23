#ifndef LIB_TEMPERATURE_ANALYZER_
#define LIB_TEMPERATURE_ANALYZER_

#include <stdlib.h>

typedef struct max_delta_t {
  size_t index;
  int delta;
} max_delta_t;

int find_max_temperature_delta(max_delta_t *max_delta, const int * const arr, const size_t size);

#endif // LIB_TEMPERATURE_ANALYZER_