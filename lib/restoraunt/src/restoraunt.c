#include "restoraunt.h"

#include <stdio.h>
#include <stdlib.h>

int read_client(Client *client) {
  if (!(client->name = read_str()))
    return EXIT_FAILURE;
  int is_error = 0;
  client->receipt = read_int(&is_error);
  client->table = read_int(&is_error);
  if (is_error)
    return EXIT_FAILURE;

  return strlen(client->name) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int read_clients(Clients *clients) {
  char key;

  while ((key = read_char()) == CLIENT_SEPARATOR) {
    Client new_client;

    if (read_client(&new_client) == EXIT_FAILURE) {
      printf("Can't read client №%i\n", clients->count + 1);
      free_client(&new_client);
      return EXIT_FAILURE;
    }
    if (clients->capacity == clients->count) {
      clients->arr = (Client *)realloc(
          clients->arr,
          sizeof(Client) * (clients->capacity ? clients->capacity *= 2 : 1));
      if (!clients->arr)
        return EXIT_FAILURE;
    }
    clients->arr[clients->count++] = new_client;
  }

  printf("Read %i clients\n", clients->count);

  return EXIT_SUCCESS;
}

void free_client(Client *client) {
  if (client->name)
    free(client->name);
}

void free_clients(Clients clients) {
  if (clients.arr) {
    for (int i = 0; i < clients.count; i++) {
      free_client(&clients.arr[i]);
    }
    free(clients.arr);
  }

  clients.capacity = clients.count = 0;
}
