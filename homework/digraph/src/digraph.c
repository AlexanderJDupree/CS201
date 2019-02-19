/*
 * File: digraph.c
 *
 * Brief: Implementation file for digraphs object. Defines public digraph
 *        methods and static private subroutines the digraph uses.
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "digraph.h"
#include "exceptions.h"

static const int MAX_EDGES = 2704;
static const int ALPHABETIC_CHARACTERS = 52;
static const char* ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

typedef struct Edge
{
    long weight;
    char vertices[3];
} Edge;

struct Digraph_Class
{
    Edge* edge_list;
    long char_count;
    long weight_sum;
};

/*******************************************************************************
 * Static/Private Edge functions
 ******************************************************************************/

static Edge construct_edge(int weight, char origin, char dest)
{
    Edge new_edge = { .weight = weight, 
                      .vertices[0] = origin, 
                      .vertices[1] = dest, 
                      .vertices[2] = '\0' };
    return new_edge;
}

static Edge* construct_edge_list()
{
    int edges = MAX_EDGES;

    Edge* edge_list = (Edge*) malloc(sizeof(Edge) * edges);

    if(edge_list == NULL)
    {
        throw_exception(&standard_exceptions.bad_alloc, "construct_edge_list()", -1);
    }

    for (int i = ALPHABETIC_CHARACTERS - 1; i >= 0; --i)
    {
        for(int j = ALPHABETIC_CHARACTERS - 1; j >= 0; --j)
        {
            edge_list[--edges] = construct_edge(0, ALPHABET[i], ALPHABET[j]);
        }
    }
    return edge_list;
}

/*******************************************************************************
 * Static/Private Digraph methods
 ******************************************************************************/

static void throw_if_null(Digraph* self)
{
    if(self == NULL)
    {
        throw_exception(&standard_exceptions.null_ptr, "Digraph* self", -1);
    }
    return;
}

static long char_to_index(char letter)
{
    return (letter >= 'A' && letter <= 'Z') ? letter - 'A' :
           (letter >= 'a' && letter <= 'z') ? letter - 'a' + 26 : -1;
}

static long convert_to_index(char origin, char dest)
{
/* The edge list is ordered like a 2-d array. origin is the row and dest is the
 column. To get the right index we map the Alphabetic characters from 0 - 51 
 where 0 is 'A' and 51 is 'z'. Then we multiply the row by 52 and add the 
 column */

    long index = char_to_index(origin) 
               * ALPHABETIC_CHARACTERS 
               + char_to_index(dest);

    if(index < 0)
    {
        throw_exception(&standard_exceptions.out_of_range, 
                        "convert_to_index() failed", -1);
    }

    return index;
}

static int compare_weight_descending(Edge* lhs, Edge* rhs)
{
    return lhs->weight > rhs->weight;
}

static void swap(Edge** lhs, Edge** rhs)
{
    Edge* temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
    return;
}

static int partition(Edge** list, int left, int right, 
                     int (*comparator)(Edge* lhs, Edge* rhs))
{
/* Partition is the workhorse for the quick sort algorithm. We select an 
   arbitrary element as pivot and arrange the list around the pivot */

    Edge* pivot = list[right];

    int i = left - 1;
    
    for (int j = left; j <= right - 1; ++j)
    {
        // if comparator succeeds we switch pivot with i
        if (comparator(list[j], pivot))
        {
            swap(list + j, list + (++i));
        }
    }
    // swap pivot to the correct index in the list
    swap(list + (++i), list + right);
    return i;
}

static void quick_sort(Edge** list, int left, int right,
                       int (*comparator)(Edge* lhs, Edge* rhs))
{
    // Base case
    if (left >= right) 
    { 
        return; 
    }

    int part = partition(list, left, right, comparator);

    // Quick sort left partition
    quick_sort(list, left, part - 1, comparator);

    // Quick sort right partition
    quick_sort(list, part + 1, right, comparator);

    return;
}

/*******************************************************************************
 * Public Digraph methods
 ******************************************************************************/

Digraph* new_digraph()
{
    Digraph* new_graph = (Digraph*) malloc(sizeof(Digraph));

    if(new_graph == NULL)
    {
        throw_exception(&standard_exceptions.bad_alloc, "new_digraph()", -1);
    }

    new_graph->weight_sum = 0;
    new_graph->char_count = 0;
    new_graph->edge_list = construct_edge_list();

    return new_graph;
}

Digraph* construct_graph(const char* text)
{
    Digraph* new_graph = new_digraph();

    parse_text(new_graph, text);

    return new_graph;
}

void free_digraph(Digraph** self)
{
    if(self && *self)
    {
        (*self)->weight_sum = 0;
        (*self)->char_count = 0;
        free((*self)->edge_list);
        free((*self));
        *self = NULL;
    }
}

void clear_graph(Digraph* self)
{
    throw_if_null(self);

    // checks if graph is already empty
    if(self->weight_sum > 0)
    {
        for (int i = 0; i < MAX_EDGES; ++i)
        {
            self->edge_list[i].weight = 0;
        }
        self->weight_sum = 0;
        self->char_count = 0;
    }
}

int parse_text(Digraph* self, const char* text)
{
    throw_if_null(self);

    int char_count = 0;
    if(text)
    {
        int length = strlen(text);
        for (int i = 0; i < length - 1; ++i)
        {
            if(isalpha(text[i])) // TODO refactor
            {
                ++char_count;
            }
            if(isalpha(text[i]) && isalpha(text[i + 1]))
            {
                add_edge(self, text[i], text[i + 1]);
            }
        }
    }
    self->char_count += char_count;
    return char_count;
}

long graph_size(Digraph* self)
{
    throw_if_null(self);
    return self->weight_sum;
}

long char_count(Digraph* self)
{
    throw_if_null(self);
    return self->char_count;
}

long get_edge(Digraph* self, char origin, char dest)
{
    throw_if_null(self);
    if(catch_exception(standard_exceptions.out_of_range))
    {
        return handle_exception(&standard_exceptions.out_of_range);
    }
    return self->edge_list[convert_to_index(origin, dest)].weight;
}

long add_edge(Digraph* self, char origin, char dest)
{
    throw_if_null(self);
    if(catch_exception(standard_exceptions.out_of_range))
    {
        // Add failed, reduce to size to original state
        --(self->weight_sum);
        return handle_exception(&standard_exceptions.out_of_range);
    }
    ++(self->weight_sum);
    return self->edge_list[convert_to_index(origin, dest)].weight += 1;
}

void for_each(Digraph* self, int n, void(*func)(const char* vertices, long weight))
{
    throw_if_null(self);

    // Create a temporary list of pointers to actual data
    Edge* temp_list[MAX_EDGES];
    for (int i = 0; i < MAX_EDGES; ++i)
    {
        temp_list[i] = self->edge_list + i;
    }

    quick_sort(temp_list, 0, MAX_EDGES - 1, compare_weight_descending);

    // Perform functor on top N digraphs
    for (int i = 0; i < MAX_EDGES && i < n; ++i)
    {
        func(temp_list[i]->vertices, temp_list[i]->weight);
    }
    return;
}

int max_edges()
{
    return MAX_EDGES;
}

