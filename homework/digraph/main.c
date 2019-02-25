/*
 * File: main.c
 *
 * Brief: main.c is the entry point for the digraphs application. mains 
 *        responsibility is to parse the command line arguments and dispatch the
 *        args towards the correct functions. run_digraphs conducts the
 *        appropriate digraph analysis and dispalys the results of this analysis
 *
 *        Note: directory_analysis will ignore symlinks and permission protected
 *              directories
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
#include <unistd.h>
#include <inttypes.h>

#include "digraph.h"
#include "exceptions.h"
#include "file_reader.h"

void usage();

// Diplays top N digraphs
void display_analysis(Digraph* graph, const char* header, int n);
void display_edge(const char* vertices, long weight);

// Uses file_reader utility to load a file into memory and run digraph analysis
void file_analysis(Digraph* graph, const char* file_name);

// Recursively travels the indicated directory parsing each directory entry
void directory_analysis(Digraph* graph, const char* directory);

// Runs the appropriate digraph analysis, returns 0 on success, -1 on any error
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
    if(!file_name && !directory)
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
#endif // UNIT_TESTS

void usage()
{
    fprintf(stderr, "usage:\n  digraphs <options>\nOptions:\n  "
            "-h or -?\t\tDisplays usage info\n  "
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
    Digraph* graph = new_digraph();

    // Set up exception handler
    if(catch_exception(standard_exceptions.invalid_argument))
    {
        free_digraph(&graph);
        log_error("Error encountered: exiting");
        return handle_exception(&standard_exceptions.invalid_argument);
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
    free_digraph(&graph);

    return 0;
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
    // TODO package all this logic into a reusable utility file
    struct dirent* entry = NULL;
    DIR* dir = opendir(directory);

    if (dir == NULL || chdir(directory) != 0)
    {
        return;
    }

    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            parse_text(graph, entry->d_name);
            if(entry->d_type == DT_DIR)
            {
                // Recursively travel the file system
                directory_analysis(graph, entry->d_name);
            }
        }
    }

    closedir(dir);
    chdir("..");
    return;
}

