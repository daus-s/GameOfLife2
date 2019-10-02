using namespace std;

#ifndef Grid_H
#define Grid_H


class Grid
{
    public:
        int row;
        int col;

        int mode;

        float density;

        char** myGrid;
        char** nextGen;

        //count neighbor functions
        int countNeighbors(int i, int j);
        int countNeighborsClassic(int i, int j);
        int countNeighborsMirror(int i, int j);
        int countNeighborsDonut(int i, int j);

        //utilities; like print set
        void printGrid();
        void set(int i, int j, char c);

        //function functions, to edit/ update to change grid display
        int determineGrowth(int i, int j);
        void populateNextGen();
        void randomGrid(int i, int j, float density);
        int numberofCells();

        //constructors & destructors
        Grid();
        Grid(int row, int col, char** array);
        Grid(int x, int y, float density);
        ~Grid();

        //booleans
        bool isEmpty();
        bool isConstant();
};
#endif
