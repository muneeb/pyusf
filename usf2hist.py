#!/usr/bin/python
import sys
import pyusf

from uart.utils import print_and_exit
from uart.hist  import Hist

usage_str = "usage: usf2hist.py [INFILE] [OUTFILE]"

class Args:
    def __init__(self):
        self.i_file_name = ""
        self.o_file_name = None

    def parse(self):
        if len(sys.argv) <= 1:
            print_and_exit(usage_str, 0)

        if len(sys.argv) > 1:
           self.i_file_name = sys.argv[1]

        if len(sys.argv) > 2:
            self.o_file_name = sys.argv[2]

def parse_usf(usf_file):
    dict_ = {}
    for event in usf_file:
        if event.type == pyusf.USF_EVENT_SAMPLE:
            rdist = event.end.time - event.begin.time - 1
        elif event.type == pyusf.USF_EVENT_DANGLING:
            rdist = sys.maxint
        else:
            continue

        if dict_.has_key(rdist):
            dict_[rdist] += 1
        else:
            dict_[rdist] = 1

    return Hist(dict_)


def main():
    args = Args()
    args.parse()

    try:
        usf_file = pyusf.Usf(args.i_file_name)
    except IOError, e:
        print_and_exit(str(e))

    hist = parse_usf(usf_file)
    hist.dump(args.o_file_name)

    usf_file.close()

if __name__ == "__main__":
    main()
