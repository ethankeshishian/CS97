#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

int
handle_input(int argc, char *argv[]);

bool
get_iflag();

bool
get_oflag();

char*
get_ival();

char*
get_oval();

long long
get_nbytes();

#endif