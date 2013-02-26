#!/usr/bin/python
from distutils.core import setup, Extension

module1 = Extension('pyusf',
                    sources = ['pyusfmodule.c', 'usf_obj.c',     \
                               'header_obj.c', 'sample_obj.c',   \
                               'access_obj.c', 'dangling_obj.c', \
                               'burst_obj.c', 'trace_obj.c',     \
                               'stride_obj.c', 'smptrace_obj.c' ],
                    libraries = ['usf', 'bz2'])

setup(name = 'usf', version = '1.0', description = 'XXX',
      ext_modules = [module1])
