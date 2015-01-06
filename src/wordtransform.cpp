// {"category": "Algorithm", "notes": "Transform one word into another"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given two words of equal length that are in a dictionary, write a method to
//  transform one word into another word by changing only one letter at a time.
//  The new word you get in each step must be in the dictionary.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
void GetOneEditWords(string word, vector<string>& words)
{
    for (string::size_type i = 0; i < word.length(); i++)
    {
        string copy = word;

        for (char c = 'a'; c <= 'z'; c++)
        {
            if (c != word[i])
            {
                copy[i] = c;
                words.push_back(copy);
            }
        }
    }
}


void WordTransform(
    string startWord,
    string endWord,
    map<string, bool>& dictionary)
{
    queue<string> wordQueue;
    map<string, bool> isVisited;
    map<string, string> backtrackMap;

    wordQueue.push(startWord);
    isVisited[startWord] = true;

    while (!wordQueue.empty())
    {
        string currentWord = wordQueue.front();
        wordQueue.pop();
        vector<string> nextWords;
        GetOneEditWords(currentWord, nextWords);

        for (vector<string>::size_type i = 0; i < nextWords.size(); i++)
        {
            string nextWord = nextWords[i];

            if (nextWord == endWord)
            {
                stack<string> printStack;
                printStack.push(endWord);

                while (!currentWord.empty())
                {
                    printStack.push(currentWord);
                    currentWord = backtrackMap[currentWord];
                }

                while (!printStack.empty())
                {
                    cout << printStack.top().c_str();
                    printStack.pop();

                    if (!printStack.empty())
                    {
                        cout << " => ";
                    }
                }

                cout << endl;
                return;
            }

            if (dictionary[nextWord] && !isVisited[nextWord])
            {
                wordQueue.push(nextWord);
                isVisited[nextWord] = true;
                backtrackMap[nextWord] = currentWord;
            }
        }
    }
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    const char* c_dictionary[] = { "damp", "lamp", "limp", "lime", "like" };
    map<string, bool> dictionary;

    for (int i = 0; i < ARRAYSIZE(c_dictionary); i++)
    {
        dictionary[string(c_dictionary[i])] = true;
    }

    WordTransform(string("damp"), string("like"), dictionary);

    return 0;
}
