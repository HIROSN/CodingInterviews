#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <map>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  You are given a tower of wine glasses. Each wine glass in an upper row
//  spills into two lower glasses on either side. The tower forms a triangle
//  and so the first cup spills equally into the two cups in the second row.
//  This continues throughout all of the rows.
//
//  I am going to hand you a set amount of water to pour, name this water.
//  I will also tell you how much each cup can hold, name this capacity.
//  I will then ask you how much water is in the cup in given row and column.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
double ChampagneTower(
    double water,
    double capacity,
    unsigned int row,
    unsigned int col)
{
    if (0 == row || 0 == col || col > row)
    {
        return 0.0;
    }

    col = min(col, row - col + 1);
    map<int, double> cup;
    cup[0] = water;

    for (unsigned int r = 1; r < row; r++)
    {
        for (unsigned int c = min(col - 1, r); c > 0 ; c--)
        {
            cup[c] = max((cup[c] - capacity) / 2.0, 0.0) +
                max((cup[c - 1] - capacity) / 2.0, 0.0);
        }

        cup[0] = max((cup[0] - capacity) / 2.0, 0.0);
    }

    return min(cup[col - 1], capacity);
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    double water = 100.0;
    double capacity = 10.0;

    if (argc > 2)
    {
        int iw = 0;
        int ic = 0;

        swscanf_s(argv[1], L"%d", &iw);
        swscanf_s(argv[2], L"%d", &ic);

        water = static_cast<double>(iw);
        capacity = static_cast<double>(ic);
    }

    cout << "Water: " << water << endl;
    cout << "Capacity: " << capacity << endl;

    double total = 0.0;
    int cup = 0;

    for (int row = 1; true; row++)
    {
        int countEmpty = 0;

        for (int col = 1; col <= row; col++)
        {
            double held = ChampagneTower(water, capacity, row, col);
            total += held;
            ++cup;

            if (held > 0.0)
            {
                cout << "Cup " << cup << "\t(r:" << row << ",\tc:" << col;
                cout << ") :\t" << held << endl;
            }
            else
            {
                ++countEmpty;
            }
        }

        if (countEmpty >= row)
        {
            break;
        }

        cout << endl;
    }

    cout << (total == water ? "[PASS] " : "[FAIL] ");
    cout << "Total: " << total << endl;
    return 0;
}
