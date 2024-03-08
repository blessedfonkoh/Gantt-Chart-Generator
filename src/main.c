#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../include/ganttio.h"
#include "../include/logging.h"
#include "../include/_data.h"

int main(void)
{
    bool useExample = false;
    Task tasks[10];
    int num_tasks;
    printf("Would you like to view an example Gantt? (y for yes, n or ENTER to make your own)\n");
    useExample = getYesOrNo();
    bool editGantt = false;

    if (useExample)
    {
        // Creating an array of 10 tasks
        Task tasks[10] = {
            {"Purchase Material", 1, 5, 0, {}},
            {"Sketch Drawings", 2, 4, 0, {1}},
            {"Stretch Canvas", 3, 5, 2, {1, 2}},
            {"Painting", 4, 7, 2, {1, 3}},
            {"Drying", 5, 6, 1, {4}},
            {"Frame Canvas", 6, 9, 2, {1, 5}},
            {"Gallery Exhibit", 7, 10, 3, {1, 3, 5}},
            {"Review Exhibit", 6, 10, 1, {7}},
            {"Feedback Sessions", 9, 11, 1, {8}},
            {"Project Completion", 10, 12, 1, {9}}};

        // Display Sample Gantt
        displayGant(tasks, 10);

        // Ask user if they want to edit the Gantt chart
        printf("If you wish to edit the Gantt type (y for yes, n or ENTER for no)\n");
        editGantt = getYesOrNo();

        if (editGantt)
        {
            char newTask[80];

            // outer loop for error checking
            for (int i = 0; i < 1; i++)
            {
                // Prompt user to enter the exact name of the task they want to edit
                printf("Please enter the exact name of the task you want to edit\n");
                fngets(newTask, 80); // Get the name of the new task
                bool edited = false; // Flag to check if anything has been edited

                for (int j = 0; j < 10; j++)
                {
                    // Compare the entered task name with the names of existing tasks
                    if (strcmp(tasks[j].name, newTask) == 0)
                    {
                        editTask(tasks + j); // Edit the relevant task
                        displayGant(tasks, 10);
                        edited = true; // Set the Flag to true
                        break;
                    }
                    else
                    {
                        edited = false;
                    }
                }

                if (edited == false)
                {
                    // Error message if the task could not be found
                    printf("Error task could not be found. Please enter the exact task name!\n");
                    i--;
                }
                else
                {
                    break;
                }
            }
        }
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

        displayGant(tasks, num_tasks);
    }

    return 0;
}