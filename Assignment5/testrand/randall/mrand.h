#ifndef MRAND
#define MRAND

/* Software implementation.  */

/* Initialize the software rand64 implementation.  */
void
mrand_init (char *path);

/* Return a random value, using software operations.  */
unsigned long long
mrand (void);

/* Finalize the software rand64 implementation.  */
void
mrand_fini (void);

#endif