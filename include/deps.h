#ifndef DEPS_H
#define DEPS_H

#include "_data.h"

int checkCircularDeps(Task tasks[10], long taskID, long path[10], int depth);

#endif