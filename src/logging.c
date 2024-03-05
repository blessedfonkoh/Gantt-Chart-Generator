#include <stdio.h>
#include <stdarg.h>

/*This module provides wrappers around printf to print info messages to users
with colored accents. It uses vprintf to take a variable list of arguments
instead of having a variable number of arguments passed into the function.*/

void warn(char *fmt, ...)
{
    va_list args;
    // tell C that the variable arguments start from fmt, the rightmost named
    // argument
    va_start(args, fmt);

    // print the message
    printf("\n\e[38;5;214mWARNING:\e[0m ");
    vprintf(fmt, args);

    // tell C that we're done reading the variable arguments
    va_end(args);
}

void info(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("\n\e[38;5;75mINFO:\e[0m ");
    vprintf(fmt, args);
    va_end(args);
}