# COMP10050 Assignment 2
## Project details
- Group: BG
- Students:
    - Blessed Fonkoh
    - Hari Mohan
- Repo: https://csgitlab.ucd.ie/hari-mohan/bg-assignment-2

## How is the Gantt displayed?
For the Gantt chart output, we decided to stick very closely to the example
shown in the specification document, save for some minor cosmetic changes.
Instead of outputting 'XXX' for each month that a task spanned, we print a
block Unicode character instead to give the appearance of a bar. These bars are
also printed in color.

As for the implementation details, the point to note is the use of enums to
store the month and color data. The months, or more accurately the column
headers, are stored in an enum with values from 1-13 so we can easily iterate
over the range and print the appropriate content for each column. The ANSI
color escape codes are also stored in an enum simply for the purposes of making
the code look cleaner and perhaps a bit-self documenting, as this way, each
color code is associated with a color name from the very beginning.

## How are tasks mapped to a `struct` data structure?
```c
typedef struct task
{
    char name[30];
    long startMonth;
    long endMonth;
    int colorCode;
    long numDependencies;
    long dependencies[9];
} Task;
```

Each attribute of a task is mapped to a separate member of the struct.

## How are tasks edited and changed?
We observed that the userflow for adding and editing a task were almost exactly
the same. The only thing that differed was the prompts that are displayed on
the screen. Therefore, we consolidated the functions for getting input into
one `void getTask(Task *task, char mode)` function and switched on the mode
parameter to decide which prompt to print. `mode` could either be `a` for
adding a new task or `e` for editing an existing task. The other thing that
mode decides is whether a color is allotted to the task. We only want to assign
a color to a task when it is first created, and maintain the same color between
multiple edits.

## How did we search for a circular dependency?

When we say "search for a circular dependency", the underlying problem is that
we want to find cycles in a directed graph. Graphs are inherently a recursive
data structure, so it makes sense that we need to write a recursive function
for this task.

`int checkCircularDeps(Task tasks[10], long taskID, long path[10], int depth)`

We need to follow every path in the dependency graph `Task tasks[10]`, starting
from a certain task `long TaskID` and identify whether they loop back on 
themselves. So clearly, the first thing we need is an array to keep track of 
the path we have traversed so far: `long path[10]`. We also need to keep track
of how long the current path is: `int depth`.

At every call of the function, we need to check if the current task is already
in the path.

```c
for (size_t i = 0; i < depth; i++)
{
    if (path[i] == taskID)
    {
        printLog('w', "Circular dependency found:- ");

        printDeps(path, depth);
        printf("%ld\n\n", taskID + 1);

        return 1;
    }
}
```

If a cycle wasn't found, then we need to go one level deeper, and recurse over
all of the current task's dependencies.

```c
path[depth] = taskID;
// and explore each of the tasks that it depends on recursively
for (size_t i = 0; i < tasks[taskID].numDependencies; i++)
{
    if (checkCircularDeps(tasks, tasks[taskID].dependencies[i], path, depth + 1) == 1)
    {
        return 1;
    }
}
```

We add the current task to the path, increment the depth, and follow the path
down every dependency. If and only if a cycle is found and the function returns
1, we return 1 all the way up the recursive chain. If a cycle is not found, i.e.
if the function returns 0, indicating that a path has terminated without a
cycle occurring, then we do nothing.

## What is our ASCII art about?
It's a rickroll. For obvious reasons.
