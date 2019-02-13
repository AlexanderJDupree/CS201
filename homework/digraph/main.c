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
#include <string.h>
#include <dirent.h>
#include <inttypes.h>
#include "digraph.h"
#include "exceptions.h"
#include "file_reader.h"

void usage();
void display_analysis(Digraph* graph, const char* header, int n);
void display_edge(const char* vertices, long weight);

void file_analysis(Digraph* graph, const char* file_name);
void directory_analysis(Digraph* graph, const char* directory);
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
            case 'c' : count = strtoumax(optarg, NULL, 0);
            default  : break;
        }
    }
    // Set up exception handler
    if(catch_exception(standard_exceptions.invalid_argument))
    {
        log_error("Error encountered: exiting");
        exit_status = handle_exception(&standard_exceptions.invalid_argument);
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
    printf("Analysis of: %s\n"
           "Alphabetic Characters: %ld\n"
           "Top %d Digraphs:\n", 
           header, char_count(graph), n);

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

    if(!file_name && !directory)
    {
        usage();
        ret_val = -1;
    }
    if(file_name)
    {
        file_analysis(graph, file_name);
        display_analysis(graph, file_name, n);
    }
    if(directory)
    {
        clear_graph(graph);
        directory_analysis(graph, directory);
        display_analysis(graph, directory, n);
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

void directory_analysis(Digraph* graph, const char* directory)
{
    struct dirent* entry = NULL;
    DIR* dir = opendir(directory);

    if (dir == NULL)
    {
        //throw_exception(&standard_exceptions.invalid_argument, directory, -1);
        return;
    }

    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            parse_text(graph, entry->d_name);
            if(entry->d_type & DT_DIR)
            {
                char path[1024]; // TODO dynamic array, so we can have handle arbitrarly length paths
                snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
                // TODO check if %s/%s works on windows systems
                
                // Recursively travel the file system
                directory_analysis(graph, path);
            }
        }
    }
    return;
}

/*
void directory_analysis(Digraph* graph, const char* directory)
{
    Dir_Crawler* crawler = open_dir(directory);

    if(!crawler)
    {
        throw_exception(&standard_exceptions.invalid_argument, directory, -1);
    }

    while(has_next(crawler))
    {
        parse_text(graph, get_next(crawler));
    }
    
    // Free/destroy crawler?
    return;
}
*/

