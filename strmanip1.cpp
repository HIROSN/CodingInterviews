#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given a string such as "The quick brown fox jumps over the lazy dog" write
//  a function that returns the reverse of the string "god yzal eht revo spmuj
//  xof nworb kciuq ehT".
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void reverse(char* pString)
{
    if (nullptr == pString)
    {
        return;
    }

    int length = strlen(pString);

    if (length < 2)
    {
        return;
    }

    for (int i = 0; i < length / 2; i++)
    {
        swap(pString[i], pString[length - 1 - i]);
    }
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    char string[] = "The quick brown fox jumps over the lazy dog\0";
    reverse(string);
    cout << string << endl;
    return 0;
}
