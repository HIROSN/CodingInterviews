// {"category": "Algorithm", "notes": "Find largest distance in integer array"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given an unsorted array of integers, find the largest distance between
//  indices i and j such that array[i] < array[j].
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int LargestDistance(int* pIntArray, unsigned int size)
{
    if (0 == size || nullptr == pIntArray)
    {
        return 0;
    }

    int distance = 0;

    for (distance = size - 1; distance > 0; distance--)
    {
        if (pIntArray[0] != pIntArray[distance] ||
            pIntArray[size - 1 - distance] != pIntArray[size - 1])
        {
            break;
        }
    }

    return distance;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    // distance = 0
    int intArray1[] = { 1 };
    cout << LargestDistance(intArray1, 1) << endl;

    // distance = 0
    int intArray2[] = { 1, 1 };
    cout << LargestDistance(intArray2, 2) << endl;

    // i = 0, j = 1, distance = 1
    int intArray3[] = { 1, 2 };
    cout << LargestDistance(intArray3, 2) << endl;

    // i = 0, j = 4, distance = 4
    int intArray4[] = { 1, 2, 3, 4, 5 };
    cout << LargestDistance(intArray4, 5) << endl;

    // i = 4, j = 0, distance = 4
    int intArray5[] = { 5, 4, 3, 2, 1 };
    cout << LargestDistance(intArray5, 5) << endl;

    // i = 0, j = 3, distance = 3
    int intArray6[] = { 1, 1, 1, 2, 1 };
    cout << LargestDistance(intArray6, 5) << endl;

    // i = 4, j = 1, distance = 3
    int intArray7[] = { 1, 2, 1, 1, 1 };
    cout << LargestDistance(intArray7, 5) << endl;

    // i = 0, j = 2, distance = 2
    int intArray8[] = { 1, 1, 2, 1, 1 };
    cout << LargestDistance(intArray8, 5) << endl;

    // distance = 0
    int intArray9[] = { 1, 1, 1, 1, 1 };
    cout << LargestDistance(intArray9, 5) << endl;

    return 0;
}
