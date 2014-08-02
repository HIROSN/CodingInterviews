#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Quicksort
//
//------------------------------------------------------------------------------
template<class Object>
void quicksort(Object numbers[], int start, int end);

template<class Object>
void median3(Object numbers[], int start, int end);

template<class Object>
int partition(Object numbers[], int start, int end);


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
void quicksort(Object numbers[], int start, int end)
{
    if (start < end)
    {
        int pivot = partition(numbers, start, end);
        quicksort(numbers, start, pivot - 1);
        quicksort(numbers, pivot + 1, end);
    }
}


template<class Object>
void median3(Object numbers[], int start, int end)
{
    int center = (start + end) / 2;

    if (numbers[start] > numbers[center])
    {
        swap(numbers[start], numbers[center]);
    }

    if (numbers[start] > numbers[end])
    {
        swap(numbers[start], numbers[end]);
    }

    // Place pivot at the end.
    if (numbers[end] > numbers[center])
    {
        swap(numbers[end], numbers[center]);
    }
}


template<class Object>
int partition(Object numbers[], int start, int end)
{
    int indexPivot = start;
    median3(numbers, start, end);

    for (int i = start; i <= end; i++)
    {
        // Pivot is at the end.
        if (numbers[i] < numbers[end])
        {
            if (i != indexPivot)
            {
                swap(numbers[indexPivot], numbers[i]);
            }

            ++indexPivot;
        }
    }

    if (indexPivot != end)
    {
        // Restore pivot.
        swap(numbers[indexPivot], numbers[end]);
    }

    return indexPivot;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int numbers[] = { 13, 81, 92, 43, 65, 31, 57, 26, 75, 0 };
    quicksort(numbers, 0, ARRAYSIZE(numbers) - 1);

    for (int i = 0; i < ARRAYSIZE(numbers); i++)
    {
        cout << numbers[i] << " ";
    }

    cout << endl;
    return 0;
}
