#include "restoraunt.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  // init
  Clients clients = {NULL, 0, 0};
  if (read_clients(&clients))
    printf("Some issues while reading clients..\n");

  // job
  for (int i = 0; i < clients.count; i++) {
    printf("---\n%s\n%i\n%i\n---\n", clients.arr[i].name,
           clients.arr[i].receipt, clients.arr[i].table);
  }

  // free
  free_clients(clients);

  return EXIT_SUCCESS;
}