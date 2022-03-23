#include "temperature_analyzer.h"

int find_max_temperature_delta(max_delta_t *max_delta, const int *const arr,
                        const size_t size) {
  if (!max_delta || !arr) {
    return EXIT_FAILURE;
  }

  max_delta->delta = max_delta->index = 0;

  for (size_t i = 0; i < size - 1; i++) {
    if (arr[i + 1] - arr[i] > max_delta->delta) {
      max_delta->delta = arr[i + 1] - arr[i];
      max_delta->index = i;
    }
  }

  return EXIT_SUCCESS;
}