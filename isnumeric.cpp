#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  How do you check whether a string stands for a number or not?
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int CountDigits(char* pString);


bool IsNumeric(char* pString)
{
    if (nullptr == pString)
    {
        return false;
    }

    if ('+' == *pString || '-' == *pString)
    {
        ++pString;
    }

    int nIntegralDigits = CountDigits(pString);
    pString += nIntegralDigits;

    int nFractionalDigits = 0;

    if ('.' == *pString)
    {
        ++pString;
        nFractionalDigits = CountDigits(pString);
        pString += nFractionalDigits;
    }

    if (0 == nIntegralDigits + nFractionalDigits)
    {
        return false;
    }

    if ('e' == *pString || 'E' == *pString)
    {
        ++pString;

        if ('+' == *pString || '-' == *pString)
        {
            ++pString;
        }

        int nExponentialDigits = CountDigits(pString);
        pString += nExponentialDigits;

        if (0 == nExponentialDigits)
        {
            return false;
        }
    }

    return ('\0' == *pString);
}


int CountDigits(char* pString)
{
    int count = 0;

    if (pString != nullptr)
    {
        while (*pString != '\0' && *pString >= '0' && *pString <= '9')
        {
            ++count;
            ++pString;
        }
    }

    return count;
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
        bool numeric;
    };

    const TestCase tests[] =
    {
        { "+100.",      true },
        { "5e2",        true },
        { "-.123",      true },
        { "3.1416",     true },
        { "-1E-16",     true },
        { "12e",        false },
        { "1a3.14",     false },
        { "1.2.3",      false },
        { "+-5",        false },
        { "12e+5.4",    false },
        { "1,000",      false },
        { "e1",         false },
        { ".E10",       false },
        { ".",          false },
        { "+",          false },
        { "",           false },
        { nullptr,      false },
    };

    for (int i = 0; i < ARRAYSIZE(tests); ++i)
    {
        bool result = IsNumeric(tests[i].string);
        bool pass = (result == tests[i].numeric);

        cout << (pass ? "PASS: \"" : "FAIL: \"");
        cout << (nullptr == tests[i].string ? "(null)" : tests[i].string);
        cout << "\" is" << (result ? "" : " not") << " numeric" << endl;
    }

    return 0;
}
