// {"category": "List", "notes": "Find K-th node from tail of list"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Find the k th node from the tail of the list.
//
//------------------------------------------------------------------------------
template <class Object>
class ListNode
{
public:
    Object m_object;
    ListNode<Object>* m_pNext;

    ListNode<Object>(const Object& object, ListNode<Object>* pNext)
        : m_object(object), m_pNext(pNext) {}
};


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
template <class Object>
ListNode<Object>* FindTheKthToTail(ListNode<Object>* pListHead, unsigned int k)
{
    if (nullptr == pListHead || 0 == k)
    {
        return nullptr;
    }

    ListNode<Object>* pTail = pListHead;
    ListNode<Object>* pKth = pListHead;

    for (unsigned int i = 0; i < k - 1; i++)
    {
        pTail = pTail->m_pNext;

        if (nullptr == pTail)
        {
            return nullptr;
        }
    }

    while (pTail->m_pNext != nullptr)
    {
        pTail = pTail->m_pNext;
        pKth = pKth->m_pNext;
    }

    return pKth;
}


//------------------------------------------------------------------------------
//
//  Unit tests
//
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    ListNode<int> node5(5, nullptr);
    ListNode<int> node4(4, &node5);
    ListNode<int> node3(3, &node4);
    ListNode<int> node2(2, &node3);
    ListNode<int> node1(1, &node2);

    struct TestCase
    {
        unsigned int k;
        bool isFound;
        int object;
    };

    const TestCase tests[] =
    {
        { 0, false, 0 },
        { 1, true,  5 },
        { 2, true,  4 },
        { 3, true,  3 },
        { 4, true,  2 },
        { 5, true,  1 },
        { 6, false, 0 },
    };

    int countFailed = 0;

    if (FindTheKthToTail<int>(nullptr, 1) != nullptr)
    {
        countFailed++;
    }

    for (int i = 0; i < ARRAYSIZE(tests); i++)
    {
        ListNode<int>* pKth = FindTheKthToTail<int>(&node1, tests[i].k);
        bool isFound = (pKth != nullptr);
        bool failed = false;

        if (isFound != tests[i].isFound)
        {
            failed = true;
        }
        else if (isFound && pKth->m_object != tests[i].object)
        {
            failed = true;
        }

        if (failed)
        {
            countFailed++;
            cout << "Failed, " << tests[i].k << "th object is ";
            cout << (isFound ? "found as " : "not found as ");
            cout << pKth->m_object << " (expected " << tests[i].object;
            cout << ")" << endl;
        }
    }

    cout << ARRAYSIZE(tests) - countFailed << " passed, ";
    cout << countFailed << " failed." << endl;

    return 0;
}
