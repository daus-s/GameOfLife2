#include <iostream>
#include "Grid.h"

using namespace "Grid.h"

char** myGrid;
char** nextGen;

int mode = 0;

int row;
int col;

Grid::Grid(int x, int y, float density)
{
    col = x;
    row = y;

    char** myGrid = new char*[y];
    for (size_t t = 0; t < y; t++)
    {
        myGrid[t] = new char[x];
    }

        randomGrid(y, x, density);
}
//default to 2 for x,y
Grid::Grid()
{
    col = 2;
    row = 2;

    char** myGrid = new char*[2];
    for (size_t t = 0; t < 2; t++)
    {
        myGrid[t] = new char[2];
    }
}

Grid::Grid(int x, int y, char** grid)
{
    cols = x;
    rows = y;
    myGrid = grid;
}
Grid::~Grid()
{
    delete myGrid;
    delete nextGen;
}

void Grid::randomGrid(int row, int col, float density)
{

    int number = numberofCells(row, col, density);
    cout << number << endl;
    int dashes = (row * col) - number;

    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0 ; j < col; ++j)
        {
            if ((float)rand()/RAND_MAX <= density)
            {
                if (number > 0)
                {
                    myGrid[i][j] = 'X';
                    number--;
                }
                else
                {
                    myGrid[i][j] = '-';
                    dashes--;
                }
            }
            else
            {
                if (dashes > 0)
                {
                    myGrid[i][j] = '-';
                    dashes--;
                }
                else
                {
                    myGrid[i][j] = 'X';
                    number--;
                }
            }
        }
    }
    //debug line
    //printGrid(row, col, randomGrid);
}

void Grid::printGrid()
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            cout << myGrid[i][j];
        }
        cout << endl;
    }
}



int Grid::countNeighbors(int i, int j)
{
    if (mode == 1)//classic
        return countNeighborsClassic(i, j);
    if (mode == 2)//mirror
        return countNeighborsMirror(i, j);
    if (mode  == 3)//doughnut
        return countNeighborsDonut(i, j);
    else
        cout << "no mode selected yet" << endl;
    return -1;
}

int Grid::determineGrowth(int i, int j)
{
    int neighbors = countNeighbors(i, j);
    if (neighbors < 2) //die from lonliness
        return -1;
    if (neighbors == 2)//stays constant
        return 0;
    if (neighbors == 3)//grows one
        return 1;
    if (neigbors > 4) //dies from overpop
        return -1;
}

void Grid::populateNextGen()
{
    //good hint in the assignemnt sheet, 'shadow paging'
    for (int i = 0; i < row;++i)
    {
        for (int j = 0; j < col; ++j)
        {
            int growth = determineGrowth(i,j)
            if(growth == -1)
                nextGen[i][j]='-';//- is dead right?
            else
            if (growth == 1)
                nextGen[i][j]='X';//x  is alive
            else
            if(growth==0)
                nextGen[i][j] = myGrid[i][j];//remains constant
        }
    }
}

/*counts the number of neighbors in the 8 adjacent positions
 *if the adjacent location is on the outside, the method simply does not count that cell
 *running in test environment to test accuracy on a 3x3
 */
int Grid::countNeighborsClassic(int i, int j)
{
    int neighbors = 0;
    if ((i>0 && j>0) && grid[i-1][j-1]=='X')
    {
        neighbors++;
    }
    if (j>0  && grid[i-1][j]=='X')
    {
        neighbors++;
    }
    if ((i>0 && j<grid[i-1]->size()-1) && grid[i-1][j+1]=='X')
    {
        neighbors++;
    }
    if (j>0 && grid[i][j-1]=='X')
    {
        neighbors++;
    }
    if (j<grid->size()-1 && grid[i][j+1]=='X')
    {
        neighbors++;
    }
    if ((i<grid->size()-1&&j>0) && grid[i+1][j-1]=='X')
    {
        neighbors++;
    }
    if (i>0 && grid[i+1][j]=='X')
    {
        neighbors++;
    }
    if ((i<grid->size()-1&&j<grid[i]->size()-1) && grid[i+1][j+1]=='X')
    {
        neighbors++;
    }

    return neighbors;

}

