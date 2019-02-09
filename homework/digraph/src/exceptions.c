/*
 * File: exceptions.c
 *
 * Brief: 
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */


#include <stdio.h> // fprintf
#include "exceptions.h"

int try_exception(Exception* exception)
{
    if(LOG_ERRORS && exception == NULL)
    {
        standard_exceptions.error_flag = 1;
        log_error("Failed to try/catch exception. Exception pointer is NULL");
    }
    return exception != NULL;
}

int handle_exception(Exception* exception)
{
    if(LOG_ERRORS)
    {
        log_exception(exception);
    }
    return exception->ret_val;
}

void throw_exception(Exception* exception, const char* msg, int ret_val)
{
    if(msg != NULL)
    {
        exception->usr_msg = msg;
    }
    exception->ret_val = ret_val;
    longjmp(exception->env, 1);
}

void log_error(const char* err)
{
    fprintf(stderr, "%s\n", err);
}

void log_exception(Exception* exception)
{
    fprintf(stderr, "%s: %s\n", exception->usr_msg, exception->what);
}

