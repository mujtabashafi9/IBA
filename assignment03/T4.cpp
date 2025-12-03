#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int MAX_COLS = 50;
int dead_end_counter = 0; // counts how many dead ends we hit

// checks if (x,y) is inside maze limits
bool is_valid(int x, int y, int rows, int cols)
{
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool solve_maze(char maze[][MAX_COLS], int rows, int cols,
                int x, int y, vector<pair<int, int>> &path)
{
    // stop if outside maze
    if (!is_valid(x, y, rows, cols))
        return false;

    // reached exit
    if (maze[x][y] == 'E')
    {
        path.push_back({x, y});
        return true;
    }

    // blocked or already visited
    if (maze[x][y] == '#' || maze[x][y] == '*')
        return false;

    char previous_value = maze[x][y]; // store original cell

    // mark visited
    if (maze[x][y] != 'S')
        maze[x][y] = '*';

    path.push_back({x, y}); // add current cell to path

    // directions: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // try all 4 directions
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // if one direction solves the maze, return success
        if (solve_maze(maze, rows, cols, nx, ny, path))
            return true;
    }

    // backtracking: no path from here
    dead_end_counter++;
    path.pop_back(); // remove last cell

    // restore original character unless it was S
    maze[x][y] = (previous_value == 'S' ? 'S' : '.');

    return false;
}

int main()
{
    int total_rows, total_cols;
    cout << "Enter maze dimensions (rows cols): ";
    cin >> total_rows >> total_cols;

    char board[50][MAX_COLS]; // maze storage

    // input maze row by row
    cout << "Enter maze row by row:\n";
    for (int r = 0; r < total_rows; r++)
    {
        cout << "Row " << r + 1 << ": ";
        for (int c = 0; c < total_cols; c++)
        {
            cin >> board[r][c];
        }
    }

    int start_count = 0, end_count = 0; // ensure exactly 1 S and 1 E
    int start_x = -1, start_y = -1;     // store S location

    // scan maze to find S and E
    for (int r = 0; r < total_rows; r++)
    {
        for (int c = 0; c < total_cols; c++)
        {
            if (board[r][c] == 'S')
            {
                start_count++;
                start_x = r;
                start_y = c;
            }
            if (board[r][c] == 'E')
                end_count++;
        }
    }

    // invalid maze if not exactly one S and one E
    if (start_count != 1 || end_count != 1)
    {
        cout << "Invalid maze: must contain exactly one S and one E.\n";
        return 0;
    }

    cout << "\nSolving maze...\n\n";

    vector<pair<int, int>> route; // stores final path

    // try solving starting from S
    if (solve_maze(board, total_rows, total_cols, start_x, start_y, route))
    {
        cout << "Solution found!\n";
        cout << "Path length: " << route.size() << "\n\n";

        cout << "Final maze with solution path:\n";

        // mark final path on maze
        for (auto &cell : route)
            if (board[cell.first][cell.second] != 'S' && board[cell.first][cell.second] != 'E')
                board[cell.first][cell.second] = '*';

        // print final maze
        for (int r = 0; r < total_rows; r++)
        {
            for (int c = 0; c < total_cols; c++)
                cout << board[r][c];
            cout << "\n";
        }

        // print coordinates of solution path
        cout << "\nPath coordinates:\n";
        for (int i = 0; i < route.size(); i++)
        {
            cout << "(" << route[i].first << "," << route[i].second << ")";
            if (i != route.size() - 1)
                cout << " -> ";
        }
        cout << "\n";
    }
    else
    {
        // maze cannot be solved
        cout << "No solution exists.\n\n";

        cout << "Explored maze:\n";
        for (int r = 0; r < total_rows; r++)
        {
            for (int c = 0; c < total_cols; c++)
                cout << board[r][c];
            cout << "\n";
        }

        // show how many dead ends were hit
        cout << "\nDead ends encountered: " << dead_end_counter << "\n";
    }

    return 0;
}

// test case
//  10 12
// ############
// #S......#..#
// #.#######.#.
// #.#.....#.#.
// #.#.###.#.#.
// #.#.#.#.#.#.
// #...#.#.#.#E
// ###.#.#.#.#.
// #.....#.....#
// ############
