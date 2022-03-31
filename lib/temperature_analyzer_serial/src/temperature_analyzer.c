#include "temperature_analyzer.h"
// Serial

delta_temperature_t init_delta_temp() {
  // int delta;
  // size_t index;

  delta_temperature_t dt = {0, -1};

  return dt;
}

part_t init_part(size_t offset, int *arr, size_t len, int prev_elem,
                 long long prev_elem_index,
                 delta_temperature_t *max_delta_temperature) {
  part_t part = {
      offset, arr, len, prev_elem, prev_elem_index, max_delta_temperature};

  return part;
}

int find_max_temperature_delta_in_array(part_t *part) {
  if (!part || !part->arr) {
    return EXIT_FAILURE;
  }
  // Check prev last elem
  if (part->prev_elem_index != -1) {
    if (part->arr[0] - part->prev_elem > part->max_delta_temperature->delta) {
      part->max_delta_temperature->delta = part->arr[0] - part->prev_elem;
      part->max_delta_temperature->index = part->prev_elem_index;
    }
  }

  // Check elems in this part
  for (size_t i = 0; i < part->len - 1; i++) {
    if (part->arr[i + 1] - part->arr[i] > part->max_delta_temperature->delta) {
      part->max_delta_temperature->delta = part->arr[i + 1] - part->arr[i];
      part->max_delta_temperature->index = part->offset + i;
    }
  }

  // Remember last elem and change offset
  part->prev_elem_index = part->offset + part->len - 1;
  part->prev_elem = part->arr[part->len - 1];

  return EXIT_SUCCESS;
}
