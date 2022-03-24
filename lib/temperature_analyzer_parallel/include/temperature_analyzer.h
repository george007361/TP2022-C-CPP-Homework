#ifndef LIB_TEMPERATURE_ANALYZER_PARALLEL_INCLUDE_TEMPERATURE_ANALYZER_H_
#define LIB_TEMPERATURE_ANALYZER_PARALLEL_INCLUDE_TEMPERATURE_ANALYZER_H_

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MB_PER_THREAD 20
#define BYTES_IN_MB (1024 * 1024)
#define ELEMENTS_PER_THREAD 4 // (MB_PER_THREAD * BYTES_IN_MB / sizeof(int))

typedef struct {
  int delta;
  long long index;
  pthread_mutex_t mutex;
} delta_temperature_t;

typedef struct {
  size_t offset;
  int *arr;
  size_t len;

  int prev_elem;
  long long prev_elem_index;

  delta_temperature_t *max_delta_temperature;
} part_t;

typedef struct {
  pthread_t thd;
  part_t part;
  int exit_code;
} thread_part_t;

delta_temperature_t init_delta_temp();
part_t init_part(size_t offset, int *arr, size_t len, int prev_elem,
                 long long prev_elem_index,
                 delta_temperature_t *max_delta_temperature);
int find_max_temperature_delta_in_array(part_t *part);

int find_max_temperature_delta_in_array(part_t *part);

#endif // LIB_TEMPERATURE_ANALYZER_PARALLEL_INCLUDE_TEMPERATURE_ANALYZER_H_
