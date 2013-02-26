#!/usr/bin/python
import sys
import pyusf
import inspect
import numpy

usage_str = '''Usage: usfdump [OPTION...] FILE
Dumps the contents of a USF file in human readable form.
'''

def print_and_exit(s, ret = 1):
    print >> sys.stderr, s
    sys.exit(ret)

class Args:
    def __init__(self):
        self.file_name = None

    def parse(self):
        if len(sys.argv) != 2:
            print_and_exit(usage_str)
        self.file_name = sys.argv[1]

def print_header(header):
    version_major = (header.version >> 16) & 0xffff
    version_minor = header.version & 0xffff

    def line_sizes(line_size_mask):
        s = ""
        for i in range(32):
            if line_size_mask & (1 << i):
                s += "%s " % (1 << i)
        return s.strip()

    print "Header:"
    print "\tVersion: %d.%d" % (version_major, version_minor)
    print "\tCompression: %d (%s)" % (header.compression,
                                      pyusf.strcompr(header.compression))
    print "\tFlags: 0x%.8x" % (header.flags)
    print "\tSampling time: %d-%d" % (header.time_begin, header.time_end)
    print "\tLine sizes: %s" % (line_sizes(header.line_sizes))
    print "\tCommand line: "


def string_access(a):
    return "[tid: %u pc: 0x%x addr: 0x%x time: %d len: %d type: %d (%s)]" % \
           (a.tid, a.pc, a.addr, a.time, a.len, a.type, pyusf.stratype(a.type))

def print_sample(sample):
    print "[SAMPLE] pc1: %s, pc2: %s, ls: %d" % (string_access(sample.begin),
                                                 string_access(sample.end),
                                                 1 << sample.line_size)
def print_stride(stride):
    print "[STRIDE] pc1: %s, pc2: %s, ls: %d" % (string_access(stride.begin),
                                                 string_access(stride.end),
                                                 1 << stride.line_size)
def print_smptrace(smptrace):
    print "[SMPTRACE] pc1: %s" % (string_access(smptrace.begin))
    a = numpy.ndarray( (32,),dtype= numpy.uint64, buffer=smptrace.ins_trace)
    print a
#    a = np.fromiter(smptrace.ins_trace, dtype=np.float, count=DataLength.value)
   
def print_dangling(dangling):
    print "[DANGLING] pc1: %s, ls: %d" % (string_access(dangling.begin),
                                          1 << dangling.line_size)

def print_burst(burst):
    print "[BURST] begin_time: %d" % burst.begin_time

def print_trace(trace):
    print "[TRACE] pc1: %s" % string_access(trace.access)

def print_event(event):
    print_event_map = {0: print_sample, \
                       1: print_dangling, \
                       2: print_burst, \
                       3: print_trace, \
                       4: print_stride, \
                       5: print_smptrace }

    print_event_map[event.type](event)

def main():
    args = Args()
    args.parse()

    usffile = pyusf.Usf(args.file_name)

    print_header(usffile.header)
    for event in usffile:
        print_event(event)

    usffile.close()

if __name__ == "__main__":
    main()
