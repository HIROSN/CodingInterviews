// {"category": "String", "notes": "Last substring in string"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write a function that takes in a substring and returns the index of the
//  last occurrence of the substring in a larger string.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int IndexOfLastSubstring(char* pString, char* pSubstring)
{
    if (nullptr == pString || nullptr == pSubstring || '\0' == *pSubstring)
    {
        return -1;
    }

    int length = lstrlenA(pString);

    for (int i = 0; i < length; i++)
    {
        int indexString = length - 1 - i;
        int indexSubstring = 0;
        int indexCopy = indexString;

        while (pString[indexString] != '\0' &&
            pSubstring[indexSubstring] != '\0' &&
            pString[indexString] == pSubstring[indexSubstring])
        {
            ++indexString;
            ++indexSubstring;
        }

        if ('\0' == pSubstring[indexSubstring])
        {
            return indexCopy;
        }
    }

    return -1;
}


//------------------------------------------------------------------------------
//
//  Unit tests
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    struct TestCase
    {
        char* pString;
        char* pSubstring;
        int index;
    };

    const TestCase tests[] =
    {
        { "abc", "ab", 0 },
        { "aaa", "bb", -1 },
        { "abc", "abcd", -1 },
        { "abc", "c", 2 },
        { "", "a", -1 },
        { "abc", "", -1 },
        { nullptr, "abc", -1 },
        { "abc", nullptr, -1 },
        { "abcdabcd", "bc", 5 },
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        int index = IndexOfLastSubstring(tests[i].pString, tests[i].pSubstring);
        bool pass = (index == tests[i].index);

        cout << (pass ? "PASS: \"" : "FAIL: \"");
        cout << (nullptr == tests[i].pSubstring ? "(null)" : tests[i].pSubstring);
        cout << "\" is ";
        if (-1 == index)
            cout << "not";
        else
            cout << "at " << index;
        cout << " in \"";
        cout << (nullptr == tests[i].pString ? "(null)" : tests[i].pString);
        cout << "\"" << endl;
    }

    return 0;
}
