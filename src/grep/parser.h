#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>
#include <regex.h>

#include "dynamic_memory_functions.h"

int parseFlags(int argc, char *argv[], GrepConfig *grepConfig);

#endif