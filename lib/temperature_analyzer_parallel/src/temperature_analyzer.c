#include "temperature_analyzer.h"

delta_temperature_t init_delta_temp() {
  // int delta;
  // size_t index;
  // pthread_t mutex;

  delta_temperature_t dt = {0, -1, {0}};

  return dt;
}

part_t init_part(size_t offset, int *arr, size_t len, int prev_elem,
                 long long prev_elem_index,
                 delta_temperature_t *max_delta_temperature) {
  part_t part = {
      offset, arr, len, prev_elem, prev_elem_index, max_delta_temperature};

  return part;
}

void check_prev_elem(part_t *part) {
  if (!part) {
    return;
  }
  if (part->prev_elem_index != -1) {
    if (!part->arr) {
      return;
    }
    if (part->arr[0] - part->prev_elem > part->max_delta_temperature->delta) {
      part->max_delta_temperature->delta = part->arr[0] - part->prev_elem;
      part->max_delta_temperature->index = part->prev_elem_index;
    }
  }
}

void *find_max_temperature_delta_in_thread(void *arg) { // arg = part
  part_t *thread_part = (part_t *)arg;

  check_prev_elem(thread_part);
  if (!thread_part) {
    //
  }

  delta_temperature_t local_max = init_delta_temp();

  for (size_t i = 0; i < thread_part->len - 1; i++) {
    if (thread_part->arr[i + 1] - thread_part->arr[i] > local_max.delta) {
      local_max.delta = thread_part->arr[i + 1] - thread_part->arr[i];
      local_max.index = thread_part->offset + i;
    }
  }

  pthread_mutex_lock(&thread_part->max_delta_temperature->mutex);
  check_prev_elem(thread_part);
  if (local_max.delta > thread_part->max_delta_temperature->delta) {
    thread_part->max_delta_temperature->delta = local_max.delta;
    thread_part->max_delta_temperature->index = local_max.index;
  }
  pthread_mutex_unlock(&thread_part->max_delta_temperature->mutex);

  //  return EXIT_SUCCESS;
  return NULL;
}

int find_max_temperature_delta_in_array(part_t *part) {
  if (!part) {
    return EXIT_FAILURE;
  }

  size_t count_of_threads = sysconf(_SC_STREAM_MAX);
  while (part->len / count_of_threads < ELEMENTS_PER_THREAD &&
         count_of_threads > 1) {
    --count_of_threads;
  }

  size_t step = (part->len / count_of_threads) + 1;
  size_t thread_offset = 0;

  thread_part_t *thread_parts =
      (thread_part_t *)malloc(sizeof(thread_part_t) * count_of_threads);
  if (!thread_parts) {
    return EXIT_FAILURE;
  }

  pthread_mutex_init(&part->max_delta_temperature->mutex, NULL);

  for (size_t i = 0; i < count_of_threads; i++) {
    size_t next_len =
        thread_offset + step < part->len ? step : part->len - thread_offset;

    long long next_prev_elem_index =
        (long long)thread_offset - 1 >= 0
            ? (long long)thread_offset + next_len - 1
            : part->prev_elem_index;

    int next_prev_elem = (long long)thread_offset - 1 >= 0
                             ? part->arr[next_prev_elem_index]
                             : part->prev_elem;

    thread_parts[i].part = init_part(
        part->offset + thread_offset, part->arr + thread_offset, next_len,
        next_prev_elem, next_prev_elem_index, part->max_delta_temperature);

    int errflag = pthread_create(&thread_parts[i].thd, NULL,
                                 find_max_temperature_delta_in_thread,
                                 (void *)&thread_parts[i].part);

    if (errflag != 0) {
      //
    }
    thread_offset += next_len;
  }

  for (size_t i = 0; i < count_of_threads; i++) {
    pthread_join(thread_parts[i].thd, NULL);
    if (thread_parts[i].exit_code == !EXIT_FAILURE) {
      //
    }
  }

  pthread_mutex_destroy(&part->max_delta_temperature->mutex);

  return EXIT_SUCCESS;
}

// delta_temperature_t init_delta_temperature() {
//   delta_temperature_t td = {0, -1};

//   return td;
// }

