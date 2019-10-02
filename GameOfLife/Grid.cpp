#include <iostream>
#include "Grid.h"

char** myGrid;
char** nextGen;

int mode;

int row;
int col;

float density = 0.0f;

//generates random grid based off parameters passed in by user
Grid::Grid(int x, int y, float density, int m)
{
    col = x;
    row = y;
    this->density = density;
    mode = m;
    cout << x << "," << y << "," << density << endl;


    myGrid = new char*[y];
    for (size_t t = 0; t < y; t++)
    {
        myGrid[t] = new char[x];
    }
    //cout << "entering randomGrid()" << endl;
    randomGrid(y, x, density);
    //cout << "do i make it here?" << endl;
    cout << "constructor complete" << endl;
    printGrid();

    nextGen = new char*[y];
    for (size_t t = 0; t < y; t++)
    {
        nextGen[t] = new char[x];
    }
}
//default to 2 for x,y
Grid::Grid()
{
    col = 2;
    row = 2;

    myGrid = new char*[2];
    for (size_t t = 0; t < 2; t++)
    {
        myGrid[t] = new char[2];
    }
}
//uses pointer for grid location
Grid::Grid(int x, int y, char** grid, int m)
{
    col = x;
    row = y;
    myGrid = new char*[y];
    for (size_t t = 0; t < y; t++)
    {
        myGrid[t] = new char[x];
    }


    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            myGrid[i][j]=grid[i][j];
        }
    }
    mode = m;

    nextGen = new char*[y];
    for (size_t t = 0; t < y; t++)
    {
        nextGen[t] = new char[x];
    }
}
Grid::~Grid()
{
    delete myGrid;
    delete nextGen;
}


//populates grid using density and dimension inputs from constructor
void Grid::randomGrid(int row, int col, float density)
{
    srand(time(0));
    int number = (float)(row*col)*density;
    //cout << number << endl;
    int dashes = (row * col) - number;

    for (size_t i = 0; i < row; ++i)
    {
        for (size_t j = 0 ; j < col; ++j)
        {
            if ((float)rand()/RAND_MAX <= density) //float value from rand/
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
    printGrid(); //we get to here
    return;
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
    //cout << "countNeighbors time" << endl;
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
    //cout << "i: " << i << " j: " << j<< endl;
    //cout << "determine growth:" << mode << "mode" << endl;
    int neighbors = countNeighbors(i, j);
    if (neighbors < 2) //die from lonliness
        return -1;
    if (neighbors == 2)//stays constant
        return 0;
    if (neighbors == 3)//grow one
        return 1;
    if (neighbors > 4) //dies from overpop
        return -1;
}

//fills in the 'nextGen' 2d array
void Grid::populateNextGen()
{
    //good hint in the assignemnt sheet, 'shadow paging'
    //cout << "locating segfault just inside populateNextGen" << endl;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            //cout << "locating segfault, outside of determineGrowth" << endl;
            int growth = determineGrowth(i,j);
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
    cout << "we made it here?" << endl;
    int neighbors = 0;
    if ((i>0 && j>0) && myGrid[i-1][j-1]=='X')
    {
        neighbors++;
    }
    if (i>0  && myGrid[i-1][j]=='X')
    {
        neighbors++;
    }
    if ((i>0 && j<col-1) && myGrid[i-1][j+1]=='X')
    {
        neighbors++;
    }
    if (j>0 && myGrid[i][j-1]=='X')
    {
        neighbors++;
    }
    if (j<col-1 && myGrid[i][j+1]=='X')
    {
        neighbors++;
    }
    if ((i<row-1&&j>0) && myGrid[i+1][j-1]=='X')
    {
        neighbors++;
    }
    if (i<row-1 && myGrid[i+1][j]=='X')
    {
        neighbors++;
    }
    if ((i<row-1&&j<col-1) && myGrid[i+1][j+1]=='X')
    {
        neighbors++;
    }
    cout << neighbors << endl;
    return neighbors;

}

int Grid::countNeighborsDonut(int i, int j)
{
    //i->row
    //j-col
    //similar to time and momentum and space and energy so think that for project
    int neighbors = 0;
    if (myGrid[(i-1)%row][(j-1)%col]=='X')
    {
        neighbors++;
    }
    if (myGrid[(i-1)%row][j]=='X')
    {
        neighbors++;
    }
    if (myGrid[(i-1)%row][(j+1%col)]=='X')
    {
        neighbors++;
    }
    if (myGrid[i][(j-1)%col]=='X')
    {
        neighbors++;
    }
    if (myGrid[i][(j+1)%col]=='X')
    {
        neighbors++;
    }
    if (myGrid[(i+1)%row][(j-1)%col]=='X')
    {
        neighbors++;
    }
    if (myGrid[(i+1)%row][j]=='X')
    {
        neighbors++;
    }
    if (myGrid[(i+1)%row][(j+1)%col]=='X')
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
    if ((i==0 && j==col) && myGrid[i][j]=='X')
    {
        neighbors +=  3;
    }
    if ((i==row && j==col) && myGrid[i][j]=='X')
    {
        neighbors += 3;
    }
    if ((i==row && j==0) && myGrid[i][j]=='X')
    {
        neighbors +=  3;
    }
    //these however are the edge cases rather than the corner cases
    //this checks to make sure it is not either corner
    if ((i==0 && (j!=0 && j!=col)) && myGrid[i][j]=='X')
    {
        neighbors++;
    }
    if ((i==row && (j!=0 && j!=col)) && myGrid[i][j]=='X')
    {
        neighbors++;
    }
    if (((i!=row&&i!=0) && j==col) && myGrid[i][j]=='X')
    {
        neighbors++;
    }
    if (((i!=row&&i!=0) && j==0) && myGrid[i][j]=='X')
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
        if (j>0)
        {
            ul = myGrid[i-1][j-1];
        }

            um = myGrid[i-1][j];

        if (j<col-1)
        {
            ur = myGrid[i-1][j+1];
        }
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
        if (j > 0)
        {
            ll = myGrid[i+1][j-1];
        }
            lm = myGrid[i+1][j];
        if (j < col -1)
        {
            lr = myGrid[i+1][j+1];
        }
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
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            if (myGrid[i][j]=='X')
                return false;
    return true;
}

bool Grid::isConstant()
{
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            if (myGrid[i][j]!=nextGen[i][j])
                return false;
    return true;
}
void setMode(int m)
{
    mode = m;
}
