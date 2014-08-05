#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------
//
//  When there is a loop in a linked list, how do you find the entry node of
//  the loop?
//
//------------------------------------------------------------------------------
template<class Object>
class ListNode
{
public:
    Object m_object;
    ListNode* m_pNext;

    ListNode<Object>(Object object, ListNode* pNext = nullptr)
        : m_object(object), m_pNext(pNext) {}
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template<class Object>
ListNode<Object>* EntryNodeOfLoop(ListNode<Object>* pHead)
{
    if (nullptr == pHead)
    {
        return nullptr;
    }

    ListNode<Object>* pSlow = pHead->m_pNext;

    if (nullptr == pSlow)
    {
        return nullptr;
    }

    ListNode<Object>* pFast = pSlow->m_pNext;

    while (pSlow != pFast)
    {
        if (nullptr == pSlow || nullptr == pFast)
        {
            return nullptr;
        }

        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;

        if (pFast != nullptr)
        {
            pFast = pFast->m_pNext;
        }
    }

    int numberOfNodesInLoop = 1;

    while (pSlow->m_pNext != pFast)
    {
        pSlow = pSlow->m_pNext;
        ++numberOfNodesInLoop;
    }

    pSlow = pHead;

    for (int i = 0; i < numberOfNodesInLoop; i++)
    {
        pSlow = pSlow->m_pNext;
    }

    while (pHead != pSlow)
    {
        pHead = pHead->m_pNext;
        pSlow = pSlow->m_pNext;
    }

    return pHead;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    ListNode<int>* pNull = nullptr;
    ListNode<int>* pEntry = EntryNodeOfLoop(pNull);
    if (pEntry) cout << pEntry->m_object; else cout << "(null)"; cout << endl;

    ListNode<int> node(1);
    node.m_pNext = &node;
    pEntry = EntryNodeOfLoop(&node);
    if (pEntry) cout << pEntry->m_object; else cout << "(null)"; cout << endl;

    ListNode<int> node6(6);
    ListNode<int> node5(5, &node6);
    ListNode<int> node4(4, &node5);
    ListNode<int> node3(3, &node4);
    ListNode<int> node2(2, &node3);
    ListNode<int> node1(1, &node2);
    pEntry = EntryNodeOfLoop(&node1);
    if (pEntry) cout << pEntry->m_object; else cout << "(null)"; cout << endl;

    node6.m_pNext = &node3;
    pEntry = EntryNodeOfLoop(&node1);
    if (pEntry) cout << pEntry->m_object; else cout << "(null)"; cout << endl;

    return 0;
}
