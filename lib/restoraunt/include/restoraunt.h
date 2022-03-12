#ifndef LIB_RESTORAUNT_INCLUDE_RESTORAUNT_H_
#define LIB_RESTORAUNT_INCLUDE_RESTORAUNT_H_

#include "functions.h"

#define CLIENT_SEPARATOR '#'
#define BUFF_SIZE 5

typedef struct Client {
  char *name;
  int table;
  int receipt;
} Client;

typedef struct Clients {
  Client *arr;
  size_t capacity;
  size_t count;
} Clients;

int read_clients(Clients *clients);
void free_client(Client *client);
void free_clients(Clients *clients);
void quick_sort_by_table_clients(Clients *clients);
void print_clietns(const Clients clients);

#endif // LIB_RESTORAUNT_INCLUDE_RESTORAUNT_H_
