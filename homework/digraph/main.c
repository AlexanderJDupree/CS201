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
#include "digraph.h"
#include "exceptions.h"

void usage();
void display_edge(const char* vertices, long weight);

// Hides main from the unit tests build
#ifndef UNIT_TESTS
int main()
{
    if(catch_exception(standard_exceptions.bad_alloc))
    {
        return handle_exception(&standard_exceptions.bad_alloc);
    }

    return 0;
}
#endif

void usage()
{
    fprintf(stderr, "prtest: usage: prtest [<path to file>]\n");
    return;
}

void display_edge(const char* vertices, long weight)
{
    printf("   %s : %ld\n", vertices, weight);
    return;
}

