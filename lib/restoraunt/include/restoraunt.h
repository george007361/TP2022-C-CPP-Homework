#ifndef RESTORAUNT_H_
#define RESTORAUNT_H_

#include "functions.h"

#define CLIENT_SEPARATOR '#'
#define BUFF_SIZE 5

typedef struct Client {
  char *name;
  int table;
  int receipt
} Client;

typedef struct Clients {
  Client *arr;
  int capacity;
  int count;
} Clients;

typedef struct Table {
  int id;
  int *clients_indexes;
  int count;
  int capacity;
} Table;

typedef struct Tables {
  Table *arr;
  int count;
  int capacity;
} Tables;

int read_clients(Clients *clients);
void free_client(Client *client);
void free_clients(Clients clients);
int group_clients(Tables *tables);

#endif // RESTORAUNT_H_
