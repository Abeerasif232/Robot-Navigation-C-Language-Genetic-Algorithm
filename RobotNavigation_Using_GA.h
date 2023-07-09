#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Pre-defined Macros
#define grid_size 12
#define pop_size 200
#define start_point 0
#define end 11

// Global float arrays
float fit_obstacle[pop_size];
float fit_turn[pop_size];
float fit_path[pop_size];
float final_fitness[pop_size];

// Global integer arrays
int Population[pop_size][grid_size];
int turns[pop_size];
int obstacle[pop_size];
int step[pop_size];
int path[grid_size * grid_size][2];

// Constant character variables
const char emptySpace = ' ';
const char obstacles = 178;
const char start = 219;
const char goal = 219;
const char rStep = 46;

// Integer variables
int soultion_step = 0;
int column_column = 1;
int row_row = 0;

// Function to generate random population
void generate_population()
{
    srand(time(0));
    for (int i = 0; i < pop_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (j == 0)
            {
                Population[i][j] = start_point;
            }
            else if (j == grid_size - 1)
            {
                Population[i][j] = end;
            }
            else
            {
                Population[i][j] = (rand() % grid_size);
            }
        }
    }

    // Printing Population
    for (int i = 0; i < pop_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            printf("%d", Population[i][j]);
        }
        printf("\n");
    }
}

// Fuction to find turns
void Turns()
{
    int turn = 0;
    for (int i = 0; i < pop_size; i++)
    {
        for (int j = 0; j < grid_size - 1; j++)
        {
            if (Population[i][j] != Population[i][j + 1])
            {
                turn++;
            }
        }
        turns[i] = turn;
        turn = 0;
    }
}
// function for checking fitness
// Turns , Obstacles and path length
void Fitness(int grid[grid_size][grid_size])
{
    // Finding turns
    Turns();

    int index = 0;
    int obs = 0;

    for (int i = 0; i < pop_size; i++)
    {
        if (column_column)
        {
            for (int j = 0; j < grid_size - 1; j++)
            {
                if ((Population[i][j + 1] - Population[i][j]) >= 0)
                {
                    for (int k = Population[i][j]; k <= Population[i][j + 1]; k++)
                    {
                        path[index][0] = k;
                        path[index][1] = j;
                        index++;
                    }
                }
                if ((Population[i][j + 1] - Population[i][j]) < 0)
                {
                    for (int k = Population[i][j]; k >= Population[i][j + 1]; k--)
                    {
                        path[index][0] = k;
                        path[index][1] = j;
                        index++;
                    }
                }
            }
            path[index][0] = end;
            path[index][1] = end;
        }

        if (row_row)
        {
            for (int j = 0; j < grid_size - 1; j++)
            {
                if ((Population[i][j + 1] - Population[i][j]) >= 0)
                {
                    for (int k = Population[i][j]; k <= Population[i][j + 1]; k++)
                    {
                        path[index][0] = j;
                        path[index][1] = k;
                        index++;
                    }
                }
                if ((Population[i][j + 1] - Population[i][j]) < 0)
                {
                    for (int k = Population[i][j]; k >= Population[i][j + 1]; k--)
                    {
                        path[index][0] = j;
                        path[index][1] = k;
                        index++;
                    }
                }
            }
            path[index][0] = end;
            path[index][1] = end;
        }

        for (int j = 0; j < index; j++)
        {
            if (grid[path[j][0]][path[j][1]] == 1)
            {
                obs++;
            }
        }

        step[i] = index;
        obstacle[i] = obs;
        obs = 0;
        index = 0;
    }

    int obs_max = 0;
    int obs_min = 100;
    int path_max = 0;
    int path_min = 100;
    int turn_max = 0;
    int turn_min = 100;

    for (int i = 0; i < pop_size; i++)
    {
        if (obs_max < obstacle[i])
        {
            obs_max = obstacle[i];
        }
        if (obs_min > obstacle[i])
        {
            obs_min = obstacle[i];
        }
        if (path_max < step[i])
        {
            path_max = step[i];
        }
        if (path_min > step[i])
        {
            path_min = step[i];
        }
        if (turn_max < turns[i])
        {
            turn_max = turns[i];
        }
        if (turn_min > turns[i])
        {
            turn_min = turns[i];
        }
    }

    int w_obs = 3;
    int w_turn = 2;
    int w_path = 2;

    for (int i = 0; i < pop_size; i++)
    {
        fit_obstacle[i] = 1 - ((float)(obstacle[i] - obs_min) / (float)(obs_max - obs_min));
        fit_turn[i] = 1 - ((float)(turns[i] - turn_min) / (float)(turn_max - turn_min));
        fit_path[i] = 1 - ((float)(step[i] - path_min) / (float)(path_max - path_min));
        final_fitness[i] = (100 * w_obs * fit_obstacle[i]) * (((w_path * fit_path[i]) + (w_turn * fit_turn[i])) / (w_path + w_turn));
    }
}

