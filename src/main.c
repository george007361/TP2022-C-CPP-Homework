#include <stdio.h>
#include <stdlib.h>

#include "restoraunt.h"

int main() {
  // init
  Clients clients = {NULL, 0, 0};
  if (read_clients(&clients)) {
    printf("Some issues while reading clients..\n");
    return EXIT_FAILURE;
  }

  // job
  quick_sort_by_table_clients(&clients);
  print_clietns(clients);

  // free
  free_clients(&clients);

  return EXIT_SUCCESS;
}
