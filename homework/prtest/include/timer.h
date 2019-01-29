/*
 * File: timer.h
 *
 * Brief:
 *
 * Author: Alexander DuPree
 *
 * Date: 24JAN2019
 *
 */

#ifndef TIMER_H
#define TIMER_H

typedef double (*Converter)(double seconds);

enum time_units
{
    SECONDS,
    MILLISECONDS,
    MICROSECONDS
};

struct Timer;

// Constructor returns a new malloc'ed Timer. Caller is responsible for deallocation
struct Timer* construct_timer();

/* Functions without a Timer* parameter use the GLOBAL_TIMER */

// Returns 1 on success, 0 for failure.
int timer_start();
int start(struct Timer* timer);

// Returns 1 on success, 0 for failure.
int timer_stop();
int stop(struct Timer* timer);

// Returns elapsed time in ms.
long elapsed_time(enum time_units);
long get_elapsed_time(struct Timer*, enum time_units);

/****** UNIT CONVERSIONS ******/

// s = seconds, ms = milliseconds, us = microseconds
double stoms(double seconds);
double stous(double seconds);
double stos(double seconds);

// double is used to preserve the precision through the conversion
double ustos(double microseconds);
double mstos(double milliseconds);

Converter get_conversion(enum time_units desired_units);

#endif  // TIMER_H

