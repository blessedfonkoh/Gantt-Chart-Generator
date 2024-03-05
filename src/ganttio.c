#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "logging.h"
#include "_data.h"

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
            warn("Your input has exceeded the maximum length of %d. Please try again.\n\n", length - 1);

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

void getTask(Task *task)
{
    // TODO: Error handling for basically all of this lol

    printf("What is the name of your task?\n");
    fngets(task->name, 80);

    printf("\nWhat month does this task start? (1-12)\n");
    scanf("%d", &(task->startMonth));

    printf("\nWhat month does this task end? (1-12)\n");
    scanf("%d", &(task->endMonth));

    printf("\nHow many dependencies does this task have?\n");
    scanf("%d", &(task->numDependencies));

    for (int i = 0; i < task->numDependencies; i++)
    {
        printf("Enter a dependent task: \n");
        scanf("%d", &(task->dependencies[i]));
    }
}
