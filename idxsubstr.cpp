#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Index to the first character of the first substring in a string.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int IndexOfSubstring(char* pString, char* pSubstring)
{
    if (nullptr == pString || nullptr == pSubstring || '\0' == *pSubstring)
    {
        return -1;
    }

    const char* pCopyString = pString;

    while (*pString != '\0')
    {
        char* pStr = pString;
        char* pSub = pSubstring;

        while (*pStr != '\0' && *pSub != '\0' && *pStr == *pSub)
        {
            ++pStr;
            ++pSub;
        }

        if ('\0' == *pSub)
        {
            return (pString - pCopyString);
        }

        ++pString;
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
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        int index = IndexOfSubstring(tests[i].pString, tests[i].pSubstring);
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
