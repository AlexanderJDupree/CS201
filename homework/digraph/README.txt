Alexander DuPree

CS201 
Homework 3 - digraph

================================= USAGE ========================================

usage:
  digraphs <options>
Options:
  -h or -?          Displays usage info
  -t <path to file>	Path to file to be analyzed by digraphs
  -p <directory>	Path to directory to be recursively analyzed
  -c <integer>		Number of top digraphs to be displayed

Note:
    Build Application: make
	Build Unit tests:  make tests
	Clean obj files:   make clean

    Run Application: ./digraphs <options>
    Run Unit Tests: ./tests/obj/debug/run_tests

Built With:

    Catch2 - CPP unit testing framework
    https://github.com/catchorg/Catch2

================================ WRITEUP =======================================

The Digraphs assignment was a fun exercise in parsing text into a directed graph
structure, reading files, and crawling the Linux filesystem. The first step to 
this assignment was decided how I wanted to represent the digraph in memory. 
Initially I used a 52x52 2D uint64_t array, where each index represented a 
unique digraph combonation. This method provided some benefits, namely fast
random access. However, displaying the top N digraphs using an adjacency matrix
was problematic, as the matrix can't be sorted without losing the context of what
value is associated with which digraph. Therefore, it would be required to loop 
through the adjacency matrix and build an array of results objects that contain the 
digraph and its frequency, then the array is sorted, and finally, the top N digraphs
are displayed. Instead, I opted to construct this results array from the onset to 
help simplify my code by keeping the digraph and its frequency packaged together. 
The main drawback of this method was the higher memory overhead, however I found it 
to be a managable amount for modern machines. This results array, or edge list, was 
also constructed in such fashion that the indexes for the adjacency matrix would 
be analagous to those in the edge list. 

For the other features of the digraphs assignment I used pretty standard solutions.
For command line parsing the getopt library was used, file reading was
accomplished through the file_reader utility I developed for the last assignment,
and the directory crawler was compressed into a recursive function.

Below is a sample run of the program with the provided test.txt and my home directory:

./digraphs -t test.txt -p ~/ -c 10

Analysis of: test.txt
Alphabetic Characters: 58
Top 10 Digraphs:
   th : 2
   ap : 2
   ea : 2
   er : 2
   in : 2
   xt : 1
   ch : 1
   di : 1
   ai : 1
   ac : 1

Analysis of: /home/chaos2022/
Alphabetic Characters: 3522282
Top 10 Digraphs:
   er : 51318
   es : 44772
   ng : 43526
   in : 42499
   va : 40757
   ar : 40118
   ja : 38197
   on : 37815
   te : 34800
   le : 34396

