#!/usr/bin/python
import sys
import pyusf
import random
from optparse import OptionParser

def print_err(s):
    print >> sys.stderr, s

def print_and_exit(s, ret = 1):
    print_err(s)
    sys.exit(ret)

def usage():
    usage_str = "Usage:"
    print_and_exit(usage_str, 0)


def parse_args():
    usage = "usage: %prog [OPTIONS...] INFILE"
    parser = OptionParser(usage)
    parser.add_option("-o", "--out-file",
                      dest = "ofile_name",
                      help = "Output usf file",
                      metavar = "FILE")
    parser.add_option("-b", "--burst-period",
                      type = "int", default = 0,
                      dest = "burst_period",
                      help = "Average time between bursts")
    parser.add_option("-z", "--burst-size",
                      type = "int", default = 0,
                      dest = "burst_size",
                      help = "Burst size in time")
    parser.add_option("-s", "--sample-period",
                      type = "int", default = 0,
                      dest = "sample_period",
                      help = "Average time between samples")
    (opts, args) = parser.parse_args()

    if len(args) > 0:
        opts.ifile_name = args[0]

    if not opts.ifile_name:
        parser.error("No input file specified")
    if not opts.ofile_name:
        parser.error("No output file specified")
    
    return opts

def usf_create_header():
    header = pyusf.Header()
    header.version = pyusf.USF_VERSION_CURRENT
    header.compression = pyusf.USF_COMPRESSION_NONE
    header.flags = pyusf.USF_FLAG_NATIVE_ENDIAN
    header.time_begin = 0
    header.time_end = 0
    return header

def usf_open(file_name):
    usf_file = pyusf.Usf()
    try:
        usf_file.open(file_name)
    except IOError, e:
        print_and_exit(str(e))
    return usf_file

def usf_create(file_name):
    usf_file = pyusf.Usf()
    try:
        usf_file.create(file_name, usf_create_header())
    except IOError, e:
        print_and_exit(str(e))
    return usf_file

def usf_time(event):
    if isinstance(event, pyusf.Sample):
        return event.begin.time
    if isinstance(event, pyusf.Dangling):
        return event.begin.time
    if isinstance(event, pyusf.Burst):
        return event.begin_time
    if isinstance(event, pyusf.Trace):
        return event.access.time

first = True
def usf_read_burst(usf_file):
    global first
    event_list = []
    for event in usf_file:
        if isinstance(event, pyusf.Burst):
            if first: continue
            else :    break
        first = False
        event_list.append(event)
    event_list.sort(lambda x, y: cmp(usf_time(x), usf_time(y)))
    return event_list

def usf_append_burst(usf_file, burst):
    burst_event = pyusf.Burst()
    burst_event.begin_time = usf_time(burst[0])
    
    usf_file.append(burst_event)
    for event in burst:
        usf_file.append(event)


def resample(events, burst_period, burst_size, sample_period):
    def exp_rnd(period):
        if period:
            return int(round(random.expovariate(1.0 / period)))
        else:
            return 0

    def period(burst):
        return (usf_time(burst[-1]) - usf_time(burst[0])) / (len(burst) - 1)
    
    def sample(burst, sample_period):
        if sample_period:
            s = random.sample(burst, len(burst) / sample_period)
        else:
            s = burst
        s.sort(lambda x, y: cmp(usf_time(x), usf_time(y)))
        return s

    used_sample_period = period(events)

    period_err_str = "New %s-period is less the sample-period of the input"
    if burst_period and burst_period < used_sample_period:
        print_and_exit(period_err_str % ("burst"))
    if sample_period and sample_period < used_sample_period:
        print_and_exit(period_err_str % ("sample"))
                        
    burst_period  /= used_sample_period
    burst_size    /= used_sample_period
    sample_period /= used_sample_period

    burst_list = []
    if burst_size:
        burst_start = exp_rnd(burst_period)
        while burst_start < len(events):
            burst = events[burst_start:burst_start + burst_size]
            burst = sample(burst, sample_period)
            if burst:
                burst_list.append(burst)
            burst_start += burst_size + exp_rnd(burst_period)
    else:
        burst_list.append(sample(burst), sample_period)

    return burst_list
        

def main():
    args = parse_args()

    usf_ifile = usf_open(args.ifile_name)
    usf_ofile = usf_create(args.ofile_name)

    burst = usf_read_burst(usf_ifile)
    while burst:
        burst_list = resample(burst,
                              args.burst_period,
                              args.burst_size,
                              args.sample_period)

        for b in burst_list:
            usf_append_burst(usf_ofile, b)

        burst = usf_read_burst(usf_ifile)

    usf_ifile.close()
    usf_ofile.close()


if __name__ == "__main__":
    main()
