// {"category": "C++11", "notes": "new and delete"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  new and delete
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    LPWSTR* strings = nullptr;
    const auto count = MAXINT16;

    try
    {
        strings = new LPWSTR[count](); // Zero initialized.

        for (auto i = 0; i < count; i++)
        {
            strings[i] = new WCHAR[count];
            _itow_s(i, strings[i], count, 10);
        }
    }
    catch (bad_alloc)
    {
        cout << "Out of memory.\n";
    }

    if (strings != nullptr)
    {
        for (auto i = 0; i < count; i++)
        {
            delete[] strings[i];
        }
    }

    delete[] strings;
    return 0;
}
