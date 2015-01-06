// {"category": "DP", "notes": "Build a sentence of words from string"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <map>
#include <vector>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given an original string of letters such as "catsanddogs", and a dictionary,
//  determine if the string can be broken into a sentence of words using only
//  the values in the dictionary.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
enum CacheState
{
    Undefined = 0,
    Exists = 1,
    DoesNotExist = 2,
};


bool StringMatching(
    string input,
    map<string, CacheState>& wordCache,
    vector<string>& output)
{
    switch (wordCache[input])
    {
    case Exists:
        output.push_back(input);
        return true;

    case DoesNotExist:
        return false;
    }

    bool match = false;

    for (string::size_type i = input.length() - 1; i > 0; i--)
    {
        string right = input.substr(i);

        if (Exists == wordCache[right])
        {
            string left = input.substr(0, i);
            vector<string> subout;

            if (StringMatching(left, wordCache, subout))
            {
                for (vector<string>::size_type j = 0; j < subout.size(); j++)
                {
                    output.push_back(subout[j] + " " + right);
                }

                match = true;
            }
            else
            {
                wordCache[left] = DoesNotExist;
            }
        }
    }

    return match;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    LPCSTR dictionary[] =
    {
        "cat",
        "cats",
        "sand",
        "and",
        "dogs",
    };

    map<string, CacheState> wordCache;

    for (int i = 0; i < ARRAYSIZE(dictionary); i++)
    {
        wordCache[string(dictionary[i])] = Exists;
    }

    LPCSTR tests[] =
    {
        "batsanddogs",
        "batsandcats",
        "ratsandcats",
        "ratsanddogs",
        "catsanddogs",
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        vector<string> output;

        if (StringMatching(string(tests[i]), wordCache, output))
        {
            for (vector<string>::size_type j = 0; j < output.size(); j++)
            {
                cout << output[j].c_str() << endl;
            }
        }
    }

    return 0;
}
