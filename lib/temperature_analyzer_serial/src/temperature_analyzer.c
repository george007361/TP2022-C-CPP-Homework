#include "temperature_analyzer.h"

int find_max_temperature_delta_in_array(max_delta_t *max_delta,
                                        const int *const arr,
                                        const size_t size) {
  if (!max_delta || !arr) {
    return EXIT_FAILURE;
  }

  // Check prev last elem
  if (max_delta->last_index) {
    if (arr[0] - max_delta->last_number > max_delta->delta) {
      max_delta->delta = arr[0] - max_delta->last_number;
      max_delta->index = max_delta->last_index;
    }
  }

  // Check elems in this part
  for (size_t i = 0; i < size - 1; i++) {
    if (arr[i + 1] - arr[i] > max_delta->delta) {
      max_delta->delta = arr[i + 1] - arr[i];
      max_delta->index = max_delta->offset + i;
    }
  }

  // Remember last elem and change offset
  max_delta->last_index = max_delta->offset + size - 1;
  max_delta->last_number = arr[size - 1];
  max_delta->offset += size;

  return EXIT_SUCCESS;
}
