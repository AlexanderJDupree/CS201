/*
 * File: file_reader.h
 *
 * Brief:
 *
 * Author: Alexander DuPree
 *
 * Date: 24JAN2019
 *
 */

#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>

struct File_Reader
{
    int size;
    FILE* file;
    const char* contents;
};

struct File_Reader* open_file(const char* file_name);
void close_reader(struct File_Reader* reader);

const char* read_file(struct File_Reader* reader);

long file_size(FILE* file);

#endif


