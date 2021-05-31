/* Software implementation.  */

#include "rand64-sw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Input stream containing random bytes.  */
FILE *urandstream;

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (char *path)
{
  char *inpath = "/dev/random";
  if (strcmp(path, inpath) != 0)
    inpath = path;
  urandstream = fopen (inpath, "r");
  if (! urandstream)
    exit(1);
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    exit (1);
  return x;
}

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void)
{
  fclose (urandstream);
}
