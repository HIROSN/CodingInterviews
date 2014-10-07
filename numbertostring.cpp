#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given any integer, print an English phrase that describes the integer
//  (e.g. "One thousand, two hundred thirty four").
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void Append(string& str, const char* append)
{
    if (append != nullptr)
    {
        if (!str.empty())
        {
            str += " ";
        }

        str += append;
    }
}


string ThreeDigitsToString(int number)
{
    const char* below20[] = { nullptr, "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen",
        "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

    const char* tens[] = { nullptr, "ten", "twenty", "thirty", "forty", "fifty",
        "sixty", "seventy", "eighty", "ninety" };

    string str;

    if (number >= 100)
    {
        Append(str, below20[number / 100]);
        Append(str, "hundred");
        number %= 100;
    }

    if (number >= 20)
    {
        Append(str, tens[number / 10]);
        number %= 10;
    }

    Append(str, below20[number]);

    return str;
}


string NumberToString(int number)
{
    const char* large[] = { nullptr, "thousand", "million", "billion" };
    string str;

    if (0 == number)
    {
        return "zero";
    }

    if (number < 0)
    {
        return "negative " + NumberToString(-number);
    }

    for (int i = 0; number > 0 && i < ARRAYSIZE(large); i++)
    {
        int digits = number % 1000;

        if (digits > 0)
        {
            string strDigits = ThreeDigitsToString(digits);
            Append(strDigits, large[i]);

            if (!str.empty())
            {
                strDigits += ",";
                Append(strDigits, str.c_str());
            }

            str = strDigits;
        }

        number /= 1000;
    }

    return str;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    int tests[] = { -1, 0, 1, 10, 13, 20, 21, 100, 101, 110, 117, 120, 147,
        999, 1000, 1010, 1200, 3006000, 1000000000, 1000000900, MAXINT32 };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        string str = NumberToString(tests[i]);
        str[0] += 'A' - 'a';
        cout << tests[i] << "\t\"" << str.c_str() << ".\"" << endl;
    }

    return 0;
}
