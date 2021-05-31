#include "options.h"
#include "output.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int iflag = 0;
static int oflag = 0;
static long long nbytes;
static char *ival;
static char *oval;

int
handle_input(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, ":i:o:")) != -1) {
    switch (opt){
    case 'i':
      if (iflag > 0){
        arg_error(argv[0]);
        return 1;
      }
      iflag++;
      if ((strcmp(optarg, "rdrand") == 0) || (strcmp(optarg, "mrand48_r") == 0)) 
        ival = optarg;
      else if (optarg[0] == '/')
        ival = optarg;
      else{
        arg_error(argv[0]);
        return 1;
      }
      break;
    case 'o':
      if (oflag > 0){
        arg_error(argv[0]);
        return 1;
      }
      oflag++;
      if (strcmp(optarg, "stdio") == 0)
        oval = optarg;
      else{
        bool valid = false;
        char *endptr;
        errno = 0;
        strtoll(optarg, &endptr, 10);
        if (errno)
            output_error(argv[1], "perror");
        else
            valid = true;
        if (!valid)
        {
            arg_error(argv[0]);
            return 1;
        }
      }
      oval = optarg;
      break;
    case ':':
      arg_error(argv[0]);
      return 1;
    case '?':
      arg_error(argv[0]);
      return 1;
    default:
      arg_error(argv[0]);
      return 1;
    } // end switch

  }
  /* Check main arguments.  */
  if (optind != (argc - 1)){
      arg_error(argv[0]);
      return 1;
  }
  bool valid = false;
  char *endptr;
  errno = 0;
  nbytes = strtoll (argv[optind], &endptr, 10);
  if (errno)
      output_error(argv[1], "perror");
  else
      valid = !*endptr && 0 <= nbytes;
  if (!valid)
  {
      arg_error(argv[0]);
      return 1;
  }
  if (nbytes < 0){
      arg_error(argv[0]);
      return 1;
  }
  return 0;
}

//These two may be unnecessary
bool
get_iflag(){
  return iflag;
}

bool
get_oflag(){
  return oflag;
}

char*
get_ival(){
  return ival;
}

char*
get_oval(){
  return oval;
}

long long
get_nbytes(){
    return nbytes;
}