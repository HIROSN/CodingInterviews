// {"category": "C++11", "notes": "Thread-safe singleton"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  http://www.nuonsoft.com/blog/2017/08/10/implementing-a-thread-safe-singleton-with-c11-using-magic-statics/
//
//------------------------------------------------------------------------------
class CSingleton final
{
public:
    static CSingleton& GetInstance();

private:
    CSingleton() = default;
    ~CSingleton() = default;

    CSingleton(const CSingleton&) = delete;
    CSingleton& operator=(const CSingleton&) = delete;
    CSingleton(CSingleton&&) = delete;
    CSingleton& operator=(CSingleton&&) = delete;
};

CSingleton& CSingleton::GetInstance()
{
    static CSingleton instance; // C++11 guarantees that this will be initialized in a thread-safe way.
    return instance;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    HANDLE thread = CreateThread(nullptr, 0, [](LPVOID) -> DWORD
    {
        cout << "GetInstance: " << &CSingleton::GetInstance() << endl;
        return ERROR_SUCCESS;
    }, nullptr, 0, nullptr);

    cout << "GetInstance: " << &CSingleton::GetInstance() << endl;
    WaitForSingleObject(thread, INFINITE);

    if (thread != NULL)
    {
        CloseHandle(thread);
    }
    return 0;
}
