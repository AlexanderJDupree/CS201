/*
 * File: prtest.c
 *
 * Brief: Proofreading test (prtest) app prints the contents of a specified file
 *        to the console and asks the user if the contents were altered. The 
 *        user is scored by their response time in ms. 
 *
 * Author: Alexander DuPree
 *
 * Date: 24JAN2019
 *
 */

#include <stdlib.h>   // srandom()
#include <ctype.h>    // islower()
#include <unistd.h>   // getpid()
#include <string.h>   // strlen

#include "timer.h"
#include "file_reader.h"

void usage();

// Displays the text with a random lower case character replaced, returns index
// of replaced character
int display_with_error(const char* text, int length);

// Returns argv[1] or DEFAULT_FILE name
const char* get_file_name(int argc, char** argv);

// Returns a random int in the range (min, max) inclusive
int random_int(int min, int max);

// Runs the game for N rounds and prints the result of the game and each round
int run_game(struct File_Reader* reader, int rounds);

// 50% chance to display_with_error and return 1. Else print w/out error return 0
int display_text(const char* text, int length);

void display_instructions();

// Returns input as 0 for 'y' 1 for 'n' and anything else as 2
int get_input();

// Displays success/failure message and accumulated score
void display_score(int score, int state);

const char* DEFAULT_FILE =  "test.txt";

// Hides main from the unit tests build
#ifndef UNIT_TESTS
int main(int argc, char** argv)
{
    // Seeds the generator with the unique process ID. This is done in main to 
    // ensure the generator is seeded once and available for all subsequent calls
    srandom(getpid()); 

    int exit_status = 0;
    const int ROUNDS = 3;

    struct File_Reader* reader = open_file(get_file_name(argc, argv));

    if((exit_status = run_game(reader, ROUNDS)))
    {
        usage();
    }

    close_reader(reader);

    return exit_status;
}
#endif

void usage()
{
    fprintf(stderr, "prtest: usage: prtest [<path to file>]\n"
            "\nDefault file ('%s') does not exist in this directory or supplied"
            " file was empty\n", DEFAULT_FILE);
    return;
}

int display_with_error(const char* text, int length)
{
    int replacement_index = 0;
    char replacement_char = '\0';

    // Ensures a lower case character will be replaced
    while(!islower(text[replacement_index = random_int(0, length)]));

    // Ensures the random_char isn't the same as the one its replacing
    while(text[replacement_index] == (replacement_char = random_int('a', 'z')));

    int i = 0;
    for(; i < replacement_index; ++i)
    {
        printf("%c", text[i]);
    }

    printf("%c", replacement_char);

    for(++i; i < length; ++i)
    {
        printf("%c", text[i]);
    }
    return replacement_index;
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

int random_int(int min, int max)
{
    // % by 0 check. Return 0 else return random int in range (min, max) inclusive
    return (max - min == -1) ? 0 : min + random() % (max - min + 1);
}

int run_game(struct File_Reader* reader, int rounds)
{
    if (!reader || !reader->contents)
    {
        return 1;
    }

    int total_score = 0;
    int state = 0;
    unsigned char input = 0;

    for(int i = 0; i < rounds; ++i)
    {
        // Score is the response time of the user in ms
        int score = 0;

        // State is either 0 (No errors in text) or 1 (displayed with error)
        state = display_text(reader->contents, reader->size);

        timer_start();
        input = get_input();
        timer_stop();

        score = elapsed_time(MILLISECONDS);

        if(input <= 1)
        {
            // If the user answered incorrectly add 5000 to score then display.
            (state = (state == input)) ? display_score(score, state) 
                                       : display_score(score += 5000, state);
            total_score += score;
        }
        else // User quit
        {
            rounds = i;
        }
    }
    printf("\n%d rounds, total score %d\n", rounds, total_score);
    return 0;
}

int display_text(const char* text, int length)
{
    int state = random_int(0, 1);

    printf("\n");

    (state) ? display_with_error(text, length) : printf("%s", text);
    return state;
}

void display_instructions()
{
    printf("\nType 'y' if the text is OK, or 'n' if there was an error."
           "\nType 'q' or any other character to quit\n>  ");
    return;
}

int get_input()
{
    int input = 0;

    display_instructions();

    // Ensures input is not a newline of EOF char
    while((input = getchar()) == '\n' || input == EOF);

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

