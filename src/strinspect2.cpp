// {"category": "String", "notes": "Check if string is 3 letter words"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write a function that determines if a string is composed only of 3 letter
//  words.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool Has3LetterWords(char* pString)
{
    if (nullptr == pString)
    {
        return false;
    }

    size_t indexWord = 0;
    size_t numberOfWords = 0;

    for (size_t i = 0; i < strlen(pString) + 1; i++)
    {
        if (isspace(pString[i]) || '\0' == pString[i])
        {
            if (i > indexWord)
            {
                ++numberOfWords;

                if (i - indexWord != 3)
                {
                    return false;
                }
            }

            indexWord = i + 1;
        }
    }

    return (numberOfWords > 0);
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
        bool expected;
    };

    const TestCase tests[] =
    {
        { "foo bar baz", true },
        { "The tan dog barks", false },
        { nullptr, false },
        { "", false },
        { "1", false },
        { "12", false },
        { "123", true },
        { "       foo    bar ", true },
        { " ", false },
        { "          ", false },
        { "foo\t\nbar\nbaz\r\n", true },
        { "The\ttan\tdog\tbarks\r\n", false },
        { "\t", false },
        { "\r\n", false },
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        bool result = Has3LetterWords(tests[i].string);
        cout << (result == tests[i].expected ? "PASS " : "FAIL ");
        cout << (result ? "(true) : \"" : "(false) : \"");
        cout << (tests[i].string ? tests[i].string : "(null)") << "\"" << endl;
    }

    return 0;
}
