#ifndef LOGGING_H
#define LOGGING_H

// issue a warning to the user
// a warning is used to alert the user to a failing condition that they must
// resolve
void warn(char *fmt, ...);

// give the user some information
// used for non-critical scenarios
void info(char *fmt, ...);

#endif