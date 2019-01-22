Alexander DuPree

Homework 1

Homework 1 tasked us with computing bitsets and outputting the results of the 
computation to the console. This assignment was a fun and challenging activity, as
I have never directly manipulated bits in a C program and learning about bitwise
operations was a welcome experience. 

bittool.c contains 8 functions, but the main workhorse functions are the 
validate_arg, set_bits, and showbits functions. The other functions are 
subroutines that log errors, or display usage information. The assignment 
required us to parse arguments from the command line as 32bit unsigned integers,
then based on the number of arguments either take the bit intersection of two
numbers or set bits to 1 given a list of bit positions as arguments.

The validate_arg function handles the command line parsing by attempign to 
convert the C-string into a 32 bit unsigned integer. The parser runs the result
of the conversion through the rule set for the program and logs any errors that
occur and returns 1, signalling to the main that the parsing failed. If the
parsing is successful the result of the conversions are stored into a 
32 bit integer array that is allocated in main. Main then stores the result of 
the validate_arg function (either 0 or 1) into a exit_status variable and if the
exit_status is still 0, then the program continues. Otherwise main will free the
integer array and exit with 1.

With the arguments successfully parsed we are left with an integer array that 
only contains valid integer arguments. if the number of arguments was 2, then 
main will mask the first and second argument together (creating a 32bit number
with only common bits) and pipe that result into the show_bits32 function. If 
argument count was more than 2 then the arguments are treated as a list of
bit positions. This bit position list is forwarded to the set_bits function 
which returns a 16 bit number with the indicated bit positions set to 1. This
result is piped into the show_bits16 function which prints out the binary 
representation of the number to the console. 

To test this program, I got lazy and just manually provided a series of arguments
through the command line. I ensured the output matched the ones outlined in the
assignment description and those provided by Arash Mirhosseini on slack. Generally,
I spin up a suite of unit tests with the catch2 unit testing framework 
(https://github.com/catchorg/Catch2), however, I didn't get around to doing that
this time around.



