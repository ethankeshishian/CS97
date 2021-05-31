/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "options.h"
#include "output.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "mrand.h"
#include <stdlib.h>
#include <string.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  if (handle_input(argc, argv) == 1)
    return 1;

  long long nbytes = get_nbytes();  

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Prepare -o arguments for use with libraries */
  int nKB;
  if (get_oflag() == 0 || (strcmp(get_oval(), "stdio") == 0)){
    nKB = 1;
  }
  else{
    nKB = strtoll(get_oval(), NULL, 10); //error checked in handle_input
    if (nKB <= 0){
      arg_error(argv[0]);
      return 1;
    }
    nKB *=1024;
  }

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize) (char*);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  if (rdrand_supported () && ((get_iflag() == 0) || (strcmp(get_ival(), "rdrand") == 0)))
    {
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    }
  else if (strcmp(get_ival(), "mrand48_r") == 0)
    {
      initialize = mrand_init;
      rand64 = mrand;
      finalize = mrand_fini;
    }
  else if (get_ival()[0] == '/')
    {
      initialize = software_rand64_init;
      rand64 = software_rand64;
      finalize = software_rand64_fini;
    }
  else
    {
      arg_error(argv[0]);
      return 1;
    }

  initialize (get_ival());
  return create_output(nbytes, rand64, finalize, nKB);

}
