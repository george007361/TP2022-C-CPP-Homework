#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "utils.h"

#define RUN_TASK_ERR_MSG "While running task, error occured\n"

int main(int argc, char *argv[]) {
  if (run_task(argc, argv) == EXIT_FAILURE) {
    fprintf(stderr, "main() : %s\n", RUN_TASK_ERR_MSG);

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
