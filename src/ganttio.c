#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/logging.h"
#include "../include/_data.h"
#include "../include/colors.h"

// fngets is essentially a stricter version of fgets, in that it detects if the
// user has entered more characters than expected, clears the stdin buffer, and
// then re-prompts them until they enter a valid input
int fngets(char *dest, int length)
{
    // NOTE: This function is reused from Hari Mohan's assignment 1

    // length + 1 to account for \n character
    char inputBuffer[length + 1]; // string to read input into
    char *lineFeed;               // pointer to newline character

    while (true)
    {
        printf("> ");
        fgets(inputBuffer, length + 1, stdin);

        // strchr is used to search for the location of a character in a string
        // it returns a pointer to the character if it exists, else NULL
        lineFeed = strchr(inputBuffer, '\n');

        // If there isn't a newline in the string, that means that the user
        // has typed in more than the allowed number of characters, and fgets
        // has copied in only part of it.
        if (lineFeed == NULL)
        {
            // Warn the user
            printLog('w', "Your input has exceeded the maximum length of %d. Please try again.\n\n", length - 1);

            // Flush stdin by fgets-ing until we find the newline
            while (!strchr(inputBuffer, '\n'))
            {
                fgets(inputBuffer, length, stdin);
            }
        }
        else
        {
            *lineFeed = '\0'; // remove the newline
            strcpy(dest, inputBuffer);

            // these return status codes are used to detect in the main
            // program if the user wants to cancel an input operation
            if (lineFeed == inputBuffer)
            // i.e. if the user has entered a blank input
            {
                return 1;
            }
            else
            // The user has entered valid input
            {
                return 0;
            }
        }
    }
}

// function modified from https://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
// I emailed Abey and he said it was okay as long as I cited the source
// this function safely obtains integer input from the user, without the risk of
// buffer overflow ocurring (which can happen with scanf)
int getNum(long *dest)
{
    long result;
    // it's a bit disruptive to see WARNING's about input length, so the input
    // buffer is large enough to hold any reasonable number, and error
    // checking is left to strtol
    char inputBuffer[128]; 
    int valid;            // flag for successful conversion

    do
    {
        // does not accept blank input
        while (fngets(inputBuffer, 128) == 1)
        {
            continue;
        }

        char *endptr;

        // errno is an enum variable defined in <errno.h> that contains data
        // about runtime errors in the program so different parts of the code
        // can perform error-handling in a uniform way
        errno = 0; // reset error number

        // strtol converts a string to a long
        result = strtol(inputBuffer, &endptr, 10);

        if (errno == ERANGE)
        {
            // ERANGE signifies that the number in the string is either too big
            // or too small to be stored in a long
            printf("Sorry, this number is too small or too large.\n");
            valid = 0;
        }
        else if (endptr == inputBuffer)
        {
            // no character was read
            valid = 0;
        }
        else if (*endptr != '\0' && *endptr != '\n')
        {
            // checks if strtol has read the entire string 
            valid = 0;
        }
        else
        {
            valid = 1;
        }
    } while (!valid); // repeat until we get a valid number

    *dest = result;
    return 0;
}

