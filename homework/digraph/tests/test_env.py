#!/usr/bin/python
#Brief: Simple utility to generate nested test directories
#Author: Alexander DuPree

import os, sys, getopt, random, string

def main(argv):

    exit_status = 0

    flags = {
            '-h' : False,
            '-r' : False,
            '-n' : 'test.txt',
            '-d' : '0',
            '-f' : '0'
            }

    opts, args = get_opts_args(argv)

    for opt, arg in opts:
        flags[opt] = arg if arg != '' else True

    if(flags['-h'] == True):
        usage()
    else:
        try:
            make_dirs(int(flags['-d']))
            make_text_file(int(flags['-f']), flags['-n'], flags['-r'])
        except ValueError as err:
            print(err)
            usage()
            exit_status = 1
    
    return exit_status

def random_word(length):
    return ''.join(random.choice(string.ascii_letters) for i in range(length))

def long_word(length):
    return ''.join('a' for i in range(length))

def make_text_file(length, file_name='test.txt', randomize=False):
    if (length != 0):
        with open(file_name, "w+") as file:
            file.write(random_word(length) if randomize else long_word(length))
        print('\n{} created with size {}\n'.format(file_name, length))
    return

def make_dirs(num = 0):
    for i in range(int(num)):
        dir = "level" + str(i)
        os.mkdir(dir)
        os.chdir(dir)
    if(num != 0):
        print('\n{} directories created!\n'.format(num))
    return

def usage():
    print("""
        Usage:
            test_env.py [options]

        Options:
            -h        Show usage information
            -d <$1>   Creates $1 nested directories
            -f <$1>   Creates test.txt file with $1 characters
            -n <$1>   Sets default file name (test.txt) to $1
            -r        Randomizes characters placed into test.txt
            """)

def get_opts_args(argv):
    try:
        opts, args = getopt.getopt(argv, "hrd:f:n:", [])
    except getopt.GetoptError as err:
        print(err)
        usage()
        sys.exit(1)
    return opts, args

if __name__ == "__main__":
    main(sys.argv[1:])

