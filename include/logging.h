#ifndef LOGGING_H
#define LOGGING_H

// logs a message to the terminal
// mode:
// 's' for a success message
// 'i' for an info message
// 'w' for a warning message
// 'e' for an error message
void printLog(char mode, char *fmt, ...);

// prints text to the terminal in color
// the first argument must be 1-256, representing the 256 standard colors
// listed in the ANSI escape sequence specifications
void cprintf(int color, char *fmt, ...);
#endif
