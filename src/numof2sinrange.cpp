// {"category": "Algorithm", "notes": "Count number of 2's between 0 and n"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write a method to count the number of 2's between 0 and n.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int Count2sInRange(int number, int indexDigit)
{
    int powerOf10 = static_cast<int>(pow(10.0, indexDigit));
    int nextPowerOf10 = powerOf10 * 10;
    int roundDown = number - (number % nextPowerOf10);
    int roundUp = roundDown + nextPowerOf10;
    int digit = (number - roundDown) / powerOf10;

    if (digit < 2)
    {
        return roundDown / 10;
    }

    if (digit > 2)
    {
        return roundUp / 10;
    }

    return roundDown / 10 + (number % powerOf10) + 1;
}


int Count2sInRange(int number)
{
    int count = 0;
    int copy = number;

    for (int indexDigit = 0; copy > 0; indexDigit++)
    {
        count += Count2sInRange(number, indexDigit);
        copy /= 10;
    }

    return count;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int Count2sInRangeTest(int number)
{
    int count = 0;

    for (int i = 0; i <= number; i++)
    {
        int copy = i;

        while (copy > 0)
        {
            if ((copy % 10) == 2)
            {
                ++count;
            }

            copy /= 10;
        }
    }

    return count;
}


int _tmain(int argc, _TCHAR* argv[])
{
    int tests[] = { -1, 0, 1, 2, 10, 20, 22, 29, 30, 200, 222, 61523 };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        int count = Count2sInRange(tests[i]);
        int expected = Count2sInRangeTest(tests[i]);
        cout << (count == expected ? "PASS: n = " : "FAILED: n = ");
        cout << tests[i] << ", # of 2's: " << count << " (expected ";
        cout << expected << ")" << endl;
    }

    return 0;
}
