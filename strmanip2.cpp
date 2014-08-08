#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stack>
#include <Windows.h>
#include <strsafe.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given a string such as "The quick brown fox jumps over the lazy dog" write
//  a function that returns the string with the words in reverse order
//  "dog lazy the over jumps fox brown quick The".
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void WordsInReverseOrder(char* pString, int cch)
{
    if (nullptr == pString)
    {
        return;
    }

    char* const pCopy = pString;
    char* pStart = pString;
    stack<string> words;
    string reversed;

    while (*pString != '\0')
    {
        if (' ' == *pString)
        {
            if (pString > pStart)
            {
                words.push(string(pStart).substr(0, pString - pStart));
            }

            pStart = pString + 1;
        }

        ++pString;
    }

    if (pString > pStart)
    {
        words.push(string(pStart).substr(0, pString - pStart));
    }

    while (!words.empty())
    {
        if (!reversed.empty())
        {
            reversed += " ";
        }

        reversed += words.top();
        words.pop();
    }

    StringCchCopyA(pCopy, cch, reversed.c_str());
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    char string[] = "The quick brown fox jumps over the lazy dog";
    WordsInReverseOrder(string, ARRAYSIZE(string));
    cout << string << endl;
    return 0;
}
