/*
 * File: prtest.c
 *
 * Brief:
 *
 * Author: Alexander DuPree
 *
 * Date: 24JAN2019
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define DEFAULT_FILE "test.txt"

void usage();

// Displays the text with a random lower case character modified
void display_with_error(const char* text);

// Returns size of file in bytes. Return -1 if file is NULL
long int file_size(FILE* file);

// Returns argv[1] or DEFAULT_FILE name
const char* get_file_name(int argc, char** argv);

// Reads the entire file into an ALLOCATED char buffer. Caller is responsible
// DEALLOCATION
char* read_file(FILE* file);

// Returns a random int in the range (min, max) inclusive
int random_int(int min, int max);

// Runs the game for N rounds and prints the result of the game and each round
int run_game(const char* text, int rounds);

// 50% chance to display_with_error and return 1. Else print and return 0
int display_text(const char* text);

void display_instructions();

// Returns input as 0, 1, or 2. Writes score as elapsed time in ms into score
int get_input_and_score(int* score);

// Displays success/failure message and accumulated score
void display_score(int score, int state);

// Hides main from the unit tests build
#ifdef UNIT_TESTS
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0

int main(int argc, char** argv)
{
    // Seeds the generator with the unique process ID. This is done in main to 
    // ensure the generator is seeded once and available for all subsequent calls
    srandom(getpid()); 

    const int ROUNDS = 3;

    int exit_status = 0;

    FILE* file = fopen(get_file_name(argc, argv), "r");

    char* file_contents = read_file(file);
    
    if(file_contents)
    {
        exit_status = run_game(file_contents, ROUNDS);
        fclose(file);
    }
    else
    {
        usage();
        exit_status = -1;
    }

    free(file_contents);

    return exit_status;
}

#endif

void usage()
{
    fprintf(stderr, "prtest: usage: prtest [<path to file>]\n"
            "Default file is: '%s' ensure default file exists and is in this"
            " directory)\n", DEFAULT_FILE);
    return;
}

void display_with_error(const char* text)
{
    // Refactor so length is a parameter. strlen is O(n) function and the length
    // of the text was already ascertained during allocation
    int length = strlen(text);

    int random_index = 0;
    char random_char = '\0';

    // Ensures a lower case character will be replaced
    while(!islower(text[random_index = random_int(0, length)]));

    // Ensures the random_char isn't the same as the one its replacing
    while(text[random_index] == (random_char = random_int('a', 'z')));

    int i = 0;
    for(; i < random_index; ++i)
    {
        printf("%c", text[i]);
    }

    printf("%c", random_char);

    for(++i; i < length; ++i)
    {
        printf("%c", text[i]);
    }
    return;
}

long int file_size(FILE* file)
{
    // ftell returns a long int, thus long int is used here as well
    long int size = -1;

    if(file)
    {
        fseek(file, 0L, SEEK_END);

        size = ftell(file);

        fseek(file, 0L, SEEK_SET);
    }
	
    return size;
}

const char* get_file_name(int argc, char** argv)
{
    if(argc == 2) // User supplied a file name
    {
        return argv[1];
    }
    else if(argc == 1)
    {
        return DEFAULT_FILE;
    }
    return NULL; // User entered too many args, program fails
}

char* read_file(FILE* file)
{
    if(file)
    {
        int size = file_size(file);

        char* contents = (char*) malloc(size + 1 * sizeof(char));

        // grab character from stream, store it into contents. Ensure it isn't
        // EOF char and ensure we don't write past the buffer size
        int i = 0;
        while( i < size && (*(contents + i++) = fgetc(file)) != EOF)

        *(contents + i) = '\0'; // Add null terminator to the end of string

        return contents;
    }

    return NULL;
}

int random_int(int min, int max)
{
    // % by 0 check. Return 0 else return random int in range (min, max) inclusive
    return (max - min == -1) ? 0 : min + random() % (max - min + 1);
}

int run_game(const char* text, int rounds)
{
    int total_score = 0;
    int state = 0;
    unsigned char input = 0;

    for(int i = 0; i < rounds; ++i)
    {
        // Score is the response time of the user in ms
        int score = 0;

        // State is either 0 (No errors in text) or 1 (displayed with error)
        state = display_text(text);

        input = get_input_and_score(&score);

        if(input > 1) // User quit
        {
            return input;
        }

        // If the user answered incorrectly add 5000 to score and display.
        (state = (state == input)) ? display_score(score, state) 
                                   : display_score(score += 5000, state);
        total_score += score;
    }
    printf("\n%d rounds, total score %d\n", rounds, total_score);
    return 0;
}

int display_text(const char* text)
{
    int state = 0;

    printf("\n");
    if ((state = random_int(0, 1)))
    {
        display_with_error(text);
    }
    else
    {
        printf("%s", text);
    }
    return state;
}

void display_instructions()
{
    printf("\nType 'y' if the text is OK, or 'n' if there was an error."
           "\nType 'q' or any other character to quit\n>  ");
    return;
}

int get_input_and_score(int* score)
{
    int input = 0;

    struct timeval start, end;

    display_instructions();

    gettimeofday(&start, NULL);

    // Ensures input is not a newline of EOF char
    while((input = getchar()) == '\n' || input == EOF);

    gettimeofday(&end, NULL);

    // Composes two units, seconds and microseconds, into time elapsed in ms
    *score = ((end.tv_sec - start.tv_sec) * 1000) + 
             ((end.tv_usec - start.tv_usec) / 1000);
    
    switch(input)
    {
        case 'y' : return 0;
        case 'n' : return 1;
        default  : return 2;
    }
};

void display_score(int score, int state)
{
    if(state)
    {
        printf("Correct! for %d points!\n", score);
    }
    else
    {
        printf("Incorrect! A 5000 point penalty was added to %d points for a "
               "total of %d points\n", score - 5000, score);
    }
}

