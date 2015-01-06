// {"category": "List", "notes": "Print a list from tail to head"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <memory>
#include <stack>
using namespace std;


//------------------------------------------------------------------------------
//
//  Please implement a function to print a list from its tail to head.
//
//------------------------------------------------------------------------------
template<class Object>
class ListNode
{
public:
    ListNode<Object>(const Object& object = Object());
    void Add(const Object& object);

private:
    Object m_object;
    shared_ptr<ListNode<Object>> m_spNext;


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
public:
    void ReversePrint();
};


template<class Object>
void ListNode<Object>::ReversePrint()
{
    stack<shared_ptr<ListNode<Object>>> nodes;
    shared_ptr<ListNode<Object>> spNext = m_spNext;

    while (spNext != nullptr)
    {
        nodes.push(spNext);
        spNext = spNext->m_spNext;
    }

    while (!nodes.empty())
    {
        cout << nodes.top()->m_object << " ";
        nodes.pop();
    }

    cout << endl;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
template<class Object>
ListNode<Object>::ListNode(const Object& object)
    : m_object(object), m_spNext(nullptr)
{
}


template<class Object>
void ListNode<Object>::Add(const Object& object)
{
    shared_ptr<ListNode<Object>> spNext = shared_ptr<ListNode<Object>>(
        new ListNode<Object>(object));

    if (nullptr == m_spNext)
    {
        m_spNext = spNext;
    }
    else
    {
        shared_ptr<ListNode<Object>> spLast = m_spNext;

        while (spLast->m_spNext != nullptr)
        {
            spLast = spLast->m_spNext;
        }

        spLast->m_spNext = spNext;
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
    ListNode<int> listHead;

    for (int i = 1; i <= 10; i++)
    {
        listHead.Add(i);
    }

    listHead.ReversePrint();

    return 0;
}
