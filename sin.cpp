#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    bool inputValid = false;
    double x_min;
    double x_max;

    while (!inputValid)
    {
        cout << "Enter x_min: ";
        cin >> x_min;

        if (cin.fail())
        {
            cin.clear();    
            cin.ignore(1000, '\n'); 
            cout << "Invalid input. Please enter a number.\n\n";
            continue;
        }

        cout << "Enter x_max: ";
        cin >> x_max;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n\n";
            continue;
        }

        if (x_min == x_max)
        {
            cout << "x_min and x_max cannot be equal\n\n";
            continue;
        }

        inputValid = true;
    }

    double x = x_min;
    double y = sin(x_min);

    double y_min = -1.0;
    double y_max = 1.0;

    int grid_width = 80;
    int grid_height = 20;

    string grid[grid_height][grid_width];
    for (int i = 0; i < grid_height; i++)
    {
        for (int j = 0; j < grid_width; j++)
        {
            if (i == grid_height/2)
            {
                grid[i][j] = "-";
            }
            else if (j == grid_width/2)
            {
                grid[i][j] = "|";
            }
            else
            {
                grid[i][j] = " ";
            }
        }
    }

    for (int i = 0; i < grid_width; i++)
    {
        double grid_x = ((x - x_min) / (x_max - x_min)) * (grid_width - 1.0);
        int colIndex = roundl(grid_x);

        double grid_y = ((y - y_min) / (y_max - y_min)) * (grid_height - 1.0);
        int rowIndex = roundl(grid_y);

        if (rowIndex >= 0 && rowIndex < grid_height && colIndex >= 0 && colIndex < grid_width)
            grid[grid_height - 1 - rowIndex][colIndex] = "*";

        x += (x_max - x_min) / (grid_width - 1);
        y = sin(x);
    }

    cout << "\n";
    for (int i = 0; i < grid_height; i++)
    {
        for (int j = 0; j < grid_width; j++)
        {
            cout << grid[i][j];
        }
        cout << "\n";
    }

    cout << "\n";
}
