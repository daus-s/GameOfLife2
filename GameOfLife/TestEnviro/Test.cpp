#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int** indices = new int*[3];
    for (int i = 0; i < 3; ++i)
    {
        indices[i] = new int[3];
        for (size_t t = 0; t < 3; t++)
        {
            indices[i][t] = 'x';
        }
    }
    cout << grid << endl << endl;
    cout << neighbors << endl;
    return 0;
}

static int classic(char** grid, int y, int x)
{
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
