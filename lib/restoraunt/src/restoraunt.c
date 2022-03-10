#include "restoraunt.h"

#include <stdio.h>
#include <stdlib.h>

int read_client(Client *client) {
  /* int a = (client->name = read_str());
  int b = scanf("%i", &client->receipt);
  int c = scanf("%i", &client->table); */
  /* if ((client->name = read_str()) == NULL || !scanf("%i", &client->receipt)
|| !scanf("%i", &client->table)) return EXIT_FAILURE;
} */
  client->name = read_str();
  client->receipt = read_int();
  client->table = read_int();

  return 1;
}

Client *read_clients(int *count) {
  *count = 0;
  int size = BUFF_SIZE;

  Client *clients = (Client *)malloc(size * sizeof(Client));
  if (!clients)
    return EXIT_FAILURE;

  char key;

  while ((key = read_char()) == CLIENT_SEPARATOR) {
    Client new_client;

    if (!read_client(&new_client)) {
      printf("Cant read %i client.\n", *count);
      return EXIT_FAILURE;
    }
    clients[(*count)++] = new_client;
  }

  printf("Read %i clients\n", *count);

  return clients;
}

void free_clients(Client *clients, int *count) {
  if (clients != NULL) {
    for (int i = 0; i < *count; i++) {
      if (clients[i].name != NULL)
        free(clients[i].name);
    }
    free(clients);
  }

  *count = 0;
}