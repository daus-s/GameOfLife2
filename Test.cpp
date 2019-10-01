#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    char[3][3] grid;
    grid = {{'x','x','x'},{'x','x','x'},{'x','x','x'}};
    int** neighbors = new int[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            neighbors[i][j] = classic(grid, i , j);
        }
    }
    cout << grid << endl << endl;
    cout << neighbors << endl;
    return 0;
};
static int classic(char** myGrid, int y, int x)
{
    char** grid = myGrid;
    int i = y;
    int j = x;
    int neighbors = 0;
    if ((i>0 && j>0) && grid[i-1][j-1]=='x')
    {
        neighbors++;
    }
    if (j>0  && grid[i-1][j]=='x')
    {
        neighbors++;
    }
    if ((i>0 && j<grid[i-1]->size()-1) && grid[i-1][j+1]=='x')
    {
        neighbors++;
    }
    if (j>0 && grid[i][j-1]=='x')
    {
        neighbors++;
    }
    if (j<grid->size()-1 && grid[i][j+1]=='x')
    {
        neighbors++;
    }
    if ((i<grid->size()-1&&j>0) && grid[i+1][j-1]=='x')
    {
        neighbors++;
    }
    if (i>0 && grid[i+1][j]=='x')
    {
        neighbors++;
    }
    if ((i<grid->size()-1&&j<grid[i]->size()-1) && grid[i+1][j+1]=='x')
    {
        neighbors++;
    }

    return neighbors;
}
