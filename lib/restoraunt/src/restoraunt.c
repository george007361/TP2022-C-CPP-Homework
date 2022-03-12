#include "restoraunt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_client(Client *client) {
  if (!client)
    return EXIT_FAILURE;

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
  if (!clients)
    return EXIT_FAILURE;

  printf("Format:\n-----\n#<Name>\n<Receipt>\n<Table>\n-----\n<Any symbol to "
         "exit>\n\n");

  while (read_char() == CLIENT_SEPARATOR) {
    Client new_client;

    if (read_client(&new_client) == EXIT_FAILURE) {
      fprintf(stderr, "Can't read client №%li\n", clients->count + 1);

      free_client(&new_client);

      return EXIT_FAILURE;
    }

    if (clients->capacity == clients->count) {
      Client *pnew_arr = (Client *)realloc(
          clients->arr,
          sizeof(Client) * (clients->capacity = clients->capacity
                                                    ? clients->capacity *= 2
                                                    : 1));
      if (!pnew_arr) {
        fprintf(stderr, "Realloc error: read_clients()\n");

        free_clients(clients);

        return EXIT_FAILURE;
      }
      clients->arr = pnew_arr;
    }
    clients->arr[clients->count++] = new_client;
    // print_clietns(*clients);
  }

  // printf("Read %i clients\n", clients->count);

  return EXIT_SUCCESS;
}

void free_client(Client *client) {
  if (client) {
    if (client->name)
      free(client->name);

    client->receipt = client->table = -1;
  }
}

void free_clients(Clients *clients) {
  if (clients) {
    if (clients->arr) {
      for (size_t i = 0; i < clients->count; i++) {
        free_client(&clients->arr[i]);
      }

      free(clients->arr);
    }

    clients->capacity = clients->count = 0;
  }
}

void swap_clients(Clients *clients, int a, int b) {
  Client tmp = clients->arr[a];
  clients->arr[a] = clients->arr[b];
  clients->arr[b] = tmp;
}

int partition(Clients *clients, int a, int n) {
  if (n <= 1) {
    return 0;
  }

  const int pivot = clients->arr[a + n - 1].table;
  int i = 0, j = n - 2;
  while (i <= j) {
    for (; clients->arr[a + i].table < pivot; ++i) {
    }
    for (; j >= 0 && !(clients->arr[a + j].table < pivot); --j) {
    }
    if (i < j) {
      swap_clients(clients, a + i, a + j);
      i++;
      j++;
    }
  }
  swap_clients(clients, a + i, a + n - 1);
  return i;
}

void quick_sort(Clients *clients, int a, int n) {
  int part = partition(clients, a, n);
  if (part > 0)
    quick_sort(clients, a, part);
  if (part + 1 < n)
    quick_sort(clients, a + part + 1, n - (part + 1));
}

void quick_sort_by_table_clients(Clients *clients) {
  if (!clients)
    return;

  quick_sort(clients, 0, clients->count);
}

void print_clietns(const Clients clients) {
  for (size_t i = 0; i < clients.count; i++) {
    printf("Name: %s\n Receipt: %i\n Table: %i\n\n", clients.arr[i].name,
           clients.arr[i].receipt, clients.arr[i].table);
  }
}
