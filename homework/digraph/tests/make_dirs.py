#!/usr/bin/python
#Brief: Simple utility to generate nested test directories
#Author: Alexander DuPree

import os, sys

def main(argv):

    if len(argv) > 1 or len(argv) == 0:
        usage()
        return 1

    make_dirs(argv[0]);

    return 0

def make_dirs(num):
    for i in range(int(num)):
        dir = "level" + str(i)
        os.mkdir(dir)
        os.chdir(dir)
    return

def usage():
    print("""
            Usage:
                make_test_dirs.py NUM

            Note:
                
                make_test_dirs.py will create NUM nested directories labeled 
                level0 to level<NUM>. 

                Use rm -r level0 to remove all generated directories
            """)

if __name__ == "__main__":
    main(sys.argv[1:])

