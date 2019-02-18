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

#include <catch.hpp>

extern "C" {
    #include "digraph.h"
    #include "exceptions.h"
}


TEST_CASE("Constructing a digraph", "[digraph]")
{
    Digraph* graph = new_digraph();

    REQUIRE(graph != NULL);

    free_digraph(&graph);
}


TEST_CASE("Adding/retrieiving edges", "[digraph]")
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
    free_digraph(&graph);
}

TEST_CASE("Get the size of the graph (sum of all weights)", "[digraph]")
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

    free_digraph(&graph);
    free_digraph(&empty_graph);
}

void assert_empty_edge(const char* vertices, long weight)
{
    REQUIRE(vertices != NULL);
    REQUIRE(weight == 0);
}

TEST_CASE("Clearing a digraph", "[digraph]")
{
    const char* test_text = "ZZadZZadZZbaZZad";

    Digraph* graph = construct_graph(test_text);
    Digraph* empty_graph = new_digraph();

    clear_graph(graph);
    clear_graph(empty_graph);

    SECTION("Char count is 0")
    {
        REQUIRE(char_count(graph) == 0);
    }
    SECTION("Size is 0")
    {
        REQUIRE(graph_size(graph) == 0);
    }
    SECTION("The weight of every edge is 0")
    {
        for_each(graph, max_edges(), assert_empty_edge);
    }

    free_digraph(&graph);
    free_digraph(&empty_graph);
}

TEST_CASE("Free digraphs from memory", "[digraph]")
{
    
    // Essentially these tests pass if there is no segfault

    SECTION("Normal operation")
    {
        const char* test_text = "ZZadZZadZZbaZZad";

        Digraph* graph = construct_graph(test_text);

        free_digraph(&graph);
        REQUIRE(graph == NULL);
    }
    SECTION("Double free")
    {
        const char* test_text = "ZZadZZadZZbaZZad";

        Digraph* graph = construct_graph(test_text);

        free_digraph(&graph);
        free_digraph(&graph);

        REQUIRE(graph == NULL);
    }
    SECTION("For each after free")
    {
        if(catch_exception(standard_exceptions.null_ptr))
        {
            REQUIRE(handle_exception(&standard_exceptions.null_ptr) == -1);
        }
        else
        {
            Digraph* empty_graph = new_digraph();

            free_digraph(&empty_graph);

            for_each(empty_graph, max_edges(), assert_empty_edge);
        }
    }
}

