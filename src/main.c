#include <stdio.h>
#include <stdlib.h>

#include "restoraunt.h"

int main() {
  if (restoraunt_work() == EXIT_FAILURE) {
    printf("Error of working restoraunt\n");
  }

  return EXIT_SUCCESS;
}
