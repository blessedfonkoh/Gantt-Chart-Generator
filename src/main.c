#include <stdio.h>
#include <stdbool.h>
#include "ganttio.h"
#include "logging.h"
#include "_data.h"
#include "displayGant.h"

int main(void)
{
    bool useExample = false;
    Task tasks[10];
    int num_tasks;
    printf("Would you like to view an example Gantt? (y for yes, n or ENTER to make your own)\n");
    useExample = getYesOrNo();

    if (useExample)
    {
        // Creating an array of 10 tasks
        Task tasks[10] = {
            {"Demolition", january, february, 0, {}},
            {"Foundation Work", february, march, 0, {}},
            {"Structural Renovation", march, may, 1, {foundation_work}},
            {"Electrical Wiring", april, june, 2, {plumbing_installation, structural_renovation}},
            {"Plumbing Installation", may, july, 1, {structural_renovation}},
            {"Insulation", june, august, 1, {electrical_wiring}},
            {"Drywall Installation", july, september, 2, {electrical_wiring, insulation}},
            {"Painting", august, october, 2, {drywall_installation, painting}},
            {"Flooring Installation", september, november, 0, {}},
            {"Final Touches", october, december, 3, {painting, flooring_installation, drywall_installation}}};
        
        // implement example gantt
        displayGant(tasks, num_tasks);
        // test comment
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