// {"category": "Algorithm", "notes": "Find majority element in array"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Find the majority element in an array if exists. The majority is an element
//  that occurs for more than half of the size of the array.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
bool isMajorityElement(
    int element,
    const vector<int>& intArray)
{
    vector<int>::size_type count = 0;

    for (auto& each : intArray)
    {
        count += (each == element) ? 1 : 0;
    }

    return (count * 2 > intArray.size());
}


int findMajorityElement(
    const vector<int>& intArray)
{
    int majorityElement;
    int count = 0;

    if (intArray.size() == 0)
    {
        throw exception();
    }

    for (auto& each : intArray)
    {
        if (0 == count)
        {
            majorityElement = each;
            count = 1;
        }
        else if (each == majorityElement)
        {
            ++count;
        }
        else
        {
            --count;
        }
    }

    if (!isMajorityElement(majorityElement, intArray))
    {
        throw exception();
    }

    return majorityElement;
}


//------------------------------------------------------------------------------
//
//  Unit tests
//
//------------------------------------------------------------------------------
int _tmain(
    int argc,
    _TCHAR* argv[])
{
    struct TestCase
    {
        vector<int> intArray;
        int majorityElement;
        bool exceptionExpected;
    };

    const TestCase tests[] =
    {
        { vector<int>{{1, 2, 3, 2, 2, 2, 5, 4, 2}}, 2, false },
        { vector<int>{{1, 2, 3, 2, 2, 2, 5, 4}}, 0, true },
        { vector<int>{{1}}, 1, false },
        { vector<int>(), 0, true },
    };

    int countFailed = 0;

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        bool failed = false;
        bool exceptionThrown = false;
        int majorityElement;

        try
        {
            majorityElement = findMajorityElement(tests[i].intArray);

            if (majorityElement != tests[i].majorityElement ||
                tests[i].exceptionExpected)
            {
                failed = true;
            }
        }
        catch (exception)
        {
            exceptionThrown = true;

            if (!tests[i].exceptionExpected)
            {
                failed = true;
            }
        }

        if (failed)
        {
            countFailed++;

            if (exceptionThrown)
            {
                cout << "Exception is thrown";
            }
            else
            {
                cout << "Majority element: " << majorityElement;
            }

            cout << " (Expected: " << tests[i].majorityElement;
            cout << ")" << endl;
        }
    }

    cout << ARRAYSIZE(tests) - countFailed << " passed, ";
    cout << countFailed << " failed." << endl;

    return 0;
}
