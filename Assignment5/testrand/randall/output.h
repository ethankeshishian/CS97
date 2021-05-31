#ifndef OUTPUT_H
#define OUTPUT_H

int
create_output(long long nbytes, unsigned long long (*rand64) (void),
	      void (*finalize) (void), int nKB);

void
output_error(char *msg, char *errtype);

void
arg_error(char* argv);

#endif
