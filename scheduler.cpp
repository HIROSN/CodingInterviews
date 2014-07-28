#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <memory>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  There are three threads in a process. The first thread prints 1 1 1 ...,
//  the second one prints 2 2 2 ..., and the third one prints 3 3 3 ...
//  endlessly. How do you schedule these three threads in order to print
//  1 2 3 1 2 3 ... ?
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
class Scheduler
{
public:
    static void Main(int count, int sleep, int seconds);
};


class SimpleThread
{
public:
    SimpleThread(int number, DWORD msecWait);
    ~SimpleThread();

    HRESULT Run();
    HRESULT Notify();

private:
    void ThreadProc();
    static DWORD WINAPI StaticThreadProc(LPVOID lpParameter);

private:
    int m_number;
    DWORD m_msecWait;
    HANDLE m_hThread;
    HANDLE m_hEvent;
    bool m_running;
};


void Scheduler::Main(int count, int sleep, int seconds)
{
    vector<shared_ptr<SimpleThread>> threads;
    DWORD msecStart = GetTickCount();
    DWORD msecRun = seconds * 1000;
    DWORD msecWait = sleep * (count + 1);

    for (int i = 1; i <= count; i++)
    {
        shared_ptr<SimpleThread> thread = shared_ptr<SimpleThread>(
            new SimpleThread(i, msecWait));

        if (nullptr == thread)
        {
            return;
        }

        if (FAILED(thread->Run()))
        {
            return;
        }

        threads.push_back(thread);
    }

    while (GetTickCount() < msecStart + msecRun)
    {
        for (vector<shared_ptr<SimpleThread>>::size_type i = 0;
            i < threads.size();
            i++)
        {
            Sleep(sleep);

            if (FAILED(threads[i]->Notify()))
            {
                return;
            }
        }
    }
}


SimpleThread::SimpleThread(int number, DWORD msecWait)
    : m_number(number), m_msecWait(msecWait),
    m_hThread(NULL), m_hEvent(NULL), m_running(false)
{
}


SimpleThread::~SimpleThread()
{
    m_running = false;

    if (m_hEvent != NULL)
    {
        CloseHandle(m_hEvent);
    }

    if (m_hThread != NULL)
    {
        WaitForSingleObject(m_hThread, m_msecWait);
        CloseHandle(m_hThread);
    }
}


HRESULT SimpleThread::Run()
{
    HRESULT hr = S_OK;

    if (NULL == m_hEvent)
    {
        m_hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        if (NULL == m_hEvent)
        {
            hr = GetLastError();
        }
    }

    if (SUCCEEDED(hr))
    {
        if (NULL == m_hThread)
        {
            m_running = true;

            m_hThread = CreateThread(
                nullptr,
                0,
                StaticThreadProc,
                this,
                0,
                nullptr);

            if (NULL == m_hThread)
            {
                hr = GetLastError();
                m_running = false;
            }
        }
    }

    return hr;
}


HRESULT SimpleThread::Notify()
{
    HRESULT hr = S_OK;

    if (m_hEvent != NULL)
    {
        if (!SetEvent(m_hEvent))
        {
            hr = GetLastError();
        }
    }
    else
    {
        hr = E_HANDLE;
    }

    return hr;
}


void SimpleThread::ThreadProc()
{
    while (m_running)
    {
        if (WaitForSingleObject(m_hEvent, m_msecWait) == WAIT_OBJECT_0)
        {
            cout << m_number << " ";
        }
    }
}


DWORD WINAPI SimpleThread::StaticThreadProc(LPVOID lpParameter)
{
    DWORD error = ERROR_SUCCESS;
    SimpleThread* pThis = reinterpret_cast<SimpleThread*>(lpParameter);

    if (pThis != nullptr)
    {
        pThis->ThreadProc();
    }
    else
    {
        error = ERROR_INVALID_PARAMETER;
    }

    return error;
}


//------------------------------------------------------------------------------
//
//  Demo execution.
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    const int threadCount = 3;
    const int msecSleep = 37;
    const int secondsRun = 10;

    Scheduler::Main(threadCount, msecSleep, secondsRun);

    cout << endl;
    return 0;
}
