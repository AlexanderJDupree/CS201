/*
 * File: file_reader.h
 *
 * Brief: Simple file reader utility that provides an easy and intuitive way to 
 *        load a file's contents into memory. 
 *
 * Author: Alexander DuPree
 *
 * https://github.com/AlexanderJDupree/File_Reader
 */

#ifndef FILE_READER_H
#define FILE_READER_H

#include <stddef.h>
#include <stdio.h>

typedef struct
{
    FILE* file;
    size_t size;
    const char* contents;
} File_Reader;

File_Reader open_file(const char* file_name);

void close_reader(File_Reader* reader);

const char* read_file(File_Reader* reader);

size_t file_size(FILE* file);

#endif

