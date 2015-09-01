// {"category": "C++11", "notes": "unique_ptr deleter"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <memory>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  unique_ptr deleter
//
//------------------------------------------------------------------------------
struct HandleDeleter
{
    void operator()(HANDLE handle) const
    {
        CloseHandle(handle);
    }
};

using HandlePtr = unique_ptr<void, HandleDeleter>;


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    DWORD msecSleep = 10000;

    HandlePtr handle(CreateThread(nullptr, 0,
        [](_In_ LPVOID lpParameter) -> DWORD
    {
        Sleep(*reinterpret_cast<LPDWORD>(lpParameter));
        return ERROR_SUCCESS;
    }, &msecSleep, 0, nullptr));

    WaitForSingleObject(handle.get(), INFINITE);
    return 0;
}
