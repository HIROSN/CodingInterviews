#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  How would you convert a string into an integer?
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int StrToInt(const char* pszString)
{
    int number = 0;
    int sign = 1;
    int length = 0;

    if (nullptr == pszString)
    {
        throw exception();
    }

    length = strlen(pszString);

    for (int i = 0; i < length; i++)
    {
        switch (pszString[i])
        {
        case '+':
            if (i != 0 || 1 == length)
            {
                throw exception();
            }
            break;

        case '-':
            if (i != 0 || 1 == length)
            {
                throw exception();
            }
            sign = -1;
            break;

        default:
            if (pszString[i] >= '0' && pszString[i] <= '9')
            {
                int toAdd = static_cast<int>(pszString[i] - '0');

                if (number > MAXINT32 / 10)
                {
                    throw exception();
                }

                number *= 10;

                if (sign > 0)
                {
                    if (number > MAXINT32 - toAdd)
                    {
                        throw exception();
                    }
                }
                else
                {
                    if (-number < -MAXINT32 - 1 + toAdd)
                    {
                        throw exception();
                    }
                }

                number += toAdd;
            }
            else
            {
                throw exception();
            }
            break;
        }
    }

    return sign * number;
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
        char* pszString;
        int numberExpected;
        bool exceptionExpected;
    };

    const TestCase tests[] =
    {
        { nullptr,          0,              true },
        { "",               0,              false },
        { "12345",          12345,          false },
        { "+12345",         12345,          false },
        { "3.14",           0,              true },
        { "0x1234",         0,              true },
        { "!@#$%",          0,              true },
        { "-67890",         -67890,         false },
        { "000",            0,              false },
        { "+",              0,              true },
        { "-",              0,              true },
        { "1+1",            0,              true },
        { "2-",             0,              true },
        { " ",              0,              true },
        { " 1",             0,              true },
        { "1 ",             0,              true },
        { "2147483646",     MAXINT32-1,     false },
        { "2147483647",     MAXINT32,       false },
        { "2147483648",     0,              true },
        { "2147483650",     0,              true },
        { "-2147483647",    -MAXINT32,      false },
        { "-2147483648",    -MAXINT32-1,    false },
        { "-2147483649",    0,              true },
        { "-2147483650",    0,              true },
    };

    int countFailed = 0;

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        bool failed = false;

        try
        {
            if (StrToInt(tests[i].pszString) != tests[i].numberExpected ||
                tests[i].exceptionExpected)
            {
                failed = true;
            }
        }
        catch (exception)
        {
            if (!tests[i].exceptionExpected)
            {
                failed = true;
            }
        }

        if (failed)
        {
            cout << "Failed test case { \"" << tests[i].pszString << "\", ";
            cout << tests[i].numberExpected << ", ";
            cout << tests[i].exceptionExpected << " }" << endl;
            countFailed++;
        }
    }

    cout << ARRAYSIZE(tests) - countFailed << " passed, ";
    cout << countFailed << " failed." << endl;

    return 0;
}
