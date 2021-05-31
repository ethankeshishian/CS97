#!/usr/bin/python

"""
Output lines selected randomly

$Id: shuf.py,v 1.0 2020/010/23 23:55:00 Ethan $
"""


import random
import sys
import string
import argparse


def main():
    #     version_msg = "%prog 2.0"
    #     usage_msg = """%prog [OPTION]... FILE

    # Output randomly selected lines. """

    parser = argparse.ArgumentParser()
    # parser = argparse.ArgumentParser(description=version_msg, usage=usage_msg)
    parser.add_argument("-n", "--head-count",
                        action="store", dest="numlines", default=None, type=int,
                        help="Output at most count lines. By default, all input lines are output.")
    parser.add_argument('-e', '--echo', dest="echo_dest", action="store_true",
                        help='Treat each command-line operand as an input line.')
    parser.add_argument('-r', '--repeat', dest="rep_dest", action="store_true",
                        help='Repeat output values, that is, select with replacement. With this option the output is not a permutation of the input; instead, each output line is randomly chosen from all the inputs. This option is typically combined with --head-count; if --head-count is not given, shuf repeats indefinitely.')
    parser.add_argument('-i', '--input-range', dest="range_dest",
                        help='Act as if input came from a file containing the range of unsigned decimal integers lo...hi, one per line.')
    parser.add_argument('inputs', metavar='N', nargs='*',
                        help='List of lines, separated by spaces')
    args = parser.parse_args(sys.argv[1:])

    lines = []
    if (args.range_dest != None):
        if (not args.inputs == [] or args.echo_dest):
            parser.error("Too many parameters")
        if (args.range_dest.count("-") != 1):
            parser.error("Incorrect range syntax")
        try:
            i_range = tuple(args.range_dest.split("-"))
            range_min = int(i_range[0])
            range_max = int(i_range[1])
            if (range_min > range_max):
                parser.error("Incorrect range syntax")
            while (range_min <= range_max):
                lines.append(range_min)
                range_min += 1
        except:
            parser.error("Incorrect range syntax")
    else:
        # Read stdin into lines
        if (args.inputs == [] or args.inputs[0] == '-'):
            if (args.echo_dest or args.range_dest or len(args.inputs) > 1):
                parser.error("Too many parameters")
            for new_line in sys.stdin:
                new_line = remove_newline(new_line)
                lines.append(new_line)
        # Read echo into lines
        elif (args.echo_dest):
            lines = args.inputs
        # Read from file
        else:
            try:
                f = open(args.inputs[0], 'r')
                lines = f.readlines()
                f.close()
            except:
                parser.error("Error reading file")
            i = 0
            while i < len(lines):
                lines[i] = remove_newline(lines[i])
                i += 1
    # Loop through list, randomly outputting one line per iteration
    i = 0
    input_length = len(lines)
    n_is_set = (args.numlines != None)
    r_is_set = (args.rep_dest)
    r_is_set_without_n = ((not n_is_set) and (r_is_set))
    if (r_is_set and n_is_set):
        input_length = args.numlines
    if (n_is_set):
        if (args.numlines < 0):
            parser.error("NUMLINES cannot be less than 0")
        if (args.numlines < input_length):
            input_length = args.numlines

    if (n_is_set and args.numlines < input_length):
        if (r_is_set):
            input_length = args.numlines

    while (i < input_length):
        rand_index = random.choice(range(len(lines)))
        if (r_is_set):
            output = lines[rand_index]
        else:
            output = (lines.pop(rand_index))
        print(output)
        if (r_is_set_without_n):
            continue
        i += 1


def remove_newline(line):
    return line.rstrip('\n')


if __name__ == "__main__":
    main()
