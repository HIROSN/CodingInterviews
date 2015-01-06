// {"category": "Algorithm", "notes": "Find largest rectangle in histogram"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <stack>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given n non-negative integers representing the histogram's bar height
//  where the width of each bar is 1, find the area of largest rectangle
//  in the histogram.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
int largestRectangleArea(vector<int> &height)
{
    int area = 0;
    int size = static_cast<int>(height.size());
    int current = 0;
    stack<int> offsets;

    while (current < size || !offsets.empty())
    {
        if (offsets.empty() ||
            current < size && height[offsets.top()] <= height[current])
        {
            offsets.push(current);
            ++current;
        }
        else
        {
            int previous = offsets.top();
            offsets.pop();
            int width = current;

            if (!offsets.empty())
            {
                width = current - (offsets.top() + 1);
            }

            area = max(area, height[previous] * width);
        }
    }

    return area;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    const int c_height[] = { 2, 1, 5, 6, 2, 3 };
    vector<int> height;

    for (int i = 0; i < ARRAYSIZE(c_height); i++)
    {
        height.push_back(c_height[i]);
    }

    int area = largestRectangleArea(height);
    cout << "Largest rectangle area is " << area << endl;
    cout << (area == 10 ? "PASS" : "FAIL") << endl;
    return 0;
}
