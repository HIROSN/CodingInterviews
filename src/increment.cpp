// {"category": "Array", "notes": "Increment number represented by array"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  An array of digits represents a positive number, for example {1, 2, 3}
//  represents 123. Write a program to increment the number.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void increment(int*& array, int& size)
{
    if (nullptr == array || size <= 0)
    {
        throw exception();
    }

    bool increment = true;

    for (int i = size - 1; increment && i >= 0; i--)
    {
        if (array[i] < 0 || array[i] >= 10)
        {
            throw exception();
        }

        if (++array[i] >= 10)
        {
            array[i] = 0;
        }
        else
        {
            increment = false;
        }
    }

    if (increment)
    {
        if (size > MAXINT - 1)
        {
            throw exception();
        }

        int* newArray = new int[size + 1];

        if (nullptr == newArray)
        {
            throw exception();
        }

        newArray[0] = 1;
        CopyMemory(&newArray[1], &array[0], sizeof(int) * size++);
        delete [] array;
        array = newArray;
    }
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int size = 3;
    int* array = new int[size];

    try
    {
        array[0] = 1;
        array[1] = 2;
        array[2] = 3;
        increment(array, size);
        for (int i = 0; i < size; i++) cout << array[i]; cout << endl;

        array[0] = 9;
        array[1] = 9;
        array[2] = 9;
        increment(array, size);
        for (int i = 0; i < size; i++) cout << array[i]; cout << endl;
    }
    catch (exception) {}
    delete[] array;

    return 0;
}
