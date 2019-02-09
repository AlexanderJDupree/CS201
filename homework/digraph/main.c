/*
 * File: 
 *
 * Brief:
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 *
 */

#include <stdio.h>
#include <getopt.h>
#include "digraph.h"
#include "exceptions.h"
#include "file_reader.h"

void usage();
void display_analysis(Digraph* graph, const char* header, int n);
void display_edge(const char* vertices, long weight);

void file_analysis(Digraph* graph, const char* file_name);
int run_digraphs(const char* file_name, const char* directory, int n);

// Hides main from the unit tests build
#ifndef UNIT_TESTS
int main(int argc, char** argv)
{
    int opt = 0;
    int count = 10; // Default number of digraphs to be shown
    int exit_status = 0;
    const char* file_name = NULL;
    const char* directory = NULL;

    while((opt = getopt(argc, argv, "h?t:p:c:")) != -1)
    {
        switch(opt)
        {
            case 't' : file_name = optarg;
                       break;
            case 'p' : directory = optarg;
                       break;
            default  : break;
        }
    }
    if(file_name == NULL && directory == NULL)
    {
        usage();
        exit_status = -1;
    }
    else
    {
        exit_status = run_digraphs(file_name, directory, count);
    }

    return exit_status;
}
#endif

void usage()
{
    fprintf(stderr, "usage:\n  digraphs <options>\nOptions:\n  "
            "-t <path to file>\tPath to file to be analyzed by digraphs\n  "
            "-p <directory>\tPath to directory to be recursively analyzed\n  "
            "-c <integer>\t\tNumber of top digraphs to be displayed\n");
    return;
}

void display_analysis(Digraph* graph, const char* header, int n)
{
    printf("\nAnalysis of: %s\n", header);
    printf("Alphabetic Characters: %ld \nTop Digraphs:\n", char_count(graph));

    for_each(graph, n, display_edge);
    return;
}

void display_edge(const char* vertices, long weight)
{
    printf("   %s : %ld\n", vertices, weight);
    return;
}

int run_digraphs(const char* file_name, const char* directory, int n)
{
    int ret_val = 0;
    Digraph* graph = new_digraph();

    // Set up exception handler
    if(catch_exception(standard_exceptions.invalid_argument))
    {
        log_error("Error encountered: exiting");
        ret_val = handle_exception(&standard_exceptions.invalid_argument);
    }
    else
    {
        file_analysis(graph, file_name);
        display_analysis(graph, file_name, n);
    }

    free_digraph(graph);

    return ret_val;
}

void file_analysis(Digraph* graph, const char* file_name)
{
    File_Reader reader = open_file(file_name);
    if(!reader.file)
    {
        throw_exception(&standard_exceptions.invalid_argument, file_name, -1);
    }

    parse_text(graph, reader.contents);
    close_reader(&reader);
    return;
}

