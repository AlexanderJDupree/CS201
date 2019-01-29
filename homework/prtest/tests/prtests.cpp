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

#define UNIT_TESTS 1

#include <catch.hpp>

#include "timer.h"
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

TEST_CASE("Generating random integers")
{
    SECTION("Invalid range")
    {
        REQUIRE(random_int(1, 0) == 0);
    }
}

TEST_CASE("Generate a random english character")
{
    const char MIN = 'a';
    const char MAX = 'z';

    const char test = random_int('a', 'z');
    bool assertion = test >= MIN && test <= MAX;

    REQUIRE(assertion);
}

TEST_CASE("Using timer to record elapsed time")
{
    SECTION("Constructing a new timer")
    {
        Timer* timer = construct_timer();

        REQUIRE(elapsed_time(timer) == 0);

        free(timer);
    }
    SECTION("Start and stop return true")
    {
        REQUIRE(timer_start());
        REQUIRE(timer_stop());
    }
}

TEST_CASE("Converting time units")
{
    SECTION("seconds to ms")
    {
        REQUIRE(stoms(1) == 1000);
    }
    SECTION("seconds to microseconds")
    {
        REQUIRE(stous(1) == 1000000);
    }
    SECTION("microseconds to seconds")
    {
        REQUIRE(ustos(1000000) == 1);
    }
    SECTION("ms to seconds")
    {
        REQUIRE(mstos(1000) == 1);
    }
}

