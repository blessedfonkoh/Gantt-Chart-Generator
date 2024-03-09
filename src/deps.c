#include "../include/_data.h"
#include "../include/logging.h"
#include <stdio.h>

static void printDeps(long path[10], int depth);

int checkCircularDeps(Task tasks[10], long taskID, long path[10], int depth)
{

#ifdef DEBUG
    for (size_t i = 0; i < depth; i++)
    {
        printf(" ");
    }
    printDeps(path, depth);
    printf("%ld\n", taskID + 1);
#endif

    // if the current node has already been visited on the current path, then a
    // circular dependency exists
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

    // otherwise, add the current task to the path
    path[depth] = taskID;
    // and explore each of the tasks that it depends on recursively
    for (size_t i = 0; i < tasks[taskID].numDependencies; i++)
    {
        if (checkCircularDeps(tasks, tasks[taskID].dependencies[i], path, depth + 1) == 1)
        {
            return 1;
        }
    }

    return 0;
}

static void printDeps(long path[10], int depth)
{
    for (size_t i = 0; i < depth; i++)
    {
        printf("%ld -> ", path[i] + 1);
    }
}