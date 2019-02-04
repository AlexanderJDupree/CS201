Alexander DuPree

CS201 
Homework 2 - proofreading test (prtest)

================================= USAGE ========================================

prtest usage: prtest [<path to file>]

Default file is 'test.txt' and, if used, must be in the same directory of prtest.c

Note:
    Build Application: make
	Build Unit tests:  make tests
	Clean obj files:   make clean

    Run Application: ./prtest
    Run Unit Tests: ./tests/obj/debug/run_tests

Built With:

    Catch2 - CPP unit testing framework
    https://github.com/catchorg/Catch2

================================ WRITEUP =======================================

The prtest homework had essentially 4 components to make it work. File I/O, 
random integer generation, timer utilities, and reading/evaluating user input. 
Since I knew this wouldn't be the last time I read a file into memory or time 
something in C, I moved the functionality of those utilities into their own 
seperate header and source files. This seperation of responsibilites helped 
simplify my code and make it more manageable. 

The actual prtest program first loads the entire contents of a file into an 
allocated const char* with the file_reader utility I made. Then once that is
handled we run the game. The run_game function is the heart of this program. 
First we check if file_reader utility was actually able to read in the 
specified file. If that failed then we return 1 to main, signalling a failure. 
If the file_reader was successful then we display the text with a 50% chance of
an error and start the timer. The user's response is then evaluated and the timer
is stopped; using the elapsed time as the score. This is then repeated for the
number of specified rounds (default is 3). 

The following is a sample run of the program:

    echo "Hello World\nI am Alex" > test.txt
    ./prtest test.txt

    Hello World
    I am Alkx

    Type 'y' if the text is OK, or 'n' if there was an error.
    Type 'q' or any other character to quit
    >  n
    Correct! for 2228 points!

    Hello World
    I am Alex

    Type 'y' if the text is OK, or 'n' if there was an error.
    Type 'q' or any other character to quit
    >  y
    Correct! for 1399 points!

    Hello World
    I am Alex

    Type 'y' if the text is OK, or 'n' if there was an error.
    Type 'q' or any other character to quit
    >  n
    Incorrect! A 5000 point penalty was added to 2815 points for a total of 7815 points

    3 rounds, total score 11442

If an invalid file was entered or the file entered was empty the prtest will 
display a usage message and quit.

