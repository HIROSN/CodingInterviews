// {"category": "List", "notes": "Sort a list"}

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <Windows.h>
using namespace std;


//------------------------------------------------------------------------------
//
//  Please implement a function to sort a given list.
//
//------------------------------------------------------------------------------
template<class Object>
class ListNode
{
public:
    ListNode<Object>(const Object& object = Object());
    ~ListNode();

    void Add(const Object& object);
    void Print();

private:
    Object m_object;
    ListNode<Object>* m_pNext;


//------------------------------------------------------------------------------
//
//  Implementation
//
//------------------------------------------------------------------------------
public:
    void Sort();

private:
    void Move(
        ListNode<Object>* pToBeMoved,
        ListNode<Object>* pPrevious,
        ListNode<Object>* pInsertAfter);
};


template<class Object>
void ListNode<Object>::Sort()
{
    if (nullptr == m_pNext)
    {
        return;
    }

    ListNode<Object>* pHead = m_pNext;
    ListNode<Object>* pLastSorted = pHead;
    ListNode<Object>* pToBeSorted = pLastSorted->m_pNext;

    while (pToBeSorted != nullptr)
    {
        if (pHead->m_object > pToBeSorted->m_object)
        {
            // The node to be sorted becomes the new head of the sorted list.
            Move(pToBeSorted, pLastSorted, this);
        }
        else
        {
            // Traverse from the head node to find an appropriate location.
            ListNode<Object>* pNode = pHead;

            while (pNode != pLastSorted &&
                pNode->m_pNext->m_object < pToBeSorted->m_object)
            {
                pNode = pNode->m_pNext;
            }

            if (pNode != pLastSorted)
            {
                // Move the node to be sorted to the appropriate location.
                Move(pToBeSorted, pLastSorted, pNode);
            }
            else
            {
                // The node to be sorted is sorted.
                pLastSorted = pLastSorted->m_pNext;
            }
        }

        // Advance to the next node to be sorted.
        pToBeSorted = pLastSorted->m_pNext;
    }
}


template<class Object>
void ListNode<Object>::Move(
    ListNode<Object>* pToBeMoved,
    ListNode<Object>* pPrevious,
    ListNode<Object>* pInsertAfter)
{
    pPrevious->m_pNext = pToBeMoved->m_pNext;
    pToBeMoved->m_pNext = pInsertAfter->m_pNext;
    pInsertAfter->m_pNext = pToBeMoved;
}


//------------------------------------------------------------------------------
//
//  Demo execution
//
//------------------------------------------------------------------------------
template<class Object>
ListNode<Object>::ListNode(const Object& object)
    : m_object(object), m_pNext(nullptr)
{
}


template<class Object>
ListNode<Object>::~ListNode()
{
    if (m_pNext != nullptr)
    {
        delete m_pNext;
    }
}


template<class Object>
void ListNode<Object>::Add(const Object& object)
{
    ListNode<Object>* pNext = new ListNode<Object>(object);

    if (nullptr == m_pNext)
    {
        m_pNext = pNext;
    }
    else
    {
        ListNode<Object>* pLast = m_pNext;

        while (pLast->m_pNext != nullptr)
        {
            pLast = pLast->m_pNext;
        }

        pLast->m_pNext = pNext;
    }
}


template<class Object>
void ListNode<Object>::Print()
{
    ListNode<Object>* pNext = m_pNext;

    while (pNext != nullptr)
    {
        cout << pNext->m_object << " ";
        pNext = pNext->m_pNext;
    }

    cout << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
    const int list[] = { 3, 2, 1, 4, 3 };
    ListNode<int> listHead;

    for (int i = 0; i < ARRAYSIZE(list); i++)
    {
        listHead.Add(list[i]);
    }

    listHead.Print();
    listHead.Sort();
    listHead.Print();

    return 0;
}
