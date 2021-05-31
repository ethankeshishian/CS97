# Make x86-64 random byte generators.

# Copyright 2015, 2020 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = --xz --transform 's,^,randall/,'
TAREXT = tgz

default: randall

randall: randall.c output.c options.c rand64-sw.c rand64-hw.c mrand.c
	$(CC) $(CFLAGS) $^ -o $@

assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) -cf $@ $(assignment-files)

submission: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt rand64-sw.h rand64-sw.c rand64-hw.h rand64-hw.c output.h output.c \
  options.h options.c mrand.h mrand.c # Other files added.
randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) -cf $@ $(submission-files)

.PHONY: check default clean assignment submission

clean:
	rm -f *.o *.$(TAREXT) randall

check: randall check1 check2 check3 check4 check5 check6 check7 check8 check9

check1:
	@if [ `./randall 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check2:
	@if [ `./randall -i rdrand 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check3:
	@if [ `./randall -i mrand48_r 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check4:
	@if [ `./randall -i /dev/urandom 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check5:
	@if [ `./randall -o stdio 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check6:
	@if [ `./randall -o 100 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check7:
	@if [ `./randall -i rdrand -o 100 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check8:
	@if [ `./randall -i mrand48_r -o 100 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;

check9:
	@if [ `./randall -i /dev/urandom -o 100 100 | wc -c` -eq 100 ]; \
	then echo "test passed -> ./randall 100 "; \
	else echo "test failed -> ./randall 100 "; \
	fi;
