#include <stdlib.h>
#include <time.h>

/* mrand implementation.  */

static struct drand48_data buf = {0};

/* Initialize the mrand implementation.  */
void
mrand_init (char *path){
  long int seed = time(NULL);
  srand48_r(seed, &buf);
}

/* Return a random value, using mrand.  */
unsigned long long
mrand (void){
  long int a;
  long int b;
  mrand48_r(&buf, &a);
  mrand48_r(&buf, &b);
  return ((((unsigned long long) a) << 32) | ((unsigned long long) b & 0x00000000FFFFFFFF));
}

/* Finalize the mrand implementation.  */
void
mrand_fini (void){
}