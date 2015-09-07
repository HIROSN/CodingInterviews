// {"category": "C++11", "notes": "Thread local storage"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Thread local storage
//
//------------------------------------------------------------------------------
template <typename Object>
Object& ThreadLocal()
{
    static thread_local Object object;
    return object;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
struct Storage
{
    DWORD id;
    string name;
};

void print()
{
    Storage storage = ThreadLocal<Storage>();
    cout << "Thread ID " << storage.id << ", ";
    cout << R"(Name: ")" << storage.name.c_str() << R"(")" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    Storage& storage = ThreadLocal<Storage>();
    storage.id = GetCurrentThreadId();
    storage.name = "Primary thread";
    print();

    HANDLE thread = CreateThread(nullptr, 0, [](LPVOID) -> DWORD
    {
        Storage& storage = ThreadLocal<Storage>();
        storage.id = GetCurrentThreadId();
        storage.name = "Worker thread";
        print();

        return ERROR_SUCCESS;
    }, nullptr, 0, nullptr);

    WaitForSingleObject(thread, INFINITE);
    print();

    if (thread != NULL)
    {
        CloseHandle(thread);
    }
    return 0;
}
