#include <stdio.h>
#include <stdbool.h>
#include "ganttio.h"
#include "logging.h"
#include "_data.h"
#include "displayGant.h"

/*
typedef struct task
{
    char name[80];
    int startMonth;
    int endMonth;
    int numDependencies;
    int dependencies[9];
} Task;
*/

void displayGant(struct task tasks[10], int num_tasks)
{
    // print out top border
    for (int i = 0; i < 150; i++)
    {
        printf("-");
    }

    printf("\n\t\t\t|");
    // Enum's like Arrays start at 0
    enum month month;
    for (month = 0; month < 12; month++)
    {

        switch (month)
        {
        case (january):
            printf(" %s   |", "January");
            break;
        case (february):
            printf(" %s  |", "February");
            break;
        case (march):
            printf(" %s     |", "March");
            break;
        case (april):
            printf(" %s     |", "April");
            break;
        case (may):
            printf(" %s       |", "May");
            break;
        case (june):
            printf(" %s      |", "June");
            break;
        case (july):
            printf(" %s      |", "July");
            break;
        case (august):
            printf(" %s    |", "August");
            break;
        case (september):
            printf(" %s |", "September");
            break;
        case (october):
            printf(" %s   |", "October");
            break;
        case (november):
            printf(" %s  |", "November");
            break;
        case (december):
            printf(" %s  |", "December");
            break;
        case (dependencies):
            printf(" %s  |", "Dependencies");
            break;

        default:
            break;
        }
    }
    // print out bottom border
    for (int i = 0; i < 51; i++)
    {
        printf("---");
    }
    for (int currentMonth = 1; currentMonth < 14; currentMonth++)
    {
        for (int i = 0; i < num_tasks; i++)
        {
            // print each task name on a line
            printf("%-15s|", tasks[i].name);
            if ((currentMonth >= tasks[i].startMonth) && (currentMonth <= tasks[i].endMonth))
            {
                printf("█████████"); // from windows character map
            }
            else if(currentMonth == 13)
            {
                for(int j = 0; j < tasks[i].numDependencies; j++)
                {
                    printf("%d, ", tasks[i].dependencies[j]);
                }
            }
            else
            {
                printf("\t\t|");
            }
        }
    }
}
