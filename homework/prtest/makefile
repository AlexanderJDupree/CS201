# File: makefile
# Description: Basic makefile for automated builds
# Author: Alexander DuPree

CC := gcc
CFLAGS := -Wall -g 
INCLUDE := -I tests/third_party/ -I include -I src

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
APPLICATION := prtest.c
TARGET := prtest

TEST_CC := g++
TEST_DIR := tests
TEST_OBJ := tests/obj
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.cpp,$(TEST_OBJ)/%.o,$(TEST_SRCS))
tests := tests/obj/debug/run_tests

TESTS_MAIN := tests/obj/tests_main.o
CATCH2_MAIN := tests/tests_main.cpp

TARGET: $(OBJ_FILES) $(APPLICATION)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $^

tests: $(TEST_OBJS) $(OBJ_FILES) $(TESTS_MAIN)
	$(TEST_CC) $(CFLAGS) $(INCLUDE) -o $(tests) $^

$(TEST_OBJ)/%.o: $(TEST_DIR)/%.cpp $(APPLICATION)
	$(TEST_CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

TESTS_MAIN: $(CATCH2_MAIN)
	$(CC) $(CFLAGS) $(INCLUDE) -c $(THIRD_PARTY) -o $(TESTS_MAIN)

.PHONEY: clean

clean:
	rm -f  $(TARGET)
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TEST_OBJ)/*.o
	rm -f $(tests)
