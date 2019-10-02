using namespace std;

#ifndef Grid_H
#define Grid_H


class Grid
{
    public:
        int row;
        int col;

        int mode;

        char** myGrid;
        char** nextGen;

        //count neighbor functions
        int countNeighbors();
        int countNeighborsClassic();
        int countNeighborsMirror();
        int countNeighborsDonut();

        //utilities; like print set
        void printGrid();
        void set(int i, int j, char c);

        //function functions, to edit/ update to change grid display
        int determineGrowth(int i, int j);
        void populateNextGen();
        void randomGrid(int i, int j, float density);

        //constructors & destructors
        Grid();
        Grid(char** array);
        Grid(int x, int y, float density);
        ~Grid();

        //booleans
        bool isEmpty();
        bool isConstant();
};
#endif
