#include "output.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static bool
writebytes (unsigned long long x, int nbytes)
{
  do
    {
      if (putchar (x) < 0)
	return false;
      x >>= CHAR_BIT;
      nbytes--;
    }
  while (0 < nbytes);

  return true;
}

int
create_output(long long nbytes, unsigned long long (*rand64) (void),
	      void (*finalize) (void), int nKB){
  int output_errno = 0;
  int wordsize = sizeof rand64 ();
  if (nKB == 1){
    do
      {
        unsigned long long x = rand64 ();
        int outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (!writebytes (x, outbytes))
	  {
	    output_errno = errno;
	    break;
	  }
        nbytes -= outbytes;
      }
    while (0 < nbytes);
  }
  else{
    long long *buf = malloc(nKB);
    int totalbytes = nbytes;
    do
      {
        int outbytes = totalbytes < nKB ? totalbytes : nKB;
        int bytesleft = outbytes;
        int i = 0;
      do
        {
          unsigned long long x = rand64 ();
          buf[i] = x;
          i += 1;
          bytesleft -= sizeof(x);
        } 
      while (bytesleft > 0);
        // write!
        write(1, buf, outbytes);
        totalbytes -= outbytes;
      }
    while (totalbytes > 0);
    free(buf);
  }
  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      output_error("output" , "perror");
    }
  finalize ();
  return !!output_errno;
}

void
output_error(char *msg, char *errtype)
{
  if (strcmp(errtype, "perror") == 0)
    perror(msg);
  else if (strcmp(errtype, "fprintf") == 0)
    fprintf(stderr, msg);
}

void
arg_error(char* argv){
  char msg[100];
  snprintf(msg, sizeof(msg), "%s: usage: %s [-i INPUT] [-o OUTPUT] NBYTES\n", argv, argv);
  output_error(msg, "fprintf");
}
