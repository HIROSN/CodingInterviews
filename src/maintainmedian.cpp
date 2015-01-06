// {"category": "Algorithm", "notes": "Maintain median value in stream"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <queue>
#include <vector>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Numbers are randomly generated and passed to a method. Write a program to
//  find and maintain the median value as new values are generated.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
class Median
{
public:
    void AddNewNumber(int number)
    {
        if (m_maxHeap.size() == m_minHeap.size())
        {
            if (!m_minHeap.empty() && number > m_minHeap.top())
            {
                m_maxHeap.push(m_minHeap.top());
                m_minHeap.pop();
                m_minHeap.push(number);
            }
            else
            {
                m_maxHeap.push(number);
            }
        }
        else
        {
            if (number < m_maxHeap.top())
            {
                m_minHeap.push(m_maxHeap.top());
                m_maxHeap.pop();
                m_maxHeap.push(number);
            }
            else
            {
                m_minHeap.push(number);
            }
        }
    }

    int GetMedian()
    {
        if (m_maxHeap.empty())
        {
            return 0;
        }

        if (m_maxHeap.size() == m_minHeap.size())
        {
            return (m_maxHeap.top() + m_minHeap.top()) / 2;
        }

        return m_maxHeap.top();
    }

private:
    struct compare
    {
        bool operator()(const int& l, const int& r)
        {
            return l > r;
        }
    };

    priority_queue<int> m_maxHeap;
    priority_queue<int, vector<int>, compare> m_minHeap;
};


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    struct TestCase
    {
        int number;
        int median;
    };

    const TestCase tests[] =
    {
        { 3, 3 },
        { 5, 4 },
        { 7, 5 },
        { 1, 4 },
        { 2, 3 },
    };

    Median median;

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        median.AddNewNumber(tests[i].number);
        int result = median.GetMedian();
        cout << (result == tests[i].median ? "PASS" : "FAILED");
        cout << ": Add " << tests[i].number;
        cout << ", Median is " << result << endl;
    }

    return 0;
}
