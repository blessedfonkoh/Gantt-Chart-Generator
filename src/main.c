#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
        num_tasks = 10;
        Task exampleGantt[10] = {
            {"Purchase Material", 1, 5, 0, {}},
            {"Sketch Drawings", 2, 4, 0, {0}},
            {"Stretch Canvas", 3, 5, 2, {0, 1}},
            {"Painting", 4, 7, 2, {0, 2}},
            {"Drying", 5, 6, 1, {3}},
            {"Frame Canvas", 6, 9, 2, {0, 4}},
            {"Gallery Exhibit", 7, 10, 3, {0, 2, 4}},
            {"Review Exhibit", 6, 10, 1, {6}},
            {"Feedback Sessions", 9, 11, 1, {7}},
            {"Project Completion", 10, 12, 1, {8}}};

        for (size_t i = 0; i < num_tasks; i++)
        {
            taskCopy(&gantt[i], &exampleGantt[i]);
        }
    }
    else
    {
        printf("How many tasks would you like to enter? (1-10)\n");

        do
        {
            getNum(&num_tasks);
        } while (num_tasks < 1 && num_tasks > 10);

        for (size_t i = 0; i < num_tasks; i++)
        {
            getTask(gantt + i, 'a');
        }
    }

    displayGantt(gantt, num_tasks);

    while (true)
    {
        switch (menu())
        {
        // QUIT
        case 'q':
            return 0;
        // TEST
        case 't':
            long path[10];
            int circ = checkCircularDeps(gantt, num_tasks - 1, path, 0);

            if (circ == 0)
            {
                printLog('s', "No circular dependencies found!\n\n");
            }
            break;
        // EDIT
        case 'e':
            editTask(gantt);
            displayGantt(gantt, num_tasks);
        }
    }
}