#ifndef LIB_TEMPERATURE_ANALYZER_PARALLEL_INCLUDE_TEMPERATURE_ANALYZER_H_
#define LIB_TEMPERATURE_ANALYZER_PARALLEL_INCLUDE_TEMPERATURE_ANALYZER_H_

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MB_PER_THREAD 50
#define BYTES_IN_MB (1024 * 1024)
#define ELEMENTS_PER_THREAD (MB_PER_THREAD * BYTES_IN_MB / sizeof(int))

#ifndef SHARED_ERR_MSG
#define SHARED_ERR_MSG

#define NULL_PTR_PARAM_ERR_MSG                                                 \
  "Some params given to func as address are null ptr \n"
#define CANT_MALLOC_ERR_MSG "Cant malloc memory\n"

#endif

#define CHECK_PREV_ERR_MSG "check_prev_elem() error occured\n"
#define PTHREAD_CREATE_ERR_MSG "Pthread create error occured\n"
#define PTHREAD_JOIN_ERR_MSG "Pthread join error occured\n"
#define PTHREAD_EXIT_FAILURE_ERR_MSG "Analysing part in thread error occured"

typedef struct {
  int delta;
  long index;
  pthread_mutex_t mutex;
} delta_temperature_t;

typedef struct {
  long offset;
  int *arr;
  size_t len;

  int prev_elem;
  long prev_elem_index;

  delta_temperature_t *max_delta_temperature;
} part_t;

typedef struct {
  pthread_t thd;
  part_t part;
} thread_part_t;

delta_temperature_t init_delta_temp();
part_t init_part(long offset, int *arr, size_t len, int prev_elem,
                 long prev_elem_index,
                 delta_temperature_t *max_delta_temperature);
int find_max_temperature_delta_in_array(part_t *part);

int find_max_temperature_delta_in_array(part_t *part);

#endif // LIB_TEMPERATURE_ANALYZER_PARALLEL_INCLUDE_TEMPERATURE_ANALYZER_H_
