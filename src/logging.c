#include <stdio.h>
#include <stdarg.h>

/*This module provides wrappers around printf to print info messages to users
with colored accents.*/

// ANSI Escape Sequences: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

void printLog(char mode, char *fmt, ...)
{
    va_list args;
    // tell C that the variable arguments start from fmt, the rightmost named
    // argument
    va_start(args, fmt);

    // print the message

    switch (mode)
    {
    // WARN
    case 'w':
        // the \e[38;5;214m is the ANSI escape sequence for foreground color
        // basically, it tells the terminal emulator to start displaying text
        // with color 214 (i.e. orange) as the font color
        // \e[0m resets the terminal to the original font colors
        printf("\n\e[38;5;214mWARNING:\e[0m ");
        break;
    // INFO
    case 'i':
        // color 75 is light blue
        printf("\n\e[38;5;75mINFO:\e[0m ");
    // SUCCESS
    case 's':
        printf("\n\e[38;5;34mSUCCESS:\e[0m ");
    }

    // vprintf is a function in the printf family which, instead of taking a
    // variable number of arguments in the function call, accepts a va_list
    // of arguments instead
    vprintf(fmt, args);

    // tell C that we're done reading the variable arguments
    va_end(args);
}