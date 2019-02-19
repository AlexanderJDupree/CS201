/*
 * File: digraph.h
 *
 * Brief: Digraphs parses_text as a const char* to add weights to the 
 *        corresponding digraphs. For example, if "aaabc" was passed to the 
 *        parse_text function the resulting digraphs would be:
 *
 *              aa : 2
 *              ab : 1
 *              bc : 1
 *
 *        The for_each function allows the client to read and perform analysis
 *        on the digraphs data.
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */

#ifndef DIGRAPH_H
#define DIGRAPH_H

typedef struct Digraph_Class Digraph;

// Constructs empty digraph
Digraph* new_digraph();

// Constructs digraph with text parsed into the correct edges
Digraph* construct_graph(const char* text);

// MUST be called to prevent memory leaks. Sets callers pointer to NULL
void free_digraph(Digraph** self);

// Resets all weights and associated values to 0
void clear_graph(Digraph* self);

// Returns the sum of all weights on the graph
long graph_size(Digraph* self);

// Returns the number of alphabetic character in the most recent text parse
long char_count(Digraph* self);

// Returns the weight of the corresponding edge, else -1
long get_edge(Digraph* self, char origin, char dest);

// Increments the weight of the corresponding edge, returns edges new value
long add_edge(Digraph* self, char origin, char dest);

// Parses text into digraph, returns 1 on success, 0 for failure
int parse_text(Digraph* self, const char* text);

// Performs functor on 'n' edges from the graphs from heaviest weights to least
void for_each(Digraph* self, int n, void (*func)(const char* vertices, long weight));

// Returns the maximum possible edges
int max_edges();

#endif // DIGRAPH_H
