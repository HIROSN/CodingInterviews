// {"category": "Array", "notes": "Return all subsets of a set"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Write a method to return all subsets of a set.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
vector<vector<int>> createSubsets(int array[], int size)
{
    if (nullptr == array)
    {
        throw exception();
    }

    vector<vector<int>> subsets;

    for (int index = 0; index < size; index++)
    {
        if (0 == index)
        {
            subsets.push_back(vector<int>());
        }

        int n = subsets.size();

        for (int j = 0; j < n; j++)
        {
            vector<int> a = subsets[j];
            a.push_back(array[index]);
            subsets.push_back(a);
        }
    }

    return subsets;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int array[] = { 1, 2, 3, 4, 5 };
    vector<vector<int>> subsets = createSubsets(array, ARRAYSIZE(array));

    for (vector<int>::size_type i = 0; i < subsets.size(); i++)
    {
        vector<int> a = subsets[i];
        cout << (i > 0 ? " " : "") << "[";

        for (vector<int>::size_type j = 0; j < a.size(); j++)
        {
            cout << (j > 0 ? "," : "") << a[j];
        }

        cout << "]";
    }

    cout << endl;
    return 0;
}
