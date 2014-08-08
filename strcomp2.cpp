#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stack>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write a function that takes in two strings that represent decimal numbers,
//  computes the sum and outputs the answer as a third string.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool sum(char* pszNumber1, char* pszNumber2, char* pszAnswer, size_t cch)
{
    if (nullptr == pszNumber1 || nullptr == pszNumber2 ||
        '\0' == *pszNumber1 || '\0' == *pszNumber2 ||
        nullptr == pszAnswer || 0 == cch)
    {
        return false;
    }

    stack<char> digits1;
    stack<char> digits2;
    stack<char> digits3;
    char number = 0;

    while (*pszNumber1 != '\0')
    {
        if (*pszNumber1 < '0' || *pszNumber1 > '9')
        {
            return false;
        }

        digits1.push(*pszNumber1);
        ++pszNumber1;
    }

    while (*pszNumber2 != '\0')
    {
        if (*pszNumber2 < '0' || *pszNumber2 > '9')
        {
            return false;
        }

        digits2.push(*pszNumber2);
        ++pszNumber2;
    }

    while (!digits1.empty() || !digits2.empty())
    {
        if (!digits1.empty())
        {
            number += digits1.top() - '0';
            digits1.pop();
        }

        if (!digits2.empty())
        {
            number += digits2.top() - '0';
            digits2.pop();
        }

        digits3.push((number % 10) + '0');
        number /= 10;
    }

    if (number > 0)
    {
        digits3.push(number + '0');
    }

    if (digits3.size() >= cch)
    {
        return false;
    }

    for (size_t i = 0; !digits3.empty(); i++)
    {
        pszAnswer[i] = digits3.top();
        pszAnswer[i + 1] = '\0';
        digits3.pop();
    }

    return true;
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
        char* number1;
        char* number2;
        char* answer;
        bool valid;
    };

    const TestCase tests[] =
    {
        { "410", "175", "585", true },
        { "9993372036854775807", "6627963145224193", "10000000000000000000", true },
        { "1", "999", "1000", true },
        { nullptr, "123", "(undefined)", false },
        { "1", nullptr, "(undefined)", false },
        { "", "1", "(undefined)", false },
        { "0", "", "(undefined)", false },
        { ".", "0", "(undefined)", false },
        { "20", "928s", "(undefined)", false },
        { "0", "0", "0", true },
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        char answer[MAX_PATH] = {};

        bool result = sum(
            tests[i].number1,
            tests[i].number2,
            answer,
            ARRAYSIZE(answer));

        bool pass = (result == tests[i].valid);

        if (tests[i].valid)
        {
            pass = pass && strcmp(tests[i].answer, answer) == 0;
        }

        cout << (pass ? "PASS: \"" : "FAIL: \"");
        cout << (tests[i].number1 ? tests[i].number1 : "(null)") << "\" + \"";
        cout << (tests[i].number2 ? tests[i].number2 : "(null)") << "\" ";
        cout << (pass ? "=" : "!=") << " \"";
        cout << (result ? answer : tests[i].answer) << "\"" << endl;
    }

    return 0;
}
