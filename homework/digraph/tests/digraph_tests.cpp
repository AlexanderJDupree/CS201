/*
 * File: digraph_tests.cpp
 *
 * Brief: Unit tests for digraph
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 *
 */

#define UNIT_TESTS 1

#include <catch.hpp>

extern "C" {
    #include "digraph.h"
}


TEST_CASE("Constructing a digraph")
{
    Digraph* graph = new_digraph();

    REQUIRE(graph != NULL);

    free_digraph(graph);
}


TEST_CASE("Adding/retrieiving edges")
{
    Digraph* graph = new_digraph();

    SECTION("empty Digraph")
    {
        REQUIRE(get_edge(graph, 'a', 'c') == 0);
    }
    SECTION("Invalid characters/indices return -1")
    {
        REQUIRE(get_edge(graph, '?', '{') == -1);
        REQUIRE(get_edge(graph, 53, '<') == -1);
    }
    SECTION("add edge")
    {
        REQUIRE(add_edge(graph, 'a', 'c') == 1);
    }
    SECTION("Adding an invalid edge returns -1")
    {
        REQUIRE(add_edge(graph, '?', '{') == -1);
    }
    SECTION("adding an edge multiple times increases the weight")
    {
        for (int i = 1; i <= 3; ++i)
        {
            REQUIRE(add_edge(graph, 'Z', 'Z') == i);
        }
    }
    free_digraph(graph);
}

TEST_CASE("Get the size of the graph (sum of all weights)")
{
    const char* test_text = "ZZadZZadZZbaZZad";

    Digraph* graph = construct_graph(test_text);
    Digraph* empty_graph = new_digraph();

    SECTION("A populated graph")
    {
        REQUIRE(graph_size(graph) == 15);
    }
    SECTION("Empty graph")
    {
        REQUIRE(graph_size(empty_graph) == 0);
    }

    free_digraph(graph);
    free_digraph(empty_graph);
}

