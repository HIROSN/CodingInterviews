// {"category": "C++11", "notes": "User defined literals"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <algorithm>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  User defined literals
//
//------------------------------------------------------------------------------
constexpr long double operator "" _percent(long double percent)
{
    return percent / 100.0;
}

string operator "" _lodash(_In_ const char* cstring, size_t)
{
    string s(cstring);

    for_each(s.begin(), s.end(), [](char& c)
    {
        if (isspace(c))
        {
            c = '_';
        }
        else
        {
            c = tolower(c);
        }
    });

    return s;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    constexpr auto c_size = static_cast<size_t>(MAXINT16 * 25.0_percent);

    string underscoreDelimitedLowerCaseString =
        "The Quick Brown FOX Jumps Over a Lazy Dog"_lodash;

    cout << c_size << endl;
    cout << underscoreDelimitedLowerCaseString.c_str() << endl;

    return 0;
}
