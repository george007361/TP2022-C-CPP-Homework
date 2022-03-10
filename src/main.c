#include "restoraunt.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  // init
  int count = 0;
  Client *clients = read_clients(&count);

  // job

  // free
  free_clients(clients, &count);

  return EXIT_SUCCESS;
}