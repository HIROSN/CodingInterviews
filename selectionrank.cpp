#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Find N-th smallest element in an array.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int Partition(int array[], int left, int right, int pivotValue)
{
    while (left <= right)
    {
        while (left <= right && array[left] <= pivotValue)
        {
            ++left;
        }

        while (left <= right && array[right] > pivotValue)
        {
            --right;
        }

        if (left < right)
        {
            swap(array[left], array[right]);
        }
    }

    return left - 1;
}


int FindMax(int array[], int left, int right)
{
    int maxValue = array[left];

    for (int i = left + 1; i <= right; i++)
    {
        if (array[i] > maxValue)
        {
            maxValue = array[i];
        }
    }

    return maxValue;
}


int SelectionRank(int array[], int left, int right, int rank)
{
    int length = right - left + 1;

    if (length <= 0 || rank <= 0 || rank > length)
    {
        return -1;
    }

    int pivotValue = array[left + (rand() % length)];
    int leftEnd = Partition(array, left, right, pivotValue);
    int leftSize = leftEnd - left + 1;

    if (leftSize == rank)
    {
        return FindMax(array, left, leftEnd);
    }

    if (leftSize > rank)
    {
        return SelectionRank(array, left, leftEnd, rank);
    }

    return SelectionRank(array, leftEnd + 1, right, rank - leftSize);
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int result = 0;

    for (int rank = 1; result >= 0; rank++)
    {
        int array[] = { 41, 67, 34, 0, 69, 24, 78, 58, 62, 64, 5, 45, 81, 27 };
        result = SelectionRank(array, 0, ARRAYSIZE(array) - 1, rank);
        cout << result << " ";
    }

    cout << endl;
    return 0;
}
