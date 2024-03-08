// include guards:
// prevent the content of the header file from being included multiple times
// in the binary.
// the first time this header file is #included somewhere, the symbolic
// constant DATA_H will be defined (no value, just defined)
// on subsequent #includes, since DATA_H will already be defined, the
// #ifndef will make sure that none of this code is included again
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


enum month
{
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december,
    dependencies
}; // {0,1,2,3,4,5,6,7,8,9,10,11}

#endif