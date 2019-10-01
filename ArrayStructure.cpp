#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int[][] indices = new int[3][3];
    indices[0] = {00,01,02};
    indices[1] = {10,11,12};
    indices[2] = {20,21,22};


    for(int i =  0; i < 3; ++i)
    {
        for (int  j = 0; j < 3; ++j)
        {
            cout <<  indices[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;
    for(int i = 0; i<3;++i)
    {
        for (int j = 0; j<3; ++j)
        {
            cout <<  "["<< i << "," << j <<"]"
        }
        cout << endl;
    }
    return 0;
}
