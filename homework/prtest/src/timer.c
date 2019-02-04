/*
 * File: timer.c
 *
 * Author: Alexander DuPree
 *
 * Date: 24JAN2019
 *
 */

#include <stdlib.h>
#include <sys/time.h>

#include "timer.h"

struct Timer
{
    struct timeval start, stop;
} GLOBAL_TIMER;

struct Timer* construct_timer()
{
    struct Timer* new_timer = (struct Timer*) malloc(sizeof(struct Timer));

    new_timer->start.tv_sec  = 0;
    new_timer->start.tv_usec = 0;
    new_timer->stop.tv_sec   = 0;
    new_timer->stop.tv_usec  = 0;

    return new_timer;
}

int timer_start()
{
    return start(&GLOBAL_TIMER);
}

int start(struct Timer* timer)
{
    return gettimeofday(&(timer->start), NULL) == 0;
}

int timer_stop()
{
    return stop(&GLOBAL_TIMER);
}

int stop(struct Timer* timer)
{
    return gettimeofday(&(timer->stop), NULL) == 0;
}

long elapsed_time(enum time_units desired_units)
{
    return get_elapsed_time(&GLOBAL_TIMER, desired_units);
}

long get_elapsed_time(struct Timer* timer, enum time_units desired_units)
{
    Converter converter = get_conversion(desired_units);

    // Composes the two units into the desired_units
    return converter(timer->stop.tv_sec - timer->start.tv_sec) + 
           converter(ustos((timer->stop.tv_usec - timer->start.tv_usec)));
}

// TODO the unit converstions use "magic" numbers for their conversions. Even 
// though the unit standards will likely never change, look into refactoring 
// the magic numbers into global constants or some sort of define

// s = seconds, ms = milliseconds, us = microseconds
double stoms(double seconds)
{
    return seconds * 1000;
}
double stous(double seconds)
{
    return seconds * 1000000;
}
double stos(double seconds)
{
    return seconds;
}
double ustos(double microseconds)
{
    return microseconds / 1000000;
}
double mstos(double milliseconds)
{
    return milliseconds / 1000;
}

Converter get_conversion(enum time_units desired_units)
{
    switch(desired_units)
    {
        case MILLISECONDS : return stoms;
        case MICROSECONDS : return stous;
        default           : return stos;
    }
}

