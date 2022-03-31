#include <errno.h>
#include <fstream>
#include <getopt.h>
#include <iostream>

using namespace std;

#define COUNT_OF_NUBMERS ((sizeMB * 1024 * 1024) / sizeof(int))
#define DIAPOSONE 5000
#define OFSSET (DIAPOSONE / 2)

void usage() {
  cout << "Usage: \"--help\" for help; \"--path <path>\" data file location, "
          "required; \"--size <int>\" file size MB, required\n";
}

int main(int argc, char *argv[]) {
  string fname;
  int sizeMB = 0;

  if (argc < 3) {
    usage();

    return EXIT_FAILURE;
  }

  int option_symbol, count = 0, size = 0;

  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"path", required_argument, NULL, 'p'},
                             {"size", required_argument, NULL, 's'},
                             {NULL, 0, NULL, 0}};

  while ((option_symbol = getopt_long_only(argc, argv, "", options, NULL)) !=
         -1) {
    switch (option_symbol) {

    default:
    case 'h': {
      usage();

      return EXIT_FAILURE;
    }
    case 'p': {
      fname = string(optarg);
      break;
    }
    case 's': {
      sizeMB = stoi(optarg);
      break;
    }
    }
  }

  ofstream dataFile;

  dataFile.open(fname);
  if (!dataFile.is_open()) {

    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < COUNT_OF_NUBMERS; i++) {
    dataFile << rand() % DIAPOSONE - OFSSET << " ";
  }

  return EXIT_SUCCESS;
}