#ifndef DATA_H
#define DATA_H

typedef struct task
{
    char name[80];
    int startMonth;
    int endMonth;
    int numDependencies;
    int dependencies[9];
} Task;

#endif