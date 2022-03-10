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

Client *read_clients(int *count);
void free_clients(Client *clients, int *count);

#endif // RESTORAUNT_H_
