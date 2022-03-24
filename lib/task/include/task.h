#ifndef LIB_TASK_INCLUDE_TASK_H_
#define LIB_TASK_INCLUDE_TASK_H_

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "temperature_analyzer.h"
#include "utils.h"

int run_task(const int argc, char *const argv[]);
int read_arguments(char **filepath, const int argc, char *const argv[]);
void usage();
int find_max_temperature_delta_in_file(delta_temperature_t *found_max_delta,
                                       FILE *file);

#endif // LIB_TASK_INCLUDE_TASK_H_
