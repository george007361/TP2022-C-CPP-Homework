#include "utils.h"

void usage() {
  printf("Usage: \"--help\" for help; \"--file <filepath>\" arg "
         "required, for path to data file \n");
}

int read_arguments(char **filepath, const int argc, char *const argv[]) {
  if (argc == 0 || argv == NULL) {
    fprintf(stderr, "argc or argv NULL\n");
    return EXIT_FAILURE;
  }
  if (filepath == NULL) {
    fprintf(stderr, "ptr to filepath char* NULL\n");
    return EXIT_FAILURE;
  }
  if (argc == 1) {
    usage();

    return EXIT_FAILURE;
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
        return EXIT_FAILURE;
      }

      break;
    }

    default:
    case 'h': {
      usage();

      return EXIT_FAILURE;
    }
    }
  }

  return EXIT_SUCCESS;
}

int *init_array(size_t *size) {
  if (!size) {
    return NULL;
  }

  int *arr = NULL;
  *size = 0;
  return arr;
}

int free_array(int **arr, size_t *size) {
  if (!arr || !size) {
    return EXIT_FAILURE;
  }
  if (*arr) {
    free(*arr);
    *arr = NULL;
  }
  *size = 0;

  return EXIT_SUCCESS;
}

int open_file(FILE **file, const char *filepath) {
  if (file == NULL) {
    fprintf(stderr, "ptr to FILE* is null\n");
    return EXIT_FAILURE;
  }
  if (filepath == NULL) {
    fprintf(stderr, "filepath is NULL\n");
  }

  *file = fopen(filepath, "r");
  if (!*file) {
    fprintf(stderr, "Can't open file %s : %s\n", filepath, strerror(errno));

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int read_array_from_file(int **arr, size_t *size, FILE *file) {
  if (!arr || !size) {

    return EXIT_FAILURE;
  }
  if (!file) {

    return EXIT_FAILURE;
  }
  if (ferror(file)) {

    return EXIT_FAILURE;
  }

  free_array(arr, size);

  const size_t max_size = BUFF_SIZE_BYTES / sizeof(int);
  *arr = (int *)malloc(BUFF_SIZE_BYTES);
  if (!*arr) {
    return EXIT_FAILURE;
  }

  for (*size = 0; *size < max_size; *size += 1) {
    if (fscanf(file, "%i", &(*arr)[*size]) != 1) {
      if (feof(file)) {
        break;
      } else {
        free_array(arr, size);

        return EXIT_FAILURE;
      }
    }
  }

  if (*size < max_size) {
    int *new_arr = realloc(*arr, *size * sizeof(int));
    if (!new_arr) {

    } else {
      *arr = new_arr;
    }
  }

  return EXIT_SUCCESS;
}