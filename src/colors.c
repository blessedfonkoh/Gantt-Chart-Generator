#include <time.h>
#include <stdlib.h>

#include "../include/colors.h"

// returns a different color from a palette of 10 colors each time it is called
// if 10 colors have already been allotted, returns -1
int palette()
{
    // static variables are used because this is state that has to persist 
    // between calls of the function, i.e. the function has to "remember" which
    // colors have been used already
    // static variables are always automatically initialised to zero
    static int chosen[10];
    static int used;

    // if all ten colors have been used already, return an error
    if (used > 9)
    {
        return -1;
    }

    const Color colors[10] = {teal, blue, violet, pink, gold, purple, yellow, crimson, lavender, mint};
    srand(time(NULL));

    // choose a color that has not been used
    // the chosen array contains flags that indicate whether a color has been
    // used already
    int choice;
    do
    {
        choice = rand() % 10;
    } while(chosen[choice] == 1);

    chosen[choice] = 1;
    used++;

    return colors[choice];
}
