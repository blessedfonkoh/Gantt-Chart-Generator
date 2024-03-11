#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/logging.h"
#include "../include/_data.h"

int fngets(char *dest, int length)
{
    // NOTE: This function is reused from assignment 1

    // length + 1 to account for \n character
    char inputBuffer[length + 1]; // string to read input into
    char *lineFeed;               // pointer to newline character

    while (true)
    {
        printf("> ");
        fgets(inputBuffer, length + 1, stdin);

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
            *lineFeed = '\0';
            strcpy(dest, inputBuffer);

            if (lineFeed == inputBuffer)
            // The user is done entering data and wants to move on the next stage
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

// function re-used from https://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
// I emailed Abey and he said it was okay as long as I cited the source
int getNum(long *dest)
{
    long result;
    char inputBuffer[12]; // use 1KiB just to be sure
    int valid;            // flag for successful conversion

    do
    {
        while (fngets(inputBuffer, 12) == 1)
        {
            continue;
        }

        char *endptr;

        errno = 0; // reset error number
        result = strtol(inputBuffer, &endptr, 10);
        if (errno == ERANGE)
        {
            printf("Sorry, this number is too small or too large.\n");
            valid = 0;
        }
        else if (endptr == inputBuffer)
        {
            // no character was read
            valid = 0;
        }
        else if (*endptr && *endptr != '\n')
        {
            // *endptr is neither end of string nor newline,
            // so we didn't convert the *whole* input
            valid = 0;
        }
        else
        {
            valid = 1;
        }
    } while (!valid); // repeat until we got a valid number

    *dest = result;
    return 0;
}

bool getYesOrNo(void)
{
    char yesOrNo[2];

    // prompt the user for an answer until they enter either y, n, or a blank
    // line
    do
    {
        fngets(yesOrNo, 2);
    } while (yesOrNo[0] != 'n' && yesOrNo[0] != 'y' && yesOrNo[0] != '\0');

    if (yesOrNo[0] == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void taskCopy(Task *dest, Task *src)
{
    strcpy(dest->name, src->name);
    dest->startMonth = src->startMonth;
    dest->endMonth = src->endMonth;
    dest->numDependencies = src->numDependencies;

    for (size_t i = 0; i < dest->numDependencies; i++)
    {
        *(dest->dependencies + i) = *(src->dependencies + i);
    }
}

void getTask(Task *task, char mode)
{
    switch (mode)
    {
    case 'a':
        printf("What is the name of your task?\n");

    case 'e':
        printf("Please enter the new name for your task.\n");
    }

    while (fngets(task->name, 30) == 1)
    {
        continue;
    }

    printf("\nWhat month does this task start? (1-12)\n");
    getNum(&(task->startMonth));

    printf("What month does this task end? (1-12)\n");
    getNum(&(task->endMonth));

    printf("\nHow many dependencies does this task have?\n");
    getNum(&(task->numDependencies));

    for (size_t i = 0; i < task->numDependencies; i++)
    {
        printf("Enter a dependent task: \n");
        long temp;
        getNum(&temp);
        task->dependencies[i] = temp - 1;
    }
}

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
            printf("Error task could not be found. Please enter the exact task name!\n");
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
    { // print each task name on a line
        printf("%2d. %-30s|", i + 1, tasks[i].name);

        /* 
        * Iterative loop for printing out colored blocks for the Gantt display.
        * Loops from month 1 (January) to month 12 (December), 
        * and checks the corresponding tasks start month and end month 
        * and prints coloured blocks within that range.
        * if the 'currentMonth' is equal to 13, the dependencies for that task are printed in place.
        */
        for (int currentMonth = 1; currentMonth < 14; currentMonth++)
        {

            if ((currentMonth >= tasks[i].startMonth) && (currentMonth <= tasks[i].endMonth))
            {
                printf("\e[38;5;93m███████████\e[0m"); // print with purple accents
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
    char cmd[5];
    printf("To edit the Gantt chart, type 'edit' / To test for circular dependencies, type 'test' / To exit type 'quit' / Press <ENTER> to confirm");

    while (fngets(cmd, 5) == 1 || (strcmp(cmd, "edit") != 0 && strcmp(cmd, "test") == 0 && strcmp(cmd, "quit") == 0))
    {
        printf("Please enter a valid input");
    }

    return cmd[0];
}
