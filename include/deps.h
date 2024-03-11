#ifndef DEPS_H
#define DEPS_H

#include "_data.h"

// tests a gantt for circular dependencies, starting at task taskID
// when calling this function from your program, pass in an empty array
// of length 10 for path, and pass in 0 for depth
int checkCircularDeps(Task gantt[10], long taskID, long path[10], int depth);

#endif
