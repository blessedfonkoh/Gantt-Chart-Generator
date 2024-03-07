

void displayGant(struct task tasks[10], int num_tasks);

//enum for test data 
// Enum to represent task indices
typedef enum {
    demolition, 
    foundation_work, 
    structural_renovation, 
    electrical_wiring, 
    plumbing_installation,
    insulation, 
    drywall_installation, 
    painting, 
    flooring_installation, 
    final_touches
} TaskIndex;

enum month
{
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december,
    dependencies
}; // {0,1,2,3,4,5,6,7,8,9,10,11}