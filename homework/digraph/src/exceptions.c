/*
 * File: exceptions.c
 *
 * Brief: Implementation file for the exceptions utlity. Defines global standard
 *        exceptions and the exceptions public interface
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */

#include <stdio.h> // fprintf
#include "exceptions.h"

struct Standard_Exceptions standard_exceptions = {
    .out_of_range = {
        .what = "out of range, check indices",
    },
    .invalid_argument = {
        .what = "Argument(s) is invalid",
    },
    .null_ptr = {
        .what = "Pointer is NULL",
    },
    .bad_alloc = {
        .what = "Error, failed to allocate memory",
    },
    .logic_error = {
        .what = "Logic error occured",
    }
};

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

