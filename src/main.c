#include <stdlib.h>
#include <string.h>

#include "temperature_analyzer.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  char *filepath = NULL;

  if (read_arguments(&filepath, argc, argv) == EXIT_FAILURE) {

    return EXIT_FAILURE;
  }

  FILE *file;
  if (open_file(&file, filepath) == EXIT_FAILURE) {
    fprintf(stderr, "Can't open file %s\n", filepath);
    free(filepath);

    return EXIT_FAILURE;
  }

  size_t size = 0;
  int *arr = init_array(&size);
  if (read_array_from_file(&arr, &size, file) == EXIT_FAILURE) {

    fprintf(stderr, "Error reading array from file\n");

    return EXIT_FAILURE;
  }

  max_delta_t max_delta = {0, 0};
  if(find_max_temperature_delta(&max_delta, arr, size) == EXIT_FAILURE)
  {
    //
  }
  printf("%lu %lu\n", max_delta.delta, max_delta.index);

  fclose(file);
  free(filepath);
  free_array(&arr, &size);

  return EXIT_SUCCESS;
}
