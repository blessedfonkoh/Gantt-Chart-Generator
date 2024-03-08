// include guards:
// prevent the content of the header file from being included multiple times
// in the binary.
// the first time this header file is #included somewhere, the symbolic
// constant DATA_H will be defined (no value, just defined)
// on subsequent #includes, since DATA_H will already be defined, the
// #ifndef will make sure that none of this code is included again
#ifndef DATA_H
#define DATA_H

// #define DEBUG

typedef struct task
{
    char name[80];
    long startMonth;
    long endMonth;
    long numDependencies;
    long dependencies[9];
} Task;

#endif