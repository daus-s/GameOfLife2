using namespace std;

class Grid
{
    public:
        char** myGrid;
        char** nextGen;

        int countNeighbors();
};
