// {"category": "Algorithm", "notes": "Prime factorization"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Prime factorization is finding which prime numbers multiply together to
//  make the original number.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
vector<int> PrimeFactorization(int number)
{
    vector<int> primes;
    int divider = 2;

    while (number > 1 && divider <= number)
    {
        if ((number % divider) == 0)
        {
            primes.push_back(divider);
            number /= divider;
        }
        else
        {
            ++divider;
        }
    }

    return primes;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int tests[] = { 1000, 5001, 50001, 658 };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        vector<int> primes = PrimeFactorization(tests[i]);
        int product = 1;
        cout << tests[i] << " = ";

        for (vector<int>::size_type j = 0; j < primes.size(); j++)
        {
            product *= primes[j];
            cout << (j ? " x " : "") << primes[j];
        }

        cout << (product != tests[i] ? " !!FAILED!!" : "") << endl;
    }

    return 0;
}
