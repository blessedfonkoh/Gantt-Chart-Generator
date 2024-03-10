#include <time.h>
#include <stdlib.h>

#include "../include/colors.h"


int palette()
{
    static int chosen[10];
    const Color colors[10] = {teal, blue, violet, pink, gold, purple, yellow, crimson, lavender, mint};
    srand(time(NULL));

    int choice;
    do
    {
        choice = rand() % 10;
    } while(chosen[choice] == 1);
    chosen[choice] = 1;

    return colors[choice];
}
