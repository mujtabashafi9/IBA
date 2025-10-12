#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));

    int dayCounter = 0;
    int healthyCount = 0, infectedCount = 0, recoveredCount = 0, deadCount = 0;
    const int MAX_SIZE = 100;
    int infectionDuration[MAX_SIZE][MAX_SIZE] = {0};
    int grid[MAX_SIZE][MAX_SIZE] = {0};

    int width, height, initiallyInfected;
    float infectionProb, worsenProb;
    int recoveryTime = 5;
    int totalDays = 30;

    cout << "Enter grid width (1-100): ";
    while (!(cin >> width) || width < 1 || width > 100)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid width. Enter again: ";
    }

    cout << "Enter grid height (1-100): ";
    while (!(cin >> height) || height < 1 || height > 100)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid height. Enter again: ";
    }

    cout << "Enter number of initially infected people: ";
    while (!(cin >> initiallyInfected) || initiallyInfected < 0 || initiallyInfected > width * height)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid number. Enter again: ";
    }

    cout << "Enter infection probability (0-1): ";
    while (!(cin >> infectionProb) || infectionProb < 0 || infectionProb > 1.0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a value between 0 and 1: ";
    }

    cout << "Enter worsening probability (0-1): ";
    while (!(cin >> worsenProb) || worsenProb < 0 || worsenProb > 1.0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a value between 0 and 1: ";
    }

    int remaining = initiallyInfected;
    while (remaining > 0)
    {
        int y = rand() % height;
        int x = rand() % width;
        int severity = (rand() % 9) + 1;
        if (grid[y][x] == 0)
        {
            grid[y][x] = severity;
            infectionDuration[y][x] = 0;
            remaining--;
        }
    }

    cout << "\nInitial Grid:\n";
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[y][x] == 0)
                cout << ".";
            else
                cout << grid[y][x];
        }
        cout << endl;
    }
    cout << endl;

    for (int day = 1; day <= totalDays; day++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int maxSeverity = 0;

                if (grid[y][x] == 0)
                {
                    int infectedNeighbors = 0;

                    if (y > 0 && grid[y - 1][x] > 0 && grid[y - 1][x] < 10)
                    {
                        infectedNeighbors++;
                        maxSeverity = max(maxSeverity, grid[y - 1][x]);
                    }
                    if (y < height - 1 && grid[y + 1][x] > 0 && grid[y + 1][x] < 10)
                    {
                        infectedNeighbors++;
                        maxSeverity = max(maxSeverity, grid[y + 1][x]);
                    }
                    if (x > 0 && grid[y][x - 1] > 0 && grid[y][x - 1] < 10)
                    {
                        infectedNeighbors++;
                        maxSeverity = max(maxSeverity, grid[y][x - 1]);
                    }
                    if (x < width - 1 && grid[y][x + 1] > 0 && grid[y][x + 1] < 10)
                    {
                        infectedNeighbors++;
                        maxSeverity = max(maxSeverity, grid[y][x + 1]);
                    }

                    float chance = (rand() % 101) / 100.0;
                    if (infectedNeighbors > 0 && chance <= infectionProb)
                    {
                        grid[y][x] = (infectedNeighbors > 1) ? maxSeverity : (rand() % maxSeverity) + 1;
                        infectionDuration[y][x] = 0;
                    }
                    continue;
                }

                if (grid[y][x] == -1 || grid[y][x] == 10)
                    continue;

                float chance = (rand() % 101) / 100.0;
                if (chance <= worsenProb)
                {
                    if (grid[y][x] >= 1 && grid[y][x] <= 9)
                    {
                        grid[y][x]++;
                        infectionDuration[y][x]++;
                    }
                }
                else
                {
                    if (grid[y][x] > 1)
                    {
                        grid[y][x]--;
                        infectionDuration[y][x]++;
                    }
                }

                if (infectionDuration[y][x] == recoveryTime)
                {
                    grid[y][x] = -1;
                    infectionDuration[y][x] = 0;
                }

                if (grid[y][x] == 10 || grid[y][x] == -1)
                    infectionDuration[y][x] = 0;
            }
        }

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (grid[y][x] == 0)
                    healthyCount++;
                else if (grid[y][x] == -1)
                    recoveredCount++;
                else if (grid[y][x] == 10)
                    deadCount++;
                else
                    infectedCount++;
            }
        }

        cout << "Day " << day << ": Healthy: " << healthyCount
             << ", Infected: " << infectedCount
             << ", Recovered: " << recoveredCount
             << ", Dead: " << deadCount << endl;

        healthyCount = infectedCount = recoveredCount = deadCount = 0;
    }

    cout << "\nFinal Grid:\n";
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[y][x] == -1)
                cout << "R";
            else if (grid[y][x] == 0)
                cout << ".";
            else if (grid[y][x] == 10)
                cout << "D";
            else
                cout << grid[y][x];
        }
        cout << endl;
    }

    return 0;
}
