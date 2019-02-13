/*
 * File: dir_crawler_tests.cpp
 *
 * Brief: Unit tests for directory crawler
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 *
 */

#define UNIT_TESTS 1

#include <string>
#include <catch.hpp>

extern "C" {
    #include "dir_crawler.h"
}

TEST_CASE("Opening a directory crawler", "[dir_crawler]")
{
    Dir_Crawler* crawler = open_dir(".");

    SECTION("valid directory")
    {
        REQUIRE(std::string(root_dir(crawler)) == ".");
    }
}


