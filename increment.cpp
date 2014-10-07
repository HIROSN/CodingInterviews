#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
/*
example: {1,2,3} represents 123 
{1,2,3} -> {1,2,4}
{3,4} -> {3,5}
{9} -> {1,0}
{-1,2,-3}
{999,4,5}
{1,2,MAXINT}
nullptr
size = -1
size = 0
size = MAXINT

void increment(int*& array, int size) {
    if (nullptr == array || size <= 0)
        throw std::exception();

    bool increment = true;
    
    for (int i = size - 1; increment && i >= 0; i--) {
        if (array[i] < 0 || array[i] >= 10)
            throw std::exception();
            
        if (++array[i] >= 10) {
            array[i] = 0;
        }
        else {
            increment = false;
        }
    }
    
    if (increment) {
        if (size > MAXINT - 1)
            throw std::exception();
            
        ++size;
        int* newArray = new int[size];
        newArray[0] = 1;
        for (int i = 1; i < size; i++) {
            newArray[i] = array[i - 1];
        }
        delete [] array;
        array = newArray;
    }
}
*/


//------------------------------------------------------------------------------
//
//  Unit tests
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{

    return 0;
}
