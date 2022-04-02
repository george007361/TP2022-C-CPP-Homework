// Parallel algorythm
#include "temperature_analyzer.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

delta_temperature_t init_delta_temp() {
  delta_temperature_t dt = {0, -1, PTHREAD_MUTEX_INITIALIZER};

  return dt;
}

part_t init_part(long offset, int *arr, size_t len, int prev_elem,
                 long prev_elem_index,
                 delta_temperature_t *max_delta_temperature) {
  part_t part = {
      offset, arr, len, prev_elem, prev_elem_index, max_delta_temperature};

  return part;
}

int check_prev_elem(part_t *part) {
  if (!part) {
    fprintf(stderr, NULL_PTR_PARAM_ERR_MSG);
    return EXIT_FAILURE;
  }

  // Сравниваем последний элемент из прошлого фрагмента с начальным в текущем,
  // если он был
  if (part->prev_elem_index != -1) {
    if (!part->arr) {
      fprintf(stderr, NULL_PTR_PARAM_ERR_MSG);
      return EXIT_FAILURE;
    }

    if (part->arr[0] - part->prev_elem > part->max_delta_temperature->delta) {
      part->max_delta_temperature->delta = part->arr[0] - part->prev_elem;
      part->max_delta_temperature->index = part->prev_elem_index;
    }
  }

  return EXIT_SUCCESS;
}

void *find_max_temperature_delta_in_thread(void *arg) { // arg = part
  part_t *thread_part = (part_t *)arg;

  if (!thread_part) {
    fprintf(stderr, NULL_PTR_PARAM_ERR_MSG);
    return ((void *)THREAD_FAIL);
  }

  if (!thread_part->arr) {
    fprintf(stderr, NULL_PTR_PARAM_ERR_MSG);
    return ((void *)THREAD_FAIL);
  }

  delta_temperature_t local_max = init_delta_temp();

  for (size_t i = 0; i < thread_part->len - 1; i++) {
    if (thread_part->arr[i + 1] - thread_part->arr[i] > local_max.delta) {
      local_max.delta = thread_part->arr[i + 1] - thread_part->arr[i];
      local_max.index = thread_part->offset + i;
    }
  }

  // Переносим результат в общую для всех потоков структуру
  pthread_mutex_lock(&thread_part->max_delta_temperature->mutex);

  if (check_prev_elem(thread_part) == EXIT_FAILURE) {
    fprintf(stderr, CHECK_PREV_ERR_MSG);
    return ((void *)THREAD_FAIL);
  }

  if (local_max.delta > thread_part->max_delta_temperature->delta) {
    thread_part->max_delta_temperature->delta = local_max.delta;
    thread_part->max_delta_temperature->index = local_max.index;
  }

  pthread_mutex_unlock(&thread_part->max_delta_temperature->mutex);

  return ((void *)THREAD_SUCCESS);
}

int find_max_temperature_delta_in_array(part_t *part) {
  if (!part) {
    fprintf(stderr, NULL_PTR_PARAM_ERR_MSG);
    return EXIT_FAILURE;
  }

  int count_of_threads = sysconf(_SC_STREAM_MAX);
  if (count_of_threads < 1) {
    fprintf(stderr, "%s", strerror(errno));
    return EXIT_FAILURE;
  }

  while (part->len / count_of_threads < ELEMENTS_PER_THREAD &&
         count_of_threads > 1) {
    --count_of_threads;
  }

  size_t step = (part->len / count_of_threads) + 1;
  long thread_offset = 0;

  thread_part_t *thread_parts =
      (thread_part_t *)malloc(count_of_threads * sizeof(thread_part_t));

  if (!thread_parts) {
    fprintf(stderr, CANT_MALLOC_ERR_MSG);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < count_of_threads; i++) {
    size_t next_len =
        thread_offset + step < part->len ? step : part->len - thread_offset;

    long next_prev_elem_index = thread_offset > 0
                                    ? thread_offset + (long)next_len - 1
                                    : part->prev_elem_index;

    int next_prev_elem =
        thread_offset > 0 ? part->arr[next_prev_elem_index] : part->prev_elem;

    thread_parts[i].part = init_part(
        part->offset + thread_offset, part->arr + thread_offset, next_len,
        next_prev_elem, next_prev_elem_index, part->max_delta_temperature);

    int errflag = pthread_create(&thread_parts[i].thd, NULL,
                                 find_max_temperature_delta_in_thread,
                                 (void *)&thread_parts[i].part);

    if (errflag) {
      free(thread_parts);
      fprintf(stderr, PTHREAD_CREATE_ERR_MSG);
      return EXIT_FAILURE;
    }

    thread_offset += next_len;
  }

  void *thread_exit_code;
  for (int i = 0; i < count_of_threads; i++) {
    if (pthread_join(thread_parts[i].thd, &thread_exit_code)) {
      fprintf(stderr, PTHREAD_JOIN_ERR_MSG);
      free(thread_parts);
      return EXIT_FAILURE;
    }
    if ((int)thread_exit_code != THREAD_SUCCESS) {
      fprintf(stderr, PTHREAD_EXIT_FAILURE_ERR_MSG);
      free(thread_parts);
      return EXIT_FAILURE;
    }
  }

  free(thread_parts);
  return EXIT_SUCCESS;
}
