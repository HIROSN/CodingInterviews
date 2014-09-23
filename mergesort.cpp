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
void mergesort(Object objects[], Object* pCopy, int start, int end)
{
    if (nullptr == pCopy || start >= end)
    {
        return;
    }

    int center = (start + end) / 2;
    mergesort(objects, pCopy, start, center);
    mergesort(objects, pCopy, center + 1, end);

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
}


template<class Object>
void mergesort(Object objects[], int length)
{
    if (length > 0)
    {
        Object* pCopy = new Object[length];
        mergesort(objects, pCopy, 0, length - 1);
        delete[] pCopy;
    }
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int numbers[] = { 13, 81, 92, 43, 65, 31, 57, 26, 75, 0 };
    mergesort(numbers, ARRAYSIZE(numbers));

    for (int i = 0; i < ARRAYSIZE(numbers); i++)
    {
        cout << numbers[i] << " ";
    }

    cout << endl;
    return 0;
}
