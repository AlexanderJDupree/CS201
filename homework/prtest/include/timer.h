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

typedef long (*Converter)(long seconds);

enum time_units
{
    SECONDS,
    MILLISECONDS,
    MICROSECONDS
};

struct Timer;

// Constructor returns a new malloc'ed Timer. Caller is responsible for deallocation
struct Timer* construct_timer();

/* Timer functions without a Timer* parameter use the GLOBAL_TIMER instance */

// Returns 1 on success, 0 for failure.
int timer_start();
int timer_start(struct Timer* timer);

// Returns 1 on success, 0 for failure.
int timer_stop();
int timer_stop(struct Timer* timer);

// Returns elapsed time in ms.
long elapsed_time(enum time_units = MILLISECONDS);
long elapsed_time(struct Timer* timer, enum time_units = MILLISECONDS);

/****** UNIT CONVERSIONS ******/

// s = seconds, ms = milliseconds, us = microseconds
long stoms(long seconds);
long stous(long seconds);
long stos(long seconds);

// double is used to preserve the precision through the conversion
double ustos(double microseconds);
double mstos(double milliseconds);

Converter get_conversion(enum time_units desired_units);

#endif  // TIMER_H

