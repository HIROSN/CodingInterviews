// {"category": "Algorithm", "notes": "Search string for smaller strings"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Given a string s and an array of smaller strings T, design a method to
//  search s for each small string in T.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
class SuffixTreeNode
{
public:
    SuffixTreeNode() : m_value('\0') {}

    SuffixTreeNode(string str)
        : m_value('\0')
    {
        for (string::size_type i = 0; i < str.length(); i++)
        {
            this->Insert(str.substr(i), i);
        }
    }

    void Insert(string str, int index)
    {
        m_indexes.push_back(index);

        if (!str.empty())
        {
            m_value = str[0];
            shared_ptr<SuffixTreeNode> spChild = m_children[m_value];

            if (nullptr == spChild)
            {
                spChild = shared_ptr<SuffixTreeNode>(new SuffixTreeNode());
                m_children[m_value] = spChild;
            }

            spChild->Insert(str.substr(1), index);
        }
    }

    vector<int> Search(string str)
    {
        if (str.empty())
        {
            return m_indexes;
        }

        shared_ptr<SuffixTreeNode> spChild = m_children[str[0]];

        if (spChild != nullptr)
        {
            return spChild->Search(str.substr(1));
        }

        return vector<int>();
    }

private:
    char m_value;
    vector<int> m_indexes;
    map<char, shared_ptr<SuffixTreeNode>> m_children;
};


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    SuffixTreeNode root(string("bibs"));
    char* t[] = { "b", "i", "s", "bi", "ib", "bs", "bib", "ibs", "bibs", "x" };

    for (int i = 0; i < ARRAYSIZE(t); i++)
    {
        vector<int> indexes = root.Search(string(t[i]));
        cout << "\"" << t[i] << "\" is ";

        if (indexes.size() > 0)
        {
            for (vector<int>::size_type j = 0; j < indexes.size(); j++)
            {
                cout << (0 == j ? "at " : ", ") << indexes[j];
            }
        }
        else
        {
            cout << "not found";
        }

        cout << endl;
    }

    return 0;
}
