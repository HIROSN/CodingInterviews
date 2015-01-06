// {"category": "Matrix", "notes": "Rotate N x N matrix in place"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given an image represented by an N x N matrix, where each pixel in the
//  image is 4 bytes, write a method to rotate the image by 90 degrees.
//  Can you do this in place?
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void RotateMatrix90(int** matrix, int n)
{
    if (nullptr == matrix || n < 2)
    {
        return;
    }

    for (int layer = 0; layer < n / 2; layer++)
    {
        int first = layer;
        int last = n - 1 - layer;

        for (int i = first; i < last; i++)
        {
            int offset = i - first;
            int temp = matrix[first][i];
            matrix[first][i] = matrix[last - offset][first];
            matrix[last - offset][first] = matrix[last][last - offset];
            matrix[last][last - offset] = matrix[i][last];
            matrix[i][last] = temp;
        }
    }
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int** InitMatrix(int n)
{
    int** matrix = nullptr;

    if (n > 0)
    {
        matrix = new int*[n];
        int count = 0;

        for (int i = 0; i < n; i++)
        {
            matrix[i] = new int[n];

            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = ++count;
            }
        }
    }

    return matrix;
}


void DeleteMatrix(int** matrix, int n)
{
    if (matrix != nullptr)
    {
        for (int i = 0; i < n; i++)
        {
            if (matrix[i] != nullptr)
            {
                delete[] matrix[i];
            }
        }

        delete[] matrix;
    }
}


void PrintMatrix(int** matrix, int n)
{
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            if (matrix[y][x] < 10)
            {
                cout << " ";
            }

            cout << matrix[y][x] << " ";
        }

        cout << endl;
    }

    cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
    for (int n = 0; n <= 5; n++)
    {
        int** matrix = InitMatrix(n);
        PrintMatrix(matrix, n);
        RotateMatrix90(matrix, n);
        PrintMatrix(matrix, n);
        DeleteMatrix(matrix, n);
    }

    return 0;
}
