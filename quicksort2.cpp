#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stack>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Quicksort
//
//------------------------------------------------------------------------------
template<class Object>
void quicksort(Object objects[], int start, int end);

template<class Object>
void median3(Object objects[], int start, int end);

template<class Object>
int partition(Object objects[], int start, int end);


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
void quicksort(Object objects[], int start, int end)
{
    struct Span
    {
        int start;
        int end;

        Span(int s, int e) : start(s), end(e) {}
    };

    stack<Span> spans;
    spans.push(Span(start, end));

    while (!spans.empty())
    {
        start = spans.top().start;
        end = spans.top().end;
        spans.pop();

        if (start < end)
        {
            int pivot = partition(objects, start, end);
            spans.push(Span(pivot + 1, end));
            spans.push(Span(start, pivot - 1));
        }
    }
}


template<class Object>
void median3(Object objects[], int start, int end)
{
    int center = (start + end) / 2;

    if (objects[start] > objects[center])
    {
        swap(objects[start], objects[center]);
    }

    if (objects[start] > objects[end])
    {
        swap(objects[start], objects[end]);
    }

    // Place pivot at the end.
    if (objects[end] > objects[center])
    {
        swap(objects[end], objects[center]);
    }
}


template<class Object>
int partition(Object objects[], int start, int end)
{
    int indexPivot = start;
    median3(objects, start, end);

    for (int i = start; i <= end; i++)
    {
        // Pivot is at the end.
        if (objects[i] < objects[end])
        {
            if (i != indexPivot)
            {
                swap(objects[indexPivot], objects[i]);
            }

            ++indexPivot;
        }
    }

    if (indexPivot != end)
    {
        // Restore pivot.
        swap(objects[indexPivot], objects[end]);
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
