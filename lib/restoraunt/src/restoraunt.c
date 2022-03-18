#include "restoraunt.h"

#include <string.h>

int restoraunt_work() {
  // init
  clients clients = init_clients();
  if (read_clients(&clients, stdin)) {
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

int read_client(client *client, FILE *stream) {
  if (!client || !stream) {
    return EXIT_FAILURE;
  }

  if (!(client->name = read_str(stream))) {
    return EXIT_FAILURE;
  }

  int is_error = 0;

  client->receipt = read_int(&is_error, stream);
  client->table = read_int(&is_error, stream);

  if (is_error) {
    return EXIT_FAILURE;
  }

  return strlen(client->name) ? EXIT_SUCCESS : EXIT_FAILURE;
}

clients init_clients() {
  clients cls = {NULL, 0, 0};

  return cls;
}

int read_clients(clients *clients, FILE *stream) {
  if (!clients || !stream) {
    return EXIT_FAILURE;
  }

  printf("Format:\n-----\n#<Name>\n<Receipt>\n<Table>\n-----\n<Any symbol to "
         "exit>\n\n");

  while (read_char(stream) == CLIENT_SEPARATOR) {
    client new_client;

    if (read_client(&new_client, stream) == EXIT_FAILURE) {
      fprintf(stderr, "Can't read client №%li\n", clients->count + 1);

      free_client(&new_client);
      free_clients(clients);

      return EXIT_FAILURE;
    }

    if (clients->capacity == clients->count) {
      if (clients->capacity) {
        clients->capacity *= 2;
      } else {
        clients->capacity = 1;
      }

      client *pnew_arr =
          (client *)realloc(clients->arr, sizeof(client) * clients->capacity);
      if (!pnew_arr) {
        fprintf(stderr, "Realloc error: read_clients()\n");

        free_clients(clients);

        return EXIT_FAILURE;
      }

      clients->arr = pnew_arr;
    }

    clients->arr[clients->count++] = new_client;
  }

  return EXIT_SUCCESS;
}

void free_client(client *client) {
  if (client) {
    if (client->name) {
      free(client->name);
      client->name = NULL;
    }

    client->receipt = client->table = -1;
  }
}

void free_clients(clients *clients) {
  if (clients) {
    if (clients->arr) {
      for (size_t i = 0; i < clients->count; i++) {
        free_client(&clients->arr[i]);
      }

      free(clients->arr);
      clients->arr = NULL;
    }

    clients->capacity = clients->count = 0;
  }
}

void swap_clients(clients *clients, const int a, const int b) {
  if (!clients) {
    fprintf(stderr, "clients ptr is empty\n");
    return;
  }

  client tmp = clients->arr[a];
  clients->arr[a] = clients->arr[b];
  clients->arr[b] = tmp;
}

int partition(clients *clients, const int a, const int n) {
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

void quick_sort(clients *clients, const int a, const int n) {
  int part = partition(clients, a, n);
  if (part > 0) {
    quick_sort(clients, a, part);
  }
  if (part + 1 < n) {
    quick_sort(clients, a + part + 1, n - (part + 1));
  }
}

void quick_sort_by_table_clients(clients *clients) {
  if (!clients) {
    return;
  }

  quick_sort(clients, 0, clients->count);
}

void print_clietns(const clients clients) {
  if (clients.arr == NULL) {
    fprintf(stderr, "Print_client(): error NULL array\n");
    return;
  }

  for (size_t i = 0; i < clients.count; i++) {
    printf("Name: %s\n Receipt: %i\n Table: %i\n\n", clients.arr[i].name,
           clients.arr[i].receipt, clients.arr[i].table);
  }
}
