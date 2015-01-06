// {"category": "DP", "notes": "Find contiguous subarray within array"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Find the contiguous subarray within an array (containing at least one
//  number) which has the largest sum.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int LargestSumInSubarray(int array[], int length)
{
    if (length <= 0)
    {
        return 0;
    }

    int largestSum = array[0];
    int currentSum = array[0];

    for (int i = 1; i < length; i++)
    {
        currentSum = max(currentSum + array[i], array[i]);
        largestSum = max(largestSum, currentSum);
    }

    return largestSum;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int array1[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    cout << LargestSumInSubarray(array1, ARRAYSIZE(array1)) << endl;

    int array2[] = { -2, -1, -3, -4, -1, -2, -1, -5, -4 };
    cout << LargestSumInSubarray(array2, ARRAYSIZE(array2)) << endl;

    return 0;
}