// obtains y/n input from the user.
bool getYesOrNo(void)
{
    char yesOrNo[128];

    // prompt the user for an answer until they enter either y or n
    do
    {
        while(fngets(yesOrNo, 128) == 1)
        {
            continue;
        }
    } while (strlen(yesOrNo) != 1 || (yesOrNo[0] != 'n' && yesOrNo[0] != 'y'));

    if (yesOrNo[0] == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// copies over a task from the example gantt to the main one
// this is necessary because the example gantt is both decalred and defined not
// in the scope of the main function but rather inside an if block, so if we
// do something like gantt[i] = exampleGantt[i], a shallow copy is created and
// only the pointers to name and dependencies arrays are copied over
// when the if block ends, exampleGantt goes out of scope and these arrays cease
// to exist, which leads to undefined behavior
// this function instead creates a deepcopy to eliminate that risk
void taskCopy(Task *dest, Task *src)
{
    strcpy(dest->name, src->name);
    dest->startMonth = src->startMonth;
    dest->endMonth = src->endMonth;
    dest->numDependencies = src->numDependencies;
    dest->colorCode = src->colorCode;

    for (size_t i = 0; i < dest->numDependencies; i++)
    {
        *(dest->dependencies + i) = *(src->dependencies + i);
    }
}

// gets the details of a task from the user. mode can be either 'e' or 'a'.
// 'e' stands for edit, and is used to modify an existing task on the gantt
// 'a' stands for add, and is used to add a new task to the gantt
void getTask(Task *task, char mode)
{
    switch (mode)
    {
    case 'a':
        printf("\nWhat is the name of your task?\n");
        break;

    case 'e':
        printf("\nPlease enter a new name for your task (or enter the old one).\n");
        break;
    }

    // does not accept blank input
    while (fngets(task->name, 30) == 1)
    {
        continue;
    }

    // all of these number inputs have error handling to make sure they are in
    // the correct range
    printf("\nWhat month does this task start? (1-12)\n");
    do
    {
        getNum(&(task->startMonth));
    } while(task->startMonth < 1 || task->startMonth > 12);

    printf("What month does this task end? (1-12)\n");
    do
    {
        getNum(&(task->endMonth));
    } while(task->endMonth < 1 || task->endMonth > 12);

    // a task can only ever have 9 dependencies at maxmimum, because otherwise
    // it could depend on every task /including itself/, but I'm going to
    // disregard those sanity checks on data entry just because we have to 
    // demonstrate a circular dep checking algorith anyway that will catch this
    // stuff
    printf("\nHow many dependencies does this task have?\n");
    do
    {
        getNum(&(task->numDependencies));
    } while(task->numDependencies < 0 || task->numDependencies > 10);

    for (size_t i = 0; i < task->numDependencies; i++)
    {
        printf("Enter a dependent task: \n");
        long temp;

        do
        {
            getNum(&temp);
        } while(temp < 1 || temp > 10);

        task->dependencies[i] = temp - 1;
    }

    // only assign a new color upon the creation of a task. editing it should
    // not change its color
    if (mode == 'a')
    {
        task->colorCode = (int)palette();
    }
}

// asks the user to enter a task to edit, makes sure that task exists, and then
// calls getTask in 'e' mode to actually edit the task
void editTask(Task tasks[10])
{
    char newTask[30];

    printf("\nPlease enter the exact name of the task you want to edit, or leave blank to cancel:\n");
    // outer loop for error checking
    for (int i = 0; i < 1; i++)
    {
        // Prompt user to enter the exact name of the task they want to edit

        if (fngets(newTask, 30) == 1)
        {
            break;
        }

        bool edited = false; // Flag to check if anything has been edited

        for (int j = 0; j < 10; j++)
        {
            // Compare the entered task name with the names of existing tasks
            if (strcmp(tasks[j].name, newTask) == 0)
            {
                getTask(&tasks[j], 'e'); // Edit the relevant task
                edited = true;           // Set the Flag to true
                break;
            }
        }

        if (edited == false)
        {
            // Error message if the task could not be found
            printLog('e', "That task doesn't seem to exist. Are you sure you have the exact name?\n\n");
            i--;
        }
    }
}

void displayGantt(Task tasks[10], int num_tasks)
{
    // #ifdef WIN32
    //     system("cls");
    // #else
    //     system("clear");
    // #endif

    // https://stackoverflow.com/questions/66927511/what-does-e-do-what-does-e11h-e2j-do
    // \e[1;1H: move the cursor to line 1, column 1
    // \e[2J: Move all the text currently on screen into the scrollback buffer
    // the system clear commands print both of these and also \e[3J, which clears the scrollback
    // buffer as well. this might be disruptive from an end-user perspective, as they might not
    // expect to lose all the text in their terminal. therefore, this app prints the ANSI escape
    // sequences separately instead of using system commands
    // printf("\e[1;1H\e[2J");
    printf("\e[1;1H\e[2J");

    // print out top border
    for (int i = 0; i < 180; i++)
    {
        printf("-");
    }

    printf("\n\t\t\t          |");

    // Enum's like Arrays start at 0
    enum month month;
    for (month = 0; month < 13; month++)
    {

        switch (month)
        {
        case (january):
            printf(" %s  |", "January");
            break;
        case (february):
            printf(" %s |", "February");
            break;
        case (march):
            printf(" %s    |", "March");
            break;
        case (april):
            printf(" %s    |", "April");
            break;
        case (may):
            printf(" %s      |", "May");
            break;
        case (june):
            printf(" %s     |", "June");
            break;
        case (july):
            printf(" %s     |", "July");
            break;
        case (august):
            printf(" %s   |", "August");
            break;
        case (september):
            printf(" %s|", "September");
            break;
        case (october):
            printf(" %s  |", "October");
            break;
        case (november):
            printf(" %s |", "November");
            break;
        case (december):
            printf(" %s |", "December");
            break;
        // the dependencies have been included in the months array just because
        // it makes printing out task data a bit easier
        case (dependencies):
            printf(" %s ", "Dependencies");
            break;

        default:
            break;
        }
    }

    printf("\n");

    // print out bottom border
    for (int i = 0; i < 180; i++)
    {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < num_tasks; i++)
    { // print each task name on a line along with its number, for ease of use
        printf("%2d. %-30s|", i + 1, tasks[i].name);

        for (int currentMonth = 1; currentMonth < 14; currentMonth++)
        {
            if ((currentMonth >= tasks[i].startMonth) && (currentMonth <= tasks[i].endMonth))
            {
                //cprintf(93, "███████████"); // print with purple accents
                cprintf(tasks[i].colorCode, "███████████");
            }
            else if (currentMonth == 13)
            {
                for (int j = 0; j < tasks[i].numDependencies; j++)
                {
                    printf("%ld ", tasks[i].dependencies[j] + 1);
                }
            }
            else
            {
                printf("          |");
            }
        }

        printf("\n");
        for (int i = 0; i < 180; i++)
        {
            printf("-");
        }
        printf("\n");
    }
}

char menu()
{
    // get a command, check that it's one of 'edit', 'test', or 'quit', and
    // return the command to the caller
    char cmd[128];
    do {
        printf("To edit the Gantt chart, type 'edit' / To test for circular dependencies, type 'test' / To exit type 'quit' / Press <ENTER> to confirm");
    } while (fngets(cmd, 128) == 1 || strlen(cmd) != 4  || !(strcmp("edit", cmd) == 0 || strcmp("test", cmd) == 0 || strcmp("quit", cmd) == 0));
    
    return cmd[0];
}
