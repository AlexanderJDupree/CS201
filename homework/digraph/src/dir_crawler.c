/*
 * File: dir_crawler.c
 *
 * Brief: 
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */

#include <dirent.h>
#include <stdlib.h>
#include "dir_crawler.h"

struct Dir_Crawler_Class
{
    DIR* root_dir;
    struct dirent* entry;
};

Dir_Crawler* open_dir(const char* directory)
{
    DIR* root_dir = opendir(directory);
    if(!root_dir)
    {
        return NULL;
    }

    Dir_Crawler* new_crawler = (Dir_Crawler*) malloc(sizeof(Dir_Crawler));
    new_crawler->entry = readdir(root_dir);
    new_crawler->root_dir = root_dir;

    return new_crawler;
}

const char* root_dir(Dir_Crawler* self)
{
    return self->entry->d_name;
}

