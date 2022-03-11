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
          sizeof(Client) * (clients->capacity = clients->capacity ? clients->capacity *= 2 : 1));
      if (!clients->arr)
        return EXIT_FAILURE;
    }
    clients->arr[clients->count++] = new_client;
    print_clietns(*clients);
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

void swap_clients(Clients clients, int a, int b) {
  Client tmp = clients.arr[a];
  clients.arr[a] = clients.arr[b];
  clients.arr[b] = tmp;
}

// Возвращает индекс, на который встанет пивот после разделения.
int partition(Clients clients, int a,
              int n) { // a начальный индекс, n - количество элементов отн. a
  if (n <= 1) {
    return 0;
  }
  const int pivot = clients.arr[a + n - 1].table;
  int i = 0, j = n - 2;
  while (i <= j) {
    // Не проверяем, что i < n - 1, т.к. a[n - 1] == pivot.
    for (; clients.arr[a + i].table < pivot; ++i) {
    }
    for (; j >= 0 && !(clients.arr[a + j].table < pivot); --j) {
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

void quick_sort(Clients clients, int a, int n) {
  int part = partition(clients, a, n);
  if (part > 0)
    quick_sort(clients, a, part);
  if (part + 1 < n)
    quick_sort(clients, a + part + 1, n - (part + 1));
}

void quick_sort_by_table_clients(Clients clients) {
  quick_sort(clients, 0, clients.count);
}

void print_clietns(Clients clients) {
  for (int i = 0; i < clients.count; i++) {
    printf("---\n%s\n%i\n%i\n---\n", clients.arr[i].name,
           clients.arr[i].receipt, clients.arr[i].table);
  }
}