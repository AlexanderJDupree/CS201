/*
 * File: digraph.h
 *
 * Brief: 
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */

#ifndef DIGRAPH_H
#define DIGRAPH_H

typedef struct Digraph_Class Digraph;

/* Constructors */

// Constructs empty digraph
Digraph* new_digraph();

// Constructs digraph with text parsed into the correct edges
Digraph* construct_graph(const char* text);

/* Destructors */

// MUST be called before program exit to prevent memory leaks
void free_digraph(Digraph* self);

void clear_graph(Digraph* self);

/* Member Functions */
// Returns the sum of all weights on the graph
long graph_size(Digraph* self);

// Returns the number of alphabetic character in the most recent text parse
long char_count(Digraph* self);

// Returns the weight of the corresponding edge, else -1
long get_edge(Digraph* self, char origin, char dest);

// Increments the weight of the corresponding edge, returns edges new value
long add_edge(Digraph* self, char origin, char dest);

// Parses text into digraph, returns 1 on success, 0 for failure
void parse_text(Digraph* self, const char* text);

// Performs functor on 'n' edges from the graphs from heaviest weights to least
void for_each(Digraph* self, int n, void (*func)(const char* vertices, long weight));

// Returns the maximum possible edges
int max_edges();

//DEBUG
void display_all(Digraph* self);

#endif // DIGRAPH_H
