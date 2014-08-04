#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Please implement a function that checks whether a positive number is a
//  palindrome or not.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool IsPalindrome(unsigned int number)
{
    bool isPalindrome = false;
    unsigned int reversed = 0;
    const unsigned int copy = number;
    bool overflow = false;

    while (number != 0)
    {
        unsigned int digit = number % 10;

        if (reversed > MAXUINT32 / 10)
        {
            overflow = true;
            break;
        }

        reversed *= 10;

        if (reversed > MAXUINT32 - digit)
        {
            overflow = true;
            break;
        }

        reversed += digit;
        number /= 10;
    }

    if (!overflow)
    {
        isPalindrome = (copy == reversed);
    }
    else
    {
        const int c_numberLength = 20;
        char text[c_numberLength] = {};
        sprintf(text, "%I64d", static_cast<__int64>(copy));
        int length = strlen(text);
        isPalindrome = true;

        for (int i = 0; i < length / 2; i++)
        {
            if (text[i] != text[length - 1 - i])
            {
                isPalindrome = false;
                break;
            }
        }
    }

    return isPalindrome;
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
        unsigned int number;
        bool isPalindrome;
    };

    const TestCase tests[] =
    {
        { 121,          true },
        { 123,          false },
        { 0,            true },
        { 99,           true },
        { 4294884924,   true },
        { MAXUINT32,    false },
    };

    int countFailed = 0;

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        if (IsPalindrome(tests[i].number) != tests[i].isPalindrome)
        {
            countFailed++;
            cout << "Failed, number = " << tests[i].number << endl;
        }
    }

    cout << ARRAYSIZE(tests) - countFailed << " passed, ";
    cout << countFailed << " failed." << endl;

    return 0;
}
