#include <array>
#include <errno.h>
#include <getopt.h>
#include <iostream>
#include <time.h>

#define MILLISEC_IN_SEC 1000
#define MILLISEC_IN_NANOSEC 1 / 1000000

using namespace std;

void usage() {
  cout << "Usage: \"--help\" for help; \"--count <int>\" count of test, "
          "required; \"--size\" file size for each test, required\n";
}

string execCommand(const string cmd, int &out_exitStatus) {
  out_exitStatus = 0;
  auto pPipe = ::popen(cmd.c_str(), "r");
  if (pPipe == nullptr) {
    throw runtime_error("Cannot open pipe");
  }

  array<char, 256> buffer;

  std::string result;

  while (!feof(pPipe)) {
    auto bytes = fread(buffer.data(), 1, buffer.size(), pPipe);
    result.append(buffer.data(), bytes);
  }

  auto rc = ::pclose(pPipe);

  if (WIFEXITED(rc)) {
    out_exitStatus = WEXITSTATUS(rc);
  }

  return result;
}

int runTest(string pathToExe, double &timePassed) {
  int exitCode = 0;
  struct timespec startTime, endTime;
  clock_gettime(CLOCK_REALTIME, &startTime);
  cout << "Found max: " << execCommand(pathToExe, exitCode);// << endl;
  clock_gettime(CLOCK_REALTIME, &endTime);
  if (exitCode == EXIT_FAILURE) {

    return EXIT_FAILURE;
  }
  timePassed = (MILLISEC_IN_SEC * (endTime.tv_sec - startTime.tv_sec) +
                (endTime.tv_nsec - startTime.tv_nsec) * MILLISEC_IN_NANOSEC);

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    usage();

    return EXIT_FAILURE;
  }

  int option_symbol, count = 0, size = 0;

  struct option options[] = {{"help", no_argument, NULL, 'h'},
                             {"count", required_argument, NULL, 'c'},
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
    case 'c': {
      count = stoi(optarg);
      break;
    }
    case 's': {
      size = stoi(optarg);
      break;
    }
    }
  }

  int exitCode = 0;

  // build
  cout << execCommand("sh ./scripts/build.sh", exitCode);
  if (exitCode == EXIT_FAILURE) {

    return EXIT_FAILURE;
  }

  double medSerial = 0, medParallel = 0;

  for (int i = 0; i < count; i++) {
    // generate
    execCommand(string("./generator/generator --path ./data/data.txt --size " +
                       to_string(size)),
                exitCode);
    if (exitCode == EXIT_FAILURE) {

      return EXIT_FAILURE;
    }

    double time;

    // run serial
    if (runTest("./build/serial/main --file ./data/data.txt", time) ==
        EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
    cout << "  Serial: Test #" << i + 1 << ". Time passed:" << time
         << " millisec (10^-3 sec)" << endl;
    medSerial += time;

    if (runTest("./build/parallel/main --file ./data/data.txt", time) ==
        EXIT_FAILURE) {
      return EXIT_FAILURE;
    }

    // run parallel
    cout << "  Parallel: Test #" << i + 1 << ". Time passed:" << time
         << " millisec (10^-3 sec)" << endl << endl;
    medParallel += time;
  }

  // Crear dirs
  cout << execCommand("sh ./scripts/clear.sh", exitCode);
  if (exitCode == EXIT_FAILURE) {

    return EXIT_FAILURE;
  }

  cout << "->Parallel median time: " << medParallel / count << " ms" << endl;
  cout << "->Serial median time: " << medSerial / count << " ms" << endl;

  cout << "Done!" << endl;
  return EXIT_SUCCESS;
}
