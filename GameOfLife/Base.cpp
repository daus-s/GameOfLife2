#include <iostream>
#include "Grid.h"


using namespace std;

bool checkCharacters(Grid original)
{
    for (int i = 0; i < original.row;++i)
    {
        for (int j = 0; j < original.col; ++j)
        {
            if (original.myGrid[i][j] !='x' || original->myGrid[i][j] != '-')
                return false;
        }
    }
    return true;
}

void lowerLetterCase(Grid original)
{
    for (int i = 0; i < original.row;++i)
    {
        for (int j = 0; j < original.col; ++j)
        {
            if (original.myGrid[i][j] == 'X')
                original.set(i, j, 'x');
        }
    }
}



int numberofCells(int row, int col, float density)
{
    return (int)((float)(row * col) * density);
}



void parse()
{
    Grid grid;
    cout << "do you wish to enter a map file? (y/n)" << endl;
    char mapFile = 'X';
    cin >> mapFile;
    if (mapFile != 'Y' || mapFile != 'N' || mapFile != 'y' || mapFile != 'n')
    {
        //this makes sure you enter correct values
        cout << "enter one of yYnN" << endl;
        parse();
        return;
    }
    else if (mapFile != 'Y' || mapFile != 'y')
    {
        cout << "enter file (\"file\"+.txt)" << endl;
        string pathname = "";
        cin >> pathname;
        ifstream reader;
        reader.open(pathname, ifstream::in);
        int col = 0;
        int row = 0;

        //this will be the one that gets passed to grid constructor
        char** passedGrid;

        try
        {
            string line = "";
            getline(reader, line);
            row = stoi(line);
            getline(reader, line);
            col = stoi(line);
        }
        catch (const invalid_argument& ia)//got from c++.com
        {
            cout << "bad input in row and/or col values" << endl;
            parse();
            return;
        }
        passedGrid = new char*[row];
        for (int i = 0; i < row; ++i)
        {
            passedGrid[i] = new char[col];
        }
        int i = 0;
        int j = 0;
        while (!reader.eof())
        {
            getline(reader, line);
            if (strlen(line)==col)
            {
                for (char c: line)
                {
                    passedGrid[i][j++]=c;
                }
            }
            else
            {
                cout << "error in length of input file, input grid not correct dimensions" << endl;
                parse();
                return;
            }
            ++i;
        }
        lowerLetterCase(passedGrid);
        if (!checkCharacters(passedGrid))
        {
            cout << "illegal charcter detected in input map" << endl;
            parse();
        }
        grid = new Grid(row, col, passedGrid);

    }
    else
    {
        int row = 0;
        int col = 0;
        string stringCol;
        string stringRow;
        cout << "enter number of rows:" << endl;
        cin >> stringRow;
        cout << "enter number of cols:" << endl;
        cin >> stringCol;
        cout << "enter float value:(example:.892)" << endl; //lol this wont break if you dont do it right but if you mess up enough itll die lol
                                                            //this will be interpreted as a float it calls the function itsel;f if error occurs
        cin >> stringDensity;
        try
        {
            row = stoi(stringRow);
            col = stoi(stringCol);
            density = stof(stringDensity + "f");
        }
        catch (const invalid_argument& ia)//got from c++.com
        {
            cout << "bad input in row integer" << endl;
            parse();
            return;
        }
        if (density > 1 || density < 0)
        {
            cout << "density is greater than 1 or less than 0, this is not possible" << endl;
            parse();
            return;
        }
        grid = new Grid(row, col, density)

    }
}

int main(int argc, char **argv)
{
  parse();
  return 0;
}
