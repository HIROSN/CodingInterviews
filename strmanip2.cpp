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

    int indexWord = 0;
    stack<string> words;
    string copy(pString);
    string reversed;

    for (int i = 0; i < lstrlenA(pString) + 1; i++)
    {
        if (isspace(pString[i]) || '\0' == pString[i])
        {
            if (i > indexWord)
            {
                words.push(copy.substr(indexWord, i - indexWord));
            }

            indexWord = i + 1;
        }
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

    StringCchCopyA(pString, cch, reversed.c_str());
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
