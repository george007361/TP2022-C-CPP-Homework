#include "task.h"

int run_task(const int argc, char *const argv[]) {
  char *filepath = NULL;

  // Read command line args
  if (read_arguments(&filepath, argc, argv) != SUCCESS) {
    return EXIT_FAILURE;
  }

  // Open file
  FILE *file;
  if (open_file(&file, filepath) != SUCCESS) {
    fprintf(stderr, "Can't open file %s\n", filepath);
    free(filepath);

    return EXIT_FAILURE;
  }

  // Do job
  delta_temperature_t max_delta = init_delta_temp();
  if (find_max_temperature_delta_in_file(&max_delta, file) == EXIT_FAILURE) {
    free(filepath);
    fclose(file);

    return EXIT_FAILURE;
  }
  printf("%i %lld\n", max_delta.delta, max_delta.index);

  // Clear resources
  fclose(file);
  free(filepath);

  return EXIT_SUCCESS;
}

void usage() {
  printf("Usage: \"--help\" for help; \"--file <filepath>\" arg "
         "required, for path to data file \n");
}

int read_arguments(char **filepath, const int argc, char *const argv[]) {
  if (argv == NULL || filepath == NULL) {
    fprintf(stderr, "filepath or argv NULL\n");

    return ERROR_NULL_PTR_PARAM;
  }

  if (argc < 2) {
    usage();

    return ERROR_WRONG_USAGE;
  }

  int option_symbol;

  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"file", required_argument, NULL, 'f'},
                             {"test", required_argument, NULL, 't'},
                             {NULL, 0, NULL, 0}};

  while ((option_symbol = getopt_long_only(argc, argv, "", options, NULL)) !=
         -1) {
    switch (option_symbol) {
    case 't': {
      break;
    }
    case 'f': {
      *filepath = realpath(optarg, NULL);
      if (*filepath == NULL) {
        fprintf(stderr, "Error: incorrect filepath: \"%s\" : %s\n", optarg,
                strerror(errno));
        return ERROR_WRONG_PATH;
      }

      break;
    }

    default:
    case 'h': {
      usage();

      return ERROR_WRONG_USAGE;
    }
    }
  }

  return SUCCESS;
}

int find_max_temperature_delta_in_file(delta_temperature_t *found_max_delta,
                                       FILE *file) {
  if (!file || !found_max_delta) {
    return EXIT_FAILURE;
  }

  delta_temperature_t max_delta_temp = init_delta_temp();
  part_t part = init_part(0, NULL, 0, 0, -1, &max_delta_temp);

  int flag = SUCCESS_NOT_ALL_DATA;

  while (flag == SUCCESS_NOT_ALL_DATA) {
    flag = read_array_from_file(&part.arr, &part.len, file);
    if (part.len < 1) {
      break;
    }
    if (flag != SUCCESS_ALL_DATA && flag != SUCCESS_NOT_ALL_DATA) {
      fprintf(stderr, "Error reading array from file\n");
      free_array(&part.arr, &part.len);

      return EXIT_FAILURE;
    }

    if (find_max_temperature_delta_in_array(&part) == EXIT_FAILURE) {
      free_array(&part.arr, &part.len);

      return EXIT_FAILURE;
    }
    part.prev_elem_index = part.offset + part.len - 1;

    part.prev_elem = part.arr[part.prev_elem_index];
    part.offset += part.len;
  }

  free_array(&part.arr, &part.len);

  *found_max_delta = max_delta_temp;
  return EXIT_SUCCESS;
}
