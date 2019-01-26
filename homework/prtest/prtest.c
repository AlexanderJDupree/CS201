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

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEFAULT_FILE "test.txt"

void usage();

// Displays the text with a random lower case character modified
void display_with_error(const char* text);

// Returns size of file in bytes. Return -1 if file is NULL
long int file_size(FILE* file);

// Returns argv[1] or default file name
const char* get_file_name(int argc, char** argv);

// Reads the entire file into an ALLOCATED char buffer. Caller is responsible
// DEALLOCATION
char* read_file(FILE* file);

// Returns a random int in the range (min, max) inclusive
int random_int(int min, int max);

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0

int main(int argc, char** argv)
{
    // Seeds the generator with the unique process ID
    srandom(getpid()); 

    FILE* file = fopen(get_file_name(argc, argv), "r");

    char* file_contents = read_file(file);

    if(file_contents)
    {
        display_with_error(file_contents);
    }
    else
    {
        usage();
        return -1;
    }

    fclose(file);
    free(file_contents);

    return 0;
}

#endif

void usage()
{
    fprintf(stderr, "prtest: usage: prtest [<path to file>]\n");
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

        char* contents = (char*) calloc(size + 1, sizeof(char));

        // grab character from stream, store it into contents. Ensure it isn't
        // EOF char and ensure we don't write past the buffer size
        int i = 0;
        while( i < size && (*(contents + i++) = fgetc(file)) != EOF)

        *(contents + i) = '\0'; // Add null termination to the end of string

        return contents;
    }

    return NULL;
}

int random_int(int min, int max)
{
    return min + random() % (max - min);
}

