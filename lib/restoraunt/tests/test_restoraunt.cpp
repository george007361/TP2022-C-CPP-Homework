#include "gtest/gtest.h"

#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "restoraunt.h"
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(TestFreeClientFunc, NoErrors) {
  Client cl = {(char *)malloc(sizeof(char)), 1, 2};

  free_client(&cl);
  
  EXPECT_FALSE(cl.name);
  EXPECT_EQ(-1, cl.receipt);
  EXPECT_EQ(-1, cl.table);
}

TEST(TestFreeClientFunc, ErrorNullPtr) {
  Client cl = {NULL, 1, 2};

  free_client(&cl);
  
  EXPECT_FALSE(cl.name);
  EXPECT_EQ(-1, cl.receipt);
  EXPECT_EQ(-1, cl.table);
}

TEST(TestFreeClientFunc, ErrorNullClientPtr) { free_client(NULL); }

TEST(TestInitClientsFunc, NoErrors) {
  Clients cls = init_clients();
  
  EXPECT_FALSE(cls.arr);
  EXPECT_EQ(0, cls.capacity);
  EXPECT_EQ(0, cls.count);
}

TEST(TestReadClientsFunc, NoErrors) {
  char *buf = "#Name\n1\n2\n#Name2\n3\n4\n/";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  Clients clients = init_clients();

  EXPECT_EQ(EXIT_SUCCESS, read_clients(&clients, f));
  ASSERT_TRUE(clients.arr);
  EXPECT_EQ(2, clients.count);

  EXPECT_TRUE(!strcmp("Name", clients.arr[0].name));
  EXPECT_EQ(1, clients.arr[0].receipt);
  EXPECT_EQ(2, clients.arr[0].table);

  EXPECT_TRUE(!strcmp("Name2", clients.arr[1].name));
  EXPECT_EQ(3, clients.arr[1].receipt);
  EXPECT_EQ(4, clients.arr[1].table);

  free_clients(&clients);
  fclose(f);
}

TEST(TestReadClientsFunc, ErrorWrongName) {
  char buf[] = "#\n1\n2\n/";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  Clients clients = init_clients();

  EXPECT_EQ(EXIT_FAILURE, read_clients(&clients, f));
  ASSERT_FALSE(clients.arr);
  EXPECT_EQ(0, clients.count);

  free_clients(&clients);
  fclose(f);
}

TEST(TestReadClientsFunc, ErrorWrongReceipt) {
  char buf[] = "#Name\n\n\n/";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  Clients clients = init_clients();

  EXPECT_EQ(EXIT_FAILURE, read_clients(&clients, f));
  ASSERT_FALSE(clients.arr);
  EXPECT_EQ(0, clients.count);

  free_clients(&clients);
  fclose(f);
}

TEST(TestReadClientsFunc, ErrorWrongTable) {
  char buf[] = "#Name\n1500\nLOL\n/";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  Clients clients = init_clients();

  EXPECT_EQ(EXIT_FAILURE, read_clients(&clients, f));
  ASSERT_FALSE(clients.arr);
  EXPECT_EQ(0, clients.count);

  free_clients(&clients);
  fclose(f);
}

TEST(TestSortingFunc, NoError) {
  char buf[] = "#Third\n100\n3\n#First\n100\n1\n#Second\n100\n2\n/";
  FILE *f = fmemopen(buf, strlen(buf) + 1, "r");

  Clients clients = init_clients();

  EXPECT_EQ(EXIT_SUCCESS, read_clients(&clients, f));
  quick_sort_by_table_clients(&clients);

  EXPECT_EQ(1, clients.arr[0].table);
  EXPECT_EQ(2, clients.arr[1].table);
  EXPECT_EQ(3, clients.arr[2].table);

  free_clients(&clients);
  fclose(f);
}

TEST(TestSortingFunc, ErrorNullPtr) { quick_sort_by_table_clients(NULL); }

TEST(TestPrintClientsFunc, ErrorNullPtr) { print_clietns(init_clients()); }