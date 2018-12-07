#!/usr/bin/python

import random, sys
from optparse import OptionParser

class shuf:
    def __init__(self, filename = None):
        if filename:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

    def shuffle(self, the_input):
        random.shuffle(the_input)
        return the_input

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Generate random permutations from FILE."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-i", "--input-range",
                      action="store", type="string", dest="input_range", default=None,
                      help="treat each number LO through HI as an input line")
    parser.add_option("-n", "--head-count",
                      action="store", type="int", dest="head_count", default=None,
                      help="output at most COUNT lines")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="repeat",
                      help="output lines can be repeated")
    options, args = parser.parse_args(sys.argv[1:])
    input_range = options.input_range
    head_count = options.head_count
    repeat = options.repeat
    input_file = None

    if args:
        input_file = args[0]

    if head_count:
        head_count = int(head_count)

    try:
      if input_range:
        ir = input_range.split("-")
        start = int(ir[0])
        end = int(ir[1])+1
        input_range = list(range(start, end))
        for i in range(len(input_range)):
            input_range[i] = "{0}\n".format(input_range[i])
    except IOError as err:
      parser.error("invalid input range '{input_range}'")

    try:
        content = []
        if (input_file and input_file != "-"):
            generator = shuf(input_file)
            content = generator.lines
        elif input_range:
            generator = shuf()
            content = input_range
        else:
            generator = shuf()
            for line in sys.stdin:
                content.append(line)

        if content:
          generator.shuffle(content)
          rpt = True
          count = 0
          while rpt and (not(head_count) or count < head_count):
              rpt = repeat
              for e in content:
                  if (head_count and (count == head_count)):
                      break
                  sys.stdout.write("%s" % e)
                  count+=1
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(err.args[0], err.args[1]))

if __name__ == "__main__":
    main()
