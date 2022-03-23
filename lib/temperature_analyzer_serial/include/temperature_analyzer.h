#ifndef LIB_TEMPERATURE_ANALYZER_SERIAL_INCLUDE_TEMPERATURE_ANALYZER_H_
#define LIB_TEMPERATURE_ANALYZER_SERIAL_INCLUDE_TEMPERATURE_ANALYZER_H_

#include <stdlib.h>

typedef struct max_delta_t {
  int delta;
  size_t index;

  int last_number;
  size_t last_index;

  size_t offset;
} max_delta_t;

int find_max_temperature_delta_in_array(max_delta_t *max_delta,
                                        const int *const arr,
                                        const size_t size);

#endif // LIB_TEMPERATURE_ANALYZER_SERIAL_INCLUDE_TEMPERATURE_ANALYZER_H_
