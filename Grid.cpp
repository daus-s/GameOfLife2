#include <iostream>
#include "Grid.h"

char** myGrid;
char** nextGen;

int mode = 0;

int row;
int col;

Grid::Grid(int x, int y)
{
    col = x;
    row = y;

    myGrid = new char[y][x];
    for (int i = 0; i < y; ++i)
        for (int j = 0; j < x; ++j)
            myGrid[i][j] = '-';
}
int Grid::countNeighbors()
{
    if (mode == 1)//classic
        return countNeighborsClassic();
    if (mode == 2)//mirror
        return countNeighborsMirror();
    if (mode  == 3)//doughnut
        return countNeighborsDonut();
    else
        cout << "no mode selected yet" << endl;
    return -1;
}

int Grid::determineGrowth()
{
    int neighbors = countNeighbors();
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
    for (int i = 0; i < myGrid->size();++i)
    {
        for (int j = 0; j <  myGrid[i]->size(); ++j)
        {
            int growth = determineGrowth()
            if(growth == -1)
                nextGen[i][j]='-';//o is dead right?
            else
            if (growth == 1)
                nextGen[i][j]='x';//x  is alive
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

int Grid::countNeighborsDonut(int i, int j)
{
    //i->rows
    //j-cols
    //similar to time and momentum and space and energy so think that for project
    int cols = myGrid[0]->size();
    int rows = myGrid->size();
    int neighbors = 0;
    if (grid[(i-1)%rows][(j-1)%cols]=='x')
    {
        neighbors++;
    }
    if (grid[(i-1)%rows][j]=='x')
    {
        neighbors++;
    }
    if (grid[(i-1)%rows][(j+1%cols)]=='x')
    {
        neighbors++;
    }
    if (grid[i][(j-1)%cols]=='x')
    {
        neighbors++;
    }
    if (grid[i][(j+1)%cols]=='x')
    {
        neighbors++;
    }
    if (grid[(i+1)%rows][(j-1)%cols]=='x')
    {
        neighbors++;
    }
    if (grid[(i+1)%rows][j]=='x')
    {
        neighbors++;
    }
    if (grid[(i+1)%rows][(j+1)%cols]=='x')
    {
        neighbors++;
    }

    return neighbors;

}


int Grid::countNeighborsMirror(int i, int j)
{
    int neighbors = 0;

    //conditionals for determining exceptions, corners, edges
    if ((i==0 && j==0) && myGrid[i][j]=='x')
    {
        neighbors += 3;
    }
    if (i==0 && j==col) && myGrid[i][j]=='x')
    {
        neighbors +=  3;
    }
    if ((i==row && j==col) && myGrid[i][j]=='x')
    {
        neighbors += 3;
    }
    if (i==row && j==0) && myGrid[i][j]=='x')
    {
        neighbors +=  3;
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
    //this would be em but this is what we are observing from- i.e. particle not affecting itself gracitaionally
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

    if (ul == 'x')
        neighbors++;
    if (um == 'x')
        neighbors++;
    if (ur == 'x')
        neighbors++;
    if (el == 'x')
        neighbors++;
    if (er == 'x')
        neighbors++;
    if (ll == 'x')
        neighbors++;
    if (lm == 'x')
        neighbors++;
    if (lr == 'x')
        neighbors++;

    return neighbors;
}
