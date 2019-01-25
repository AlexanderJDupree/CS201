/*
File: bittool.c

Brief: Filter integers from the input according to filter rules

Author: Alexander DuPree

Class: CS201

*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void log_error(const char* error, const char* arg);

void usage(); // Displays usage info

int validate_input(int argc, char** argv, uint32_t* args);

int validate_arg(int index, int argc, char** argv, uint32_t* args);

// Constructs a uint32_t with the indicated bit positions set to 1
uint32_t set_bits(int size, uint32_t * bit_positions);

// Formatted 32 bit output to console
void show_bits32(uint32_t num);

// Formatted 16 bit output to console
void show_bits16(uint32_t num);

int main(int argc, char **argv) {

    // Allocate array to hold uint32_t arguments
    uint32_t* args = (uint32_t*) calloc(argc - 1, sizeof(uint32_t));

    int exit_status = validate_input(argc - 1, argv + 1, args);

    if(exit_status == 0)
    {
        if (argc == 3) 
        {
            // The result of the mask is a number containing common bits
            show_bits32(args[0] & args[1]);
        }
        else
        {
            show_bits16(set_bits(argc - 1, args));
        }
    }

    free(args);

    return exit_status;
}

void log_error(const char* error, const char* arg)
{
    fprintf(stderr, error, arg);
    return;
}

void usage() 
{
    fprintf(stderr, "bittool: usage: bittool <n> <n> [<n> ...]\n");
    return;
}

int validate_input(int argc, char** argv, uint32_t* args)
{
    // Not enough arguments for the program
    if (argc < 2)
    {
        usage();
        return 1;
    }
    return validate_arg(0, argc, argv, args);
}

// There are 3 too many return statements here
int validate_arg(int index, int argc, char** argv, uint32_t* args)
{
    // Base case: argument variables successfully processed
    if(index >= argc)
    {
        return 0;
    }

    char* arg = *(argv + index);
    char* endptr = arg;

    // Attempt conversion from char* to uint32_t
    int64_t result = strtoll(arg, &endptr, 0);
    if (*endptr != '\0') {
        log_error("bittool: invalid char in number %s\n", arg);
        return 1;
    }
    if (result < 0 || result > UINT32_MAX) {
        log_error("bittool: number %s out of range\n", arg);
        return 1;
    }
    if(argc > 2 && result > 15)
    {
        log_error("bittool: number %s out range (0...15)\n", arg);
        return 1;
    }
    *(args + index) = (uint32_t) result;

    return validate_arg(++index, argc, argv, args);
}

uint32_t set_bits(int size, uint32_t* bit_positions) 
{
    uint32_t result = 0;
    for (int i = 0; i < size; ++i)
    {
        result |= 1 << bit_positions[i];
    }
    return result;
}

void show_bits32(uint32_t num) 
{
    uint32_t mask = 1;

    printf("Bits: ");
    for (int i = 0; mask <= num && i < 32; ++i)
    {
        if((num & mask) > 0)
        {
            printf("%i ", i);
        }
        mask <<= 1;
    }
    printf("\nHex: 0x%x", num);
    printf("\nSigned: %i", num);
    printf("\nunsigned: %u\n", num);
}

void show_bits16(uint32_t num)
{
    for (int i = 15; i >= 0; --i)
    {
        printf("%i", (num >> i) & 1);
    }
    printf("\n");
    return;
}

