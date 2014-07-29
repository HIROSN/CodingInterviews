#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  In a 2-D matrix, every row is increasingly sorted from left to right, and
//  every column is increasingly sorted from top to bottom. Please implement a
//  function to check whether a number is in such a matrix or not.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool find(
    vector<vector<int>> matrix,
    int value,
    int row1,
    int col1,
    int row2,
    int col2)
{
    if (value < matrix[row1][col1] ||
        value > matrix[row2][col2])
    {
        return false;
    }

    if (value == matrix[row1][col1] ||
        value == matrix[row2][col2])
    {
        return true;
    }

    const int c_row1 = row1;
    const int c_col1 = col1;
    const int c_row2 = row2;
    const int c_col2 = col2;

    int midRow = (row1 + row2) / 2;
    int midCol = (col1 + col2) / 2;

    while (
        (row1 != midRow || col1 != midCol) &&
        (row2 != midRow || col2 != midCol))
    {
        if (value == matrix[midRow][midCol])
        {
            return true;
        }

        if (value < matrix[midRow][midCol])
        {
            row2 = midRow;
            col2 = midCol;
        }
        else
        {
            row1 = midRow;
            col1 = midCol;
        }

        midRow = (row1 + row2) / 2;
        midCol = (col1 + col2) / 2;
    }

    if (midRow < static_cast<int>(matrix.size() - 1))
    {
        if (find(matrix, value, midRow + 1, c_col1, c_row2, midCol))
        {
            return true;
        }
    }

    if (midCol < static_cast<int>(matrix[0].size() - 1))
    {
        if (find(matrix, value, c_row1, midCol + 1, midRow, c_col2))
        {
            return true;
        }
    }

    return false;
}


//------------------------------------------------------------------------------
//
//  Unit tests
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    const int array1[][4] =
    {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15},
    };

    vector<vector<int>> matrix1;

    for (int r = 0; r < ARRAYSIZE(array1); r++)
    {
        vector<int> row1;

        for (int c = 0; c < ARRAYSIZE(array1[0]); c++)
        {
            row1.push_back(array1[r][c]);
        }

        matrix1.push_back(row1);
    }

    vector<int> row2;
    row2.push_back(1);
    vector<vector<int>> matrix2;
    matrix2.push_back(row2);

    struct TestCase
    {
        vector<vector<int>> matrix;
        int value;
        bool found;
    };

    const TestCase tests[] =
    {
        {matrix1, 7,  true},
        {matrix1, 5,  false },
        {matrix1, 8,  true },
        {matrix1, 15, true },
        {matrix1, 0,  false},
        {matrix1, 16, false},
        {matrix2, 1,  true},
        {matrix2, 2,  false},
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        int value = tests[i].value;
        int row2 = static_cast<int>(tests[i].matrix.size() - 1);
        int col2 = static_cast<int>(tests[i].matrix[0].size() - 1);
        bool found = find(tests[i].matrix, value, 0, 0, row2, col2);
        cout << (found == tests[i].found ? "PASS: " : "FAIL: ");
        cout << value << " is" << (found ? "" : " not") << " found." << endl;
    }

	return 0;
}
