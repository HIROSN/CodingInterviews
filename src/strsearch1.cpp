// {"category": "String", "notes": "String search with c, ., ^, $, *, +,?"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write a function that takes in a string pattern and a string of text and
//  determines of the text matches the given pattern. The pattern can consist
//  of the following classes:
//
//  c   Matches any literal character c
//  .   Matches any single character
//  ^   Matches the beginning of the input string
//  $   Matches the end of the input string
//  *   Matches zero or more occurrences of the previous character
//  +   Matches one of more occurrences of the previous character
//  ?   Matches zero or one occurrences of the previous character
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool match(char* pString, char* pPattern, char** ppNext)
{
    if (nullptr == pString || nullptr == pPattern)
    {
        return false;
    }

    if ('\0' == *pPattern)
    {
        if (ppNext != nullptr)
        {
            *ppNext = pString;
        }

        return true;
    }

    if ('^' == *pPattern || '$' == *pPattern)
    {
        // Ignore '^' or '$'.
        return match(pString, pPattern + 1, ppNext);
    }

    if ('*' == *(pPattern + 1))
    {
        if (*pString == *pPattern || *pString != '\0' && '.' == *pPattern)
        {
            // Continue on the current pattern.
            if (match(pString + 1, pPattern, ppNext))
            {
                return true;
            }

            // Move onto the next pattern.
            if (match(pString + 1, pPattern + 2, ppNext))
            {
                return true;
            }
        }

        // Not a match. Ignore the '*'.
        return match(pString, pPattern + 2, ppNext);
    }

    if ('+' == *(pPattern + 1))
    {
        if (*pString == *pPattern || *pString != '\0' && '.' == *pPattern)
        {
            // Continue on the current pattern.
            if (match(pString + 1, pPattern, ppNext))
            {
                return true;
            }

            // Move onto the next pattern.
            if (match(pString + 1, pPattern + 2, ppNext))
            {
                return true;
            }
        }

        return false;
    }

    if ('?' == *(pPattern + 1))
    {
        if (*pString == *pPattern || *pString != '\0' && '.' == *pPattern)
        {
            // One match in the current pattern, then no more match.
            if (match(pString + 1, pPattern, ppNext) &&
                match(pString + 1, pPattern + 2, ppNext))
            {
                return true;
            }
        }

        // Not a match. Ignore the '?'.
        return match(pString, pPattern + 2, ppNext);
    }

    if (*pString == *pPattern || *pString != '\0' && '.' == *pPattern)
    {
        // Move onto the next pattern.
        return match(pString + 1, pPattern + 1, ppNext);
    }

    return false;
}


bool FindFirstMatch(
    char* pString,
    char* pPattern,
    size_t& indexFound,
    size_t& indexNext)
{
    if (nullptr == pString || nullptr == pPattern)
    {
        return false;
    }

    char* pCopy = pString;

    while (*pString != '\0')
    {
        char* pNext = nullptr;

        if (match(pString, pPattern, &pNext))
        {
            indexFound = pString - pCopy;
            indexNext = pNext - pString;

            // Ensure string after the match is empty at the end of the string.
            if ('$' == *(pPattern + strlen(pPattern) - 1) && *pNext != '\0')
            {
                return false;
            }

            return true;
        }

        if ('^' == *pPattern)
        {
            // Did not find a match at the beginning of the string.
            return false;
        }

        ++pString;
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
        bool found;
        size_t at;
        char* as;
    };

    const TestCase tests[] =
    {
        { "aaa",        "a.a",      true,   0,  "aaa" },
        { "aaa",        "ab*ac*a",  true,   0,  "aaa" },
        { "aaa",        "aa.a",     false,  0,  nullptr },
        { "aaa",        "ab*a",     true,   0,  "aa" },
        { "aaa",        ".*b*",     true,   0,  "aaa" },
        { "ac",         "a.*c",     true,   0,  "ac" },
        { "aaab",       "a*b*",     true,   0,  "aaab" },
        { "aaabbb",     "...b*",    true,   0,  "aaabbb" },
        { "aaa",        ".",        true,   0,  "a" },
        { "aaa",        "*",        false,  0,  nullptr },
        { "aaa",        "",         true,   0,  "" },
        { "aaa",        nullptr,    false,  0,  nullptr },
        { "",           ".",        false,  0,  nullptr },
        { "",           "",         false,  0,  nullptr },
        { nullptr,      "a",        false,  0,  nullptr },
        { ".",          ".",        true,   0,  "." },
        { ".",          "*",        false,  0,  nullptr },
        { "*",          "*",        true,   0,  "*" },
        { "*",          "**",       true,   0,  "*" },
        { "abc",        "c",        true,   2,  "c" },
        { "abc",        ".c",       true,   1,  "bc" },
        { "abc",        "^a",       true,   0,  "a" },
        { "abc",        "^c",       false,  0,  nullptr },
        { "abc",        "c$",       true,   2,  "c" },
        { "abc",        "b$",       false,  0,  nullptr },
        { "aaaaabbbbb", "ab*b",     true,   4,  "abbbbb" },
        { "aaabbbccc",  "ab*bc",    true,   2,  "abbbc" },
        { "aaabbbccc",  "b*",       true,   0,  "" },
        { "aaaaabbbbb", "b+",       true,   5,  "bbbbb" },
        { "aaabbbccc",  "b+",       true,   3,  "bbb" },
        { "aaabbbccc",  "bcc?",     true,   5,  "bcc" },
        { "aaabbbccc",  "bc?",      true,   3,  "b" },
        { "aaabbbccc",  "ab?bc",    false,  0,  nullptr },
    };

    for (int i = 0; i < ARRAYSIZE(tests); ++i)
    {
        char* current = tests[i].string;
        char* pattern = tests[i].pattern;
        size_t found = 0;
        size_t next = 0;
        bool result = FindFirstMatch(current, pattern, found, next);
        string match = result ? string(current).substr(found, next) : "";
        bool pass = (result == tests[i].found);
        if (result) pass = (pass && found == tests[i].at);
        if (result) pass = (pass && match == string(tests[i].as));

        cout << (pass ? "PASS: \"" : "FAILED: \"");
        cout << (nullptr == pattern ? "(null)" : pattern);
        cout << "\" is " << (result ? "found" : "not found") << " in \"";
        cout << (nullptr == current ? "(null)" : current) << "\"";
        if (result) cout << " @" << found << " as \"" << match.c_str() << "\"";
        cout << endl;
    }

    return 0;
}
