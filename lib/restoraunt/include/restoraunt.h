#ifndef LIB_RESTORAUNT_INCLUDE_RESTORAUNT_H_
#define LIB_RESTORAUNT_INCLUDE_RESTORAUNT_H_

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define CLIENT_SEPARATOR '#'
#define BUFF_SIZE 5

typedef struct client {
  char *name;
  int table;
  int receipt;
} client;

typedef struct clients {
  client *arr;
  size_t capacity;
  size_t count;
} clients;

int restoraunt_work();
clients init_clients();
int read_clients(clients *clients, FILE *stream);
void free_client(client *client);
void free_clients(clients *clients);
void quick_sort_by_table_clients(clients *clients);
void print_clietns(const clients clients);

#endif // LIB_RESTORAUNT_INCLUDE_RESTORAUNT_H_
