#ifndef GANTTIO_H
#define GANTTIO_H

#include "_data.h"

// A wrapper around `fgets` that handles scenarios where users enter more than
// LENGTH characters by clearing `stdin` and asking them to re-enter their
// input.

// Returns `0` once the user has entered a valid input string
// Returns `1` if the user has entered an empty string
int fngets(char *dest, int length);

// Prompts the user for a yes/no answer until they provide a valid repsonse
bool getYesOrNo(void);

void getTask(Task *task, char mode);

void taskCopy(Task *dest, Task *src);

void displayGantt(Task tasks[10], int num_tasks);

int getNum(long *dest);

void editTask(Task tasks[10]);

char menu();

#endif