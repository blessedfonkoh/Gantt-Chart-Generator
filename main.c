#include <stdio.h>
#include <stdbool.h>
#include "ganttio.h"
#include "logging.h"
#include "_data.h"

int main(void)
{
    bool useExample = false;
    Task tasks[10];
    int num_tasks;
    printf("Would you like to view an example Gantt? (y for yes, n or ENTER to make your own)\n");
    useExample = getYesOrNo();

    if (useExample)
    {
        // TODO: implement example gantt
    }
    else
    {
        printf("How many tasks would you like to enter?\n");

        do
        {
            scanf("%d", &num_tasks);
        } while (num_tasks < 1 && num_tasks > 10);

        for (int i = 0; i < num_tasks; i++)
        {
            getTask(tasks + i);
        }
    }

    return 0;
}