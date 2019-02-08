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
void display_edge(const char* vertices, long weight);

int run_digraphs(const char* file_name, const char* directory);
int run_analysis(const char* text);

// Hides main from the unit tests build
#ifndef UNIT_TESTS
int main(int argc, char** argv)
{
    int opt = 0;
    int exit_status = 0;
    const char* file_name = NULL;
    const char* directory = NULL;

    while((opt = getopt(argc, argv, "h?t:p:")) != -1)
    {
        switch(opt)
        {
            case 't' : file_name = optarg;
                       break;
            case 'p' : directory = optarg;
                       break;
            default  : exit_status = -1;
                       break;
        }
    }
    if(exit_status == -1 || argc == 1)
    {
        usage();
    }
    else
    {
        exit_status = run_digraphs(file_name, directory);
    }

    return exit_status;
}
#endif

void usage()
{
    fprintf(stderr, "usage:\n  digraphs <options>\nOptions:\n  -t "
                    "<path to file>\n  -p <directory>\n");
    return;
}

void display_edge(const char* vertices, long weight)
{
    printf("   %s : %ld\n", vertices, weight);
    return;
}

int run_digraphs(const char* file_name, const char* directory)
{
    int ret_val = 0;
    if(file_name)
    {
        File_Reader* reader = open_file(file_name);
        if(reader && reader->contents)
        {
            ret_val = run_analysis(reader->contents);
        }
        else
        {
            // TODO throw/log error
            ret_val = -1;
        }
        close_reader(reader);
    }
    if(directory)
    {
        ret_val = 0;
    }
    return ret_val;
}

int run_analysis(const char* text)
{
    if(catch_exception(standard_exceptions.bad_alloc))
    {
        return handle_exception(&standard_exceptions.bad_alloc);
    }

    Digraph* graph = construct_graph(text);

    printf("Alphbetic Characters: %ld \nTop Digraphs:\n", char_count(graph));

    // TODO 10 is a magic number, make a var the user can set
    for_each(graph, display_edge, 10);

    free_digraph(graph);

    return 0;
}