int Grid::countNeighborsDonut(int i, int j)
{
    //i->rows
    //j-cols
    //similar to time and momentum and space and energy so think that for project
    int cols = myGrid[0]->size();
    int rows = myGrid->size();
    int neighbors = 0;
    if (grid[(i-1)%rows][(j-1)%cols]=='X')
    {
        neighbors++;
    }
    if (grid[(i-1)%rows][j]=='X')
    {
        neighbors++;
    }
    if (grid[(i-1)%rows][(j+1%cols)]=='X')
    {
        neighbors++;
    }
    if (grid[i][(j-1)%cols]=='X')
    {
        neighbors++;
    }
    if (grid[i][(j+1)%cols]=='X')
    {
        neighbors++;
    }
    if (grid[(i+1)%rows][(j-1)%cols]=='X')
    {
        neighbors++;
    }
    if (grid[(i+1)%rows][j]=='X')
    {
        neighbors++;
    }
    if (grid[(i+1)%rows][(j+1)%cols]=='X')
    {
        neighbors++;
    }

    return neighbors;

}


int Grid::countNeighborsMirror(int i, int j)
{
    int neighbors = 0;

    //conditionals for determining exceptions, corners, edges
    if ((i==0 && j==0) && myGrid[i][j]=='X')
    {
        neighbors += 3;
    }
    if (i==0 && j==col) && myGrid[i][j]=='X')
    {
        neighbors +=  3;
    }
    if ((i==row && j==col) && myGrid[i][j]=='X')
    {
        neighbors += 3;
    }
    if (i==row && j==0) && myGrid[i][j]=='X')
    {
        neighbors +=  3;
    }
    //these however are the edge cases rather than the corner cases
    //this checks to make sure it is not either corner
    if ((i==0 && (j!=0 && j!=col)) && myGrid[i][j]=='X')
    {
        neighbors++;
    }
    if (i=row && (j!=0 && j!=col)) && myGrid[i][j]=='X')
    {
        neighbors++;
    }
    if ((i!=row&&i!=0) && j==col) && myGrid[i][j]=='X')
    {
        neighbors++;
    }
    if ((i!=row&&i!=0) && j==0) && myGrid[i][j]=='X')
    {
        neighbors++;
    }


    //sorry for bad naming convention here, however rather than creating another array i used 8 chars for neighbors
    //okey dokey: naming convention of neighbors is height, side, with (u)pper, (e)ven, (l)ower for the vertical height
    //and for side we have (l)eft, (m)iddle, (r)ight
    char ul;
    char um;
    char ur;
    char el;
    char er;
    char ll;
    char lm;
    char lr;

    //row by row
    if (i>0)
    {
        ul = myGrid[i-1][j-1];
        um = myGrid[i-1][j];
        ur = myGrid[i-1][j+1];
    }
    if (j>0)
    {
        el = myGrid[i][j-1];
    }
    //this would be em but this is what we are observing from- i.e. particle not affecting itself gravitaionally
    if (j<col-1)
    {
        er = myGrid[i][j+1];
    }
    if (i<row-1)
    {
        ll = myGrid[i+1][j-1];
        lm = myGrid[i+1][j];
        lr = myGrid[i+1][j+1];
    }

    if (ul == 'X')
        neighbors++;
    if (um == 'X')
        neighbors++;
    if (ur == 'X')
        neighbors++;
    if (el == 'X')
        neighbors++;
    if (er == 'X')
        neighbors++;
    if (ll == 'X')
        neighbors++;
    if (lm == 'X')
        neighbors++;
    if (lr == 'X')
        neighbors++;

    return neighbors;
}

//set utility for index in the grid, modifies the old grid not nextGen because this is used for setup
void set(int i, int j, char c)
{
    if (c!='X'||c!='-')
    {
        cout << "error in entering set in \"Grid.h\"" << endl;
        return;
    }
    else
    {
        myGrid[i][j]=c;
    }
}

bool Grid::isEmpty()
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (myGrid[i][j]=='X')
                return false;
    return true;
}

bool Grid::isConstant()
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (myGrid[i][j]!=nextGen[i][j])
                return false;
    return true;
}
