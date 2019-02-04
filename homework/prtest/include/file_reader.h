/*
 * File: file_reader.h
 *
 * Brief: Simple file reader utility that provides an easy and intuitive way to 
 *        load a file's contents into memory. 
 *
 * Author: Alexander DuPree
 *
 * https://github.com/AlexanderJDupree/File_Reader
 *
 */

#ifndef FILE_READER_H
#define FILE_READER_H

#include <stddef.h>
#include <stdio.h>

struct File_Reader
{
    size_t size;
    FILE* file;
    const char* contents;
};

struct File_Reader* open_file(const char* file_name);

void close_reader(struct File_Reader* reader);

const char* read_file(struct File_Reader* reader);

size_t file_size(FILE* file);

#endif

