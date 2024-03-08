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

void getTask(Task *task);

void taskCopy(Task *dest, Task *src);

void displayGantt(Task tasks[10], int num_tasks);
long getNum();

void editTask(Task *task);

void displayGant(struct task tasks[], int num_tasks);

#endif