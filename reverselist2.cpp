#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Reverse a linked-list.
//
//------------------------------------------------------------------------------
template<class Object>
class ListNode
{
public:
    Object m_object;
    ListNode<Object>* m_pNext;

    ListNode(const Object& object, ListNode<Object>* pNext = nullptr)
        : m_object(object), m_pNext(pNext) {}
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
ListNode<Object>* reverse(ListNode<Object>* pNode)
{
    if (nullptr == pNode)
    {
        return nullptr;
    }

    ListNode<Object>* pCurrent = pNode;
    pNode = pNode->m_pNext;
    pCurrent->m_pNext = nullptr;

    while (pNode != nullptr)
    {
        ListNode<Object>* pNext = pNode->m_pNext;
        pNode->m_pNext = pCurrent;
        pCurrent = pNode;
        pNode = pNext;
    }

    return pCurrent;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    ListNode<int> node5(5);
    ListNode<int> node4(4, &node5);
    ListNode<int> node3(3, &node4);
    ListNode<int> node2(2, &node3);
    ListNode<int> node1(1, &node2);

    ListNode<int>* tests[] =
    {
        &node5,
        &node1,
        nullptr,
    };

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        ListNode<int>* pNode = reverse(tests[i]);

        while (pNode != nullptr)
        {
            cout << pNode->m_object << " ";
            pNode = pNode->m_pNext;
        }

        cout << endl;
    }

    return 0;
}
