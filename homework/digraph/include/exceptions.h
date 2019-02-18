/*
 * File: exceptions.h
 *
 * Brief: exceptions is a very experimental attempt at implementing C++ style
 *        exception handling (try catch throw). This utility is in the earliest
 *        stages of developement is meant as an education opportunity for myself
 *
 * Author: Alexander DuPree
 *
 * Date: 2/4/2019
 */

/* http://www.open-std.org/jtc1/sc22/wg14/www/C99RationaleV5.10.pdf
   See section 7.13.2 to get a further understanding of the longjmp function
   Specifally, DO NOT throw_exception in an exit handling function */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// Compile with '-D LOG_ERRORS' to enable error logging
#ifndef LOG_ERRORS
#define LOG_ERRORS 0
#endif

#include <setjmp.h> // setjmp, longjmp, jmp_buf

typedef struct
{
    const char* usr_msg;
    const char* what;
    int ret_val;
    jmp_buf env;
} Exception;

/* Some standard global exceptions to use in a program. To create a custom 
   exception just create a new struct with different exception attributes */
struct Standard_Exceptions
{
    int error_flag;
    Exception out_of_range;
    Exception invalid_argument;
    Exception null_ptr;
    Exception bad_alloc;
    Exception logic_error;

} extern standard_exceptions;

/* setjmp() must be called in a valid stack frame so long jump can successfully 
   jump up the stack. The only solution I can think of for this to occur is by
   using macros. This macro extends the catch_exception() function to first 
   check if the exception is valid, then set the jump environment for a throw
   call later */
#define catch_exception(x) (try_exception(&x) && setjmp(x.env))

int try_exception(Exception* exception);

/* throwing an exception without a catch_exception call on the call stack will
   cause a segfault. TODO figure out how to print an unhandled exception message
   if a thrown exception is not caught */
void throw_exception(Exception* exception, const char* msg, int ret_val);

/* if LOG_ERROR is defined, then usr_msg and what will be printed. Else
   returns ret_val */
int handle_exception(Exception* exception);

void log_error(const char* err);

void log_exception(Exception* exception);

#endif // EXCEPTIONS_H

