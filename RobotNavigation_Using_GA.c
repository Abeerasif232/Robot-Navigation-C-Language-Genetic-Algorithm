// Complex Engineering problem
// Robot navigation
// Built-in C libraries
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "RobotNavigation_Using_GA.h"

// Main function
int main()
{
    int i = 1;
    int flag = 0;

    int grid[grid_size][grid_size] =
        {
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
            {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
            {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
        };
    // calling Function to generate random population
    generate_population();
    int a = 0;
    while (a != 1)
    {
        if (i % 50 == 0)
        {
            generate_population();
        }
        // Calling fitness function
        Fitness(grid);
        flag = Solution(final_fitness);

        if (flag)
        {
            printf("Solution is found in iteration = %d", i);
            Display_Solution(grid, path, soultion_step);
            break;
        }
        Parent(Population, final_fitness);
        // calling Function of crossover
        Crossover();
        // calling function of mutation
        Mutation();

        i++;
    }
    return 0;
}
