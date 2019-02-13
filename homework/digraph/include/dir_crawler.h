/*
 * File: dir_crawler.h
 *
 * Brief: 
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */

#ifndef DIR_CRAWLER_H
#define DIR_CRAWLER_H

typedef struct Dir_Crawler_Class Dir_Crawler;

Dir_Crawler* open_dir(const char* directory);

int has_next(Dir_Crawler* self);

const char* get_next(Dir_Crawler* self);

const char* root_dir(Dir_Crawler* self);

#endif // DIR_CRAWLER_H

