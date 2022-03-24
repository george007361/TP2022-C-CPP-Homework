#ifndef LIB_TEMPERATURE_ANALYZER_SERIAL_INCLUDE_TEMPERATURE_ANALYZER_H_
#define LIB_TEMPERATURE_ANALYZER_SERIAL_INCLUDE_TEMPERATURE_ANALYZER_H_

#include <stdlib.h>

// typedef struct max_delta_t {
//   int delta;
//   size_t index;

//   int last_number;
//   size_t last_index;

//   size_t offset;
// } max_delta_t;

typedef struct {
  int delta;
  long long index;
} delta_temperature_t;

typedef struct {
  size_t offset;
  int *arr;
  size_t len;

  int prev_elem;
  long long prev_elem_index;

  delta_temperature_t *max_delta_temperature;
} part_t;

delta_temperature_t init_delta_temp();
part_t init_part(size_t offset, int *arr, size_t len, int prev_elem,
                 long long prev_elem_index,
                 delta_temperature_t *max_delta_temperature);

int find_max_temperature_delta_in_array(part_t *part);

#endif // LIB_TEMPERATURE_ANALYZER_SERIAL_INCLUDE_TEMPERATURE_ANALYZER_H_
