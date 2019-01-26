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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_FILE "test.txt"

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0

void usage();

// Returns size of file in bytes. Return -1 if file is NULL
long int file_size(FILE* file);

// Returns argv[1] or default file name
const char* get_file_name(int argc, char** argv);

// Reads the entire file into an ALLOCATED char buffer. Caller is responsible
// DEALLOCATION
char* read_file(FILE* file);

// Returns a random int in the range (min, max) inclusive
int random_int(int min, int max);

int main(int argc, char** argv)
{
    FILE* file = fopen(get_file_name(argc, argv), "r");

    char* file_contents = read_file(file);

    if(file_contents)
    {
        // do stuff
    }
    else
    {
        usage();
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

long int file_size(FILE* file)
{
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
    if(file) // File opened successfully
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
    // PID is unique to this process, so this seed can get moved to a higher
    // scope to ensure other calls to random are already seeded
    srandom(getpid());

    return min + random() % (max - min);
}
