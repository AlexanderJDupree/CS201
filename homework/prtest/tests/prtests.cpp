/*
 * File: prtests.cpp
 *
 * Brief: Unit tests for proofreading test application
 *
 * Author: Alexander DuPree
 *
 * Date: 24JAN2019
 *
 */

#define DEBUG 1

#include <string.h>
#include <catch.hpp>

#include "../prtest.c"


TEST_CASE("Determining a file size in bytes")
{
    FILE* test = fopen("test.txt", "r");
    FILE* invalid_file = NULL;

    SECTION("test.txt size")
    {
        REQUIRE(file_size(test) == 22);
    }
    SECTION("Invalid file")
    {
        REQUIRE(file_size(invalid_file) == -1);
    }
}

TEST_CASE("Reading a file into a char buffer")
{
    FILE* test = fopen("test.txt", "r");
    FILE* invalid_file = NULL;

    SECTION("Read a valid file")
    {
        const char* test_contents = "Hello World\nI am Alex\n";

        REQUIRE(strcmp(read_file(test), test_contents)== 0);
    }
    SECTION("Read invalid file")
    {
        REQUIRE(read_file(invalid_file) == NULL);
    }
}

TEST_CASE("Generate a random english character")
{
    const char MIN = 'a';
    const char MAX = 'z';

    const char test = random_char();
    bool assertion = test >= MIN && test <= MAX;

    REQUIRE(assertion);
}