// part_t init_part(delta_temperature_t *delta_temperature) {
//   part_t part = {NULL, 0, 0, -1, delta_temperature, 0};

//   return part;
// }

// thread_part_t init_thread_part();

// void check_previous_elem(part_t *part) {
//   if (!part) {
//     return;
//   }
//   if (part->last_elem_index != -1) {
//     if (!part->max_delta_temperature || !part->ptr_arr_part) {
//       return;
//     }
//     if (part->ptr_arr_part[0] - part->last_elem >
//         part->max_delta_temperature->delta) {
//       part->max_delta_temperature->delta =
//           part->ptr_arr_part[0] - part->last_elem;
//       part->max_delta_temperature->index = part->last_elem_index;
//     }
//   }
// }

// int find_max_temperature_delta_in_array(part_t *part) {
//   if (!part) {
//     return EXIT_FAILURE;
//   }
//   check_previous_elem(part);

//   size_t count_of_threads = sysconf(_SC_STREAM_MAX);
//   while (size / count_of_threads < ELEMENTS_PER_THREAD &&
//          count_of_threads > 1) {
//     --count_of_threads;
//   }

//   size_t thread_offset = 0;
//   thread_part_t *thread_parts =
//       (thread_part_t *)malloc(sizeof(thread_part_t) * count_of_threads);
//   if (!thread_parts) {
//     return EXIT_FAILURE;
//   }

//   for (size_t i = 0; i < count_of_threads; i++) {
//     thread_parts[i] = init_thread_part();
//   }

//   for (size_t i = 0; i < count_of_threads; i++) {
//   }

//   return EXIT_SUCCESS;
// }

// void *find_max_temperature_delta_in_part(void *args) {
//   // args
//   // max_delta_t  *max_delta,
//   // const int *const arr,
//   // const size_t size

//   return EXIT_SUCCESS;
// }

// thread_args_t init_thread_args(const max_delta_t *max_delta,
//                                const int *const arr, const size_t size) {
//   thread_args_t args = {max_delta, arr, size, EXIT_FAILURE};

//   return args;
// }

// int find_max_temperature_delta_in_array(max_delta_t *max_delta,
//                                         const int *const arr,
//                                         const size_t size) {
//   if (!max_delta || !arr) {
//     return EXIT_FAILURE;
//   }

//   // Check prev last elem
//   if (max_delta->last_index) {
//     if (arr[0] - max_delta->last_number > max_delta->delta) {
//       max_delta->delta = arr[0] - max_delta->last_number;
//       max_delta->index = max_delta->last_index;
//     }
//   }

//   // Check elems in this part

//   // Calculate needed count of threads
//   size_t count_of_threads = sysconf(_SC_STREAM_MAX);
//   while (size / count_of_threads < ELEMENTS_PER_THREAD &&
//          count_of_threads > 1) {
//     --count_of_threads;
//   }

//   // Calc size of each part
//   size_t step = size / count_of_threads;

//   // Threads ids array
//   pthread_t *threads =
//       (pthread_t *)malloc(sizeof(pthread_t) * count_of_threads);
//   if (!threads) {
//     return EXIT_FAILURE;
//   }

//   // Threads args to each thread array
//   thread_args_t *thread_args =
//       (thread_args_t *)malloc(sizeof(thread_args_t) * count_of_threads);
//   if (!thread_args) {
//     return EXIT_FAILURE;
//   }

//   int err_flag = 0;
//   for (size_t i = 0; !err_flag && i < count_of_threads; i++) {
//     // Prepate args for thread
//     thread_args[i] = init_thread_args(0, 0, 0);
//     // Create new thread
//     err_flag =
//         pthread_create(&threads[i], NULL, find_max_temperature_delta_in_part,
//                        (void *)&thread_args[i]);
//   }

//   for (size_t i = 0; i < count_of_threads; i++) {
//     pthread_join(threads[i], NULL);
//   }
//   free(threads);

//   // Remember last elem and change offset
//   max_delta->last_index = max_delta->offset + size - 1;
//   max_delta->last_number = arr[size - 1];
//   max_delta->offset += size;

//   return EXIT_SUCCESS;
// }
