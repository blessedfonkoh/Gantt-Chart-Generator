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

// gets data about a task from the user. mode 'a' for add and 'e' for edit
void getTask(Task *task, char mode);

// deep copies one task into another
void taskCopy(Task *dest, Task *src);

// outputs the gantt to the terminal
void displayGantt(Task tasks[10], int num_tasks);

// sqfely gets integer input from the user without using scanf
int getNum(long *dest);

// asks the user which task they want to edit, makes sure that task exists, and
// then updates the details of that task
void editTask(Task tasks[10]);

// asks the user what command they want to perform on the gantt
// returns:
// 'q' for quitting the program
// 'e' for editting the gantt
// 't' for testing circular dependencies 
char menu();

#endif
