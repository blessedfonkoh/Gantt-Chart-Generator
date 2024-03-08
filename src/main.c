#include <stdio.h>
#include <stdbool.h>
#include "../include/ganttio.h"
#include "../include/logging.h"
#include "../include/_data.h"
#include "../include/deps.h"

int main(void)
{
    bool useExample = false;
    Task gantt[10];
    long num_tasks;

    printf("Would you like to view an example Gantt? (y for yes, n or ENTER to make your own)\n");
    useExample = getYesOrNo();

    if (useExample)
    {
        long numExampleTasks = 6;
        Task exampleGantt[10] = {
            {"Buy Christmas tree", 11, 11, 0, {}},
            {"Put up decorations", 11, 12, 1, {0}},
            {"Write letters to Santa", 10, 12, 0, {}},
            {"Buy presents for kids", 10, 12, 2, {2, 3}},
            {"Wrap presents", 11, 12, 1, {3}},
            {"Put presents under tree", 12, 12, 2, {3, 4}}};

        num_tasks = numExampleTasks;
        for (size_t i = 0; i < numExampleTasks; i++)
        {
            taskCopy(&gantt[i], &exampleGantt[i]);
        }
    }
    else
    {
        printf("How many tasks would you like to enter?\n");

        do
        {
            getNum(&num_tasks);
        } while (num_tasks < 1 && num_tasks > 10);

        for (size_t i = 0; i < num_tasks; i++)
        {
            getTask(gantt + i);
        }
    }

    displayGantt(gantt, num_tasks);

    long path[10];
    int circ = checkCircularDeps(gantt, num_tasks - 1, path, 0);
    printf("%d\n", circ);

    return 0;
}