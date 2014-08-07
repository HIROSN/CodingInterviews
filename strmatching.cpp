#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  How do you implement a function to match regular expressions with '.' and
//  '*' in patterns?
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool match(char* pString, char* pPattern)
{
    if (nullptr == pString || nullptr == pPattern)
    {
        return false;
    }

    if ('\0' == *pPattern)
    {
        return ('\0' == *pString);
    }

    if ('*' == *(pPattern + 1))
    {
        if (*pString == *pPattern || *pString != '\0' && '.' == *pPattern)
        {
            // Continue on the current pattern.
            if (match(pString + 1, pPattern))
            {
                return true;
            }

            // Move onto the next pattern.
            if (match(pString + 1, pPattern + 2))
            {
                return true;
            }
        }

        // Not a match. Ignore the '*'.
        return match(pString, pPattern + 2);
    }

    if (*pString == *pPattern || *pString != '\0' && '.' == *pPattern)
    {
        // Move onto the next pattern.
        return match(pString + 1, pPattern + 1);
    }

    return false;
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
        char* string;
        char* pattern;
        bool match;
    };

    const TestCase tests[] =
    {
        { "aaa",        "a.a",      true },
        { "aaa",        "ab*ac*a",  true },
        { "aaa",        "aa.a",     false },
        { "aaa",        "ab*a",     false },
        { "aaa",        ".*b*",     true },
        { "ac",         "a.*c",     true },
        { "aaab",       "a*b*",     true },
        { "aaabbb",     "...b*",    true },
        { "aaa",        ".",        false },
        { "aaa",        "*",        false },
        { "aaa",        "",         false },
        { "aaa",        nullptr,    false },
        { "",           ".",        false },
        { "",           "",         true },
        { nullptr,      "a",        false },
        { ".",          ".",        true },
        { ".",          "*",        false },
        { "*",          "*",        true },
        { "*",          "**",       true },
    };

    for (int i = 0; i < ARRAYSIZE(tests); ++i)
    {
        bool result = match(tests[i].string, tests[i].pattern);
        bool pass = (result == tests[i].match);

        cout << (pass ? "PASS: \"" : "FAIL: \"");
        cout << (nullptr == tests[i].string ? "(null)" : tests[i].string);
        cout << (result ? "\" == \"" : "\" != \"");
        cout << (nullptr == tests[i].pattern ? "(null)" : tests[i].pattern);
        cout << "\"" << endl;
    }

    return 0;
}
