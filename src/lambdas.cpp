// {"category": "C++11", "notes": "Lambda expressions"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Lambda expressions
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    vector<HWND> childWindows;

    EnumWindows([](_In_ HWND hwnd, _In_ LPARAM lParam) -> BOOL
    {
        EnumChildWindows(hwnd, [](_In_ HWND hwnd, _In_ LPARAM lParam) -> BOOL
        {
            reinterpret_cast<vector<HWND>*>(lParam)->push_back(hwnd);
            return TRUE;
        }, lParam);

        return TRUE;
    }, reinterpret_cast<LPARAM>(&childWindows));

    const wstring tabWindowClass = L"TabWindowClass";
    WCHAR text[MAX_PATH];

    for_each(childWindows.begin(), childWindows.end(), [&](HWND hwnd)
    {
        if (RealGetWindowClassW(hwnd, text, ARRAYSIZE(text)) != 0)
        {
            if (text == tabWindowClass)
            {
                if (GetWindowTextW(hwnd, text, ARRAYSIZE(text)) != 0)
                {
                    wprintf(L"%s\n", text);
                }
            }
        }
    });

    return 0;
}