// Sorting 
void Parent(int Population[pop_size][grid_size], float final_fitness[pop_size])
{
    int temp = 0;
    int Array_temp[grid_size];

    for (int i = 0; i < pop_size - 1; i++)
    {
        for (int j = i + 1; j < pop_size; j++)
        {
            if (final_fitness[j] > final_fitness[i])
            {
                for (int k = 0; k < grid_size; k++)
                {
                    Array_temp[k] = Population[j][k];
                }
                for (int k = 0; k < grid_size; k++)
                {
                    Population[j][k] = Population[i][k];
                }
                for (int k = 0; k < grid_size; k++)
                {
                    Population[i][k] = Array_temp[k];
                }

                temp = final_fitness[j];
                final_fitness[j] = final_fitness[i];
                final_fitness[i] = temp;
            }
        }
    }

    printf("\nParenting\n");
    for (int i = 0; i < pop_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            printf("%d", Population[i][j]);
        }
        printf("      %.2f", final_fitness[i]);
        printf("\n");
    }
}

// Function for Crossover
void Crossover()
{
    srand(time(0));

    int cutPoint = rand() % (grid_size - 2) + 1;

    for (int i = 0; i < pop_size / 2; i++)
    {
        for (int j = 0; j < cutPoint; j++)
            Population[i + pop_size / 2][j] = Population[i][j];
        for (int j = cutPoint; j < grid_size; j++)
            Population[i + pop_size / 2][j] = Population[i + 1][j];
    }
}

// Function for mutation
void Mutation()
{
    srand(time(0));
    for (int i = 0; i < pop_size; i += 2)
    {
        Population[i][rand() % (grid_size - 2) + 1] = rand() % grid_size;
    }
}

int Solution(float final_fitness[pop_size])
{

    for (int i = 0; i < pop_size; i++)
    {
        // if (final_fitness[i] == 300)
        if (obstacle[i] == 0)
        {
            soultion_step = step[i];
            int index = 0;
            if (column_column)
            {
                for (int j = 0; j < grid_size - 1; j++)
                {
                    if ((Population[i][j + 1] - Population[i][j]) >= 0)
                    {

                        for (int k = Population[i][j]; k <= Population[i][j + 1]; k++)
                        {

                            path[index][0] = k;
                            path[index][1] = j;
                            index++;
                        }
                    }
                    if ((Population[i][j + 1] - Population[i][j]) < 0)
                    {

                        for (int k = Population[i][j]; k >= Population[i][j + 1]; k--)
                        {

                            path[index][0] = k;
                            path[index][1] = j;
                            index++;
                        }
                    }
                }

                path[index][0] = end;
                path[index][1] = end;
            }

            if (row_row)
            {
                for (int j = 0; j < grid_size - 1; j++)
                {

                    if ((Population[i][j + 1] - Population[i][j]) >= 0)
                    {
                        for (int k = Population[i][j]; k <= Population[i][j + 1]; k++)
                        {
                            path[index][0] = j;
                            path[index][1] = k;
                            index++;
                        }
                    }
                    if ((Population[i][j + 1] - Population[i][j]) < 0)
                    {

                        for (int k = Population[i][j]; k >= Population[i][j + 1]; k--)
                        {
                            path[index][0] = j;
                            path[index][1] = k;
                            index++;
                        }
                    }
                }
                path[index][0] = end;
                path[index][1] = end;
            }
            return 1;
        }
    }
    return 0;
}

// Function for displaying Solution
void Display_Solution(int grid[grid_size][grid_size], int path[grid_size * grid_size][2], int PathLength)
{
    char sGrid[grid_size][grid_size];

    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (grid[i][j] == 0)
            {
                sGrid[i][j] = ' ';
            }
            else if (grid[i][j] == 1)
            {
                sGrid[i][j] = obstacles;
            }
        }
    }

    for (int i = 0; i < PathLength; i++)
    {
        sGrid[path[i][0]][path[i][1]] = rStep;
    }

    sGrid[0][0] = start;
    sGrid[grid_size - 1][grid_size - 1] = goal;

    printf("\n ---------------------------------");
    for (int i = 0; i < grid_size; i++)
    {
        printf("\n%2d|", i);
        for (int j = 0; j < grid_size; j++)
        {
            printf("%c", sGrid[i][j]);
            printf("|");
        }
    }
    printf("\n ----------------------------------\n  ");
    for (int i = 0; i < grid_size; i++)
    {
        printf("%2d", i);
    }
    printf("\n");
}