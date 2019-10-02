#include <iostream>
#include "Grid.h"
#include <cmath>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <thread>



using namespace std;

char userPauseSetting()
{
    cout << "do you want a slight (p)ause between generations, (w)ait for it to provide user input or to run (u)nintrrupted?" << endl;
    string c = "";
    cin >> c;
    if (c=="p"||c=="w"||c=="u")
      return c[0];
    else return userPauseSetting();

}
bool checkCharacters(Grid original)
{
    for (int i = 0; i < original.row;++i)
    {
        for (int j = 0; j < original.col; ++j)
        {
            if (original.myGrid[i][j] !='x' || original.myGrid[i][j] != '-')
                return false;
        }
    }
    return true;
}

void toUpperCase(Grid original)
{
    for (int i = 0; i < original.row;++i)
    {
        for (int j = 0; j < original.col; ++j)
        {
            if (original.myGrid[i][j] == 'x')
                original.myGrid[i][j]='X';
        }
    }
}




void parse(Grid grid)
{
    cout << "do you wish to enter a map file? (y/n)" << endl;
    char mapFile = 'X';
    cin >> mapFile;
    string line = "";

    if (mapFile != 'Y' && mapFile != 'N' && mapFile != 'y' && mapFile != 'n')
    {
        //this makes sure you enter correct values
        cout << "enter one of yYnN" << endl;
        parse(grid);
        return;
    }
    else if (mapFile == 'Y' || mapFile == 'y')
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
            getline(reader, line);
            row = stoi(line);
            getline(reader, line);
            col = stoi(line);
        }
        catch (const invalid_argument& ia)//got from c++.com
        {
            cout << "bad input in row and/or col values" << endl;
            parse(grid);
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
            if (line.length()==col)
            {
                for (char c: line)
                {
                    passedGrid[i][j++]=c;
                }
            }
            else
            {
                cout << "error in length of input file, input grid not correct dimensions" << endl;
                parse(grid);
                return;
            }
            ++i;
        }
        grid = Grid(row, col, passedGrid);
        toUpperCase(grid);
        if (!checkCharacters(grid))
        {
            cout << "illegal charcter detected in input map" << endl;
            parse(grid);
        }


    }
    else
    {
        int row = 0;
        int col = 0;
        float density = 0.0f;
        string stringCol;
        string stringRow;
        string stringDensity;

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
            parse(grid);
            return;
        }
        if (density > 1 || density < 0)
        {
            cout << "density is greater than 1 or less than 0, this is not possible" << endl;
            parse(grid);
            return;
        }
        cout << "entering grid construction" << endl;
        grid = Grid(row, col, density);
    }



}

int main(int argc, char **argv)
{
  Grid grid;
  parse(grid);
  char pauseStatus =  userPauseSetting();
  while (!grid.isEmpty()&&!grid.isConstant())
  {
      if (pauseStatus=='u')
      {
          grid.printGrid();
      }
      else if (pauseStatus=='w')
      {
          grid.printGrid();
          system("pause");
      }
      else if (pauseStatus=='p')
      {
          grid.printGrid();
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
      grid.populateNextGen();
  }
  return 0;
}
