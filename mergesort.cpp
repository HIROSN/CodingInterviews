#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Mergesort
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
void mergesort(Object objects[], int start, int end)
{
    if (start >= end)
    {
        return;
    }

    int center = (start + end) / 2;
    mergesort(objects, start, center);
    mergesort(objects, center + 1, end);
    Object* pCopy = new Object[end + 1];

    for (int i = start; i <= end; i++)
    {
        pCopy[i] = objects[i];
    }

    int left = start;
    int right = center + 1;
    int index = start;

    while (left <= center && right <= end)
    {
        if (pCopy[left] < pCopy[right])
        {
            objects[index++] = pCopy[left++];
        }
        else
        {
            objects[index++] = pCopy[right++];
        }
    }

    for (int i = left; i <= center; i++)
    {
        objects[index++] = pCopy[i];
    }

    delete[] pCopy;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int numbers[] = { 13, 81, 92, 43, 65, 31, 57, 26, 75, 0 };
    mergesort(numbers, 0, ARRAYSIZE(numbers) - 1);

    for (int i = 0; i < ARRAYSIZE(numbers); i++)
    {
        cout << numbers[i] << " ";
    }

    cout << endl;
    return 0;
}
