#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
      if (filepath == NULL) {
        fprintf(stderr, "Error: incorrect filepath: \"%s\" : %s\n", optarg, strerror(errno));
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

int main(int argc, char *argv[]) {
  char *filepath = NULL;

  if (read_arguments(&filepath, argc, argv) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  FILE *file;
  if (open_file(&file, filepath) == EXIT_FAILURE) {
    fprintf(stderr, "Can't open file %s : \n", filepath, strerror(errno));
    free(filepath);
   
    return EXIT_FAILURE;
  }
  
  

  fclose(file);
  free(filepath);

  return EXIT_SUCCESS;
}