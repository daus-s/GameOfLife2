#include <iostream>
#include "Grid.h"

char** myGrid;
char** nextGen;

int mode = 0;

Grid::Grid(int x, int y)
{
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
    if (neighbors == 3)//stays constant
        return 0;
    if (neighbors == 4)//grows one
        return 1;
    if (neigbors > 4) //dies from overpop
        return -1;
}

void Grid::populateNextGen()
{
    //good hint in the assignemnt sheet, 'shadow paging'
    for (int i = 0; i < myGrid.size();++i)
    {
        for (int j = 0; j <  myGrid[i].size(); ++j)
        {
            int growth = determineGrowth()
            if(growth == -1)
                nextGen[i][j]='o';//o is dead right?
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
    if ((i>0 && j>0) && myGrid[i-1][j-1]=='x')
        neighbors++;
    if (j>0  && myGrid[i-1][j]=='x')
        neighbors++;
    if ((i>0 && j<myGrid[i-1].size()-1) && myGrid[i-1][j+1]=='x')
        neighbors++;
    if (j>0 && myGrid[i][j-1]=='x')
        neighbors++;
    if (j<myGrid.size() && myGrid[i][j+1]=='x')
        neighbors++;//nice
    if ((i<myGrid.size()-1&&j>0) && myGrid[i+1][j-1]=='x')
        neighbors++;
    if ((i>0) && myGrid[i+1][j]=='x')
        neighbors++;
    if ((i<myGrid.size()&&j<myGrid.size()) && myGrid[i+1][j+1]=='x')
        neighbors++;

    return neighbors;
}
